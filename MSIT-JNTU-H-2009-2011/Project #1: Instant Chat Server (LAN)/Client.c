/*
 *	Main Client For Instant Messenger
 */

#include "im.h"

void *updateFriendsList(void *);
void *chatWithFriends(void *);
void *serverFTPFunction(void *);
void *serverFTPThreadFunction(void *);
void *clientFTPFunction(void *);

char usr[15]="guest",dwnFolder[50]="./Downloads",getFolder[50]="./PersonalFolder";
char cmd[5];
int sFd,cnt;
pthread_t updtListThread,chatThread,clientFTPThread,serverFTPThread,subServerFTPThread;
frnd_t fList[100];

// chat Varibales
int 			sSockFd,cSockFd,serFTPSockFd,newSerFTPSockFd;
struct sockaddr_in 	cSrvAdr,cCliAdr,ftpSrvAdr,ftpCliAdr,ftpCliAdr1,tcCliAdr;
time_t			now;
int 			cN,sln,cliLen,tfd;
char 			txMsg[PKT_LEN],rxMsg[PKT_LEN],fusr[15],tMsg[PKT_LEN],buff[PKT_LEN],pathFile[100],iTime[30],fileName[100];
short int 		cReq;

void signalHandler()
{
  char pkt[10];
  short int req;
  int len;
  if(strcmp(usr,"guest"))
  {
     pthread_cancel(updtListThread);
     pthread_cancel(chatThread);
     pthread_cancel(serverFTPThread);
     if(cnt == 1)
     {
       cnt=0;
       close(cSockFd); 
       close(sSockFd); 
       close(serFTPSockFd); 
     }
     userLogout(sFd,usr);
  }
  req = (short int) EXT;
  memset(pkt,0,sizeof(pkt));
  memcpy(pkt,&req,sizeof(req));
  len=sizeof(req)+1;
  if(send(sFd,pkt,len,0) != len)
     errMessage("Exit status error\n");
  printf("\nClient Is Shutting Down...........\nClient Ended.\n");
  exit(0);
}

void signalHandler1()
{
  memset(fList,0,sizeof(fList));
  friendsContactList(sFd,usr,(frnd_t *)fList);
  //displayFriendsList(fList);
}

int main()
{
  int 			sockFd;
  struct sockaddr_in 	srvAdr;
  int 			n;
  
  //sem_init(&clSemp1,0,0); 
  //sem_init(&clSemp2,0,0); 
  
  mkdir(dwnFolder,0777);
  mkdir(getFolder,0777);
 
  signal(SIGINT,signalHandler);
  signal(SIGTSTP,signalHandler);
  signal(SIGALRM,signalHandler1);

  initialProcess();
 
  if((sockFd=socket(AF_INET,SOCK_STREAM,0))<0)
    errMessage("Can't Open STREAM Socket\n");

  memset(&srvAdr,0,sizeof(srvAdr));
  srvAdr.sin_family=AF_INET;
  srvAdr.sin_addr.s_addr=inet_addr(SRV_IP);
  srvAdr.sin_port=htons(SRV_PORT);

  if(connect(sockFd,(struct sockaddr*)&srvAdr,sizeof(srvAdr))<0)
    errMessage("Can't Connect To Server\n");

  sFd = sockFd;

  while(1)
  {
    printf("\n[ %s ] # ",usr);
    scanf("%s",cmd);
    if(!strcmp(cmd,"help"))
    {
      printf("\n[ %-8s ] - Information about commands to be used\n[ %-8s ] - User can login\n[ %-8s ] - User can logout\n[ %-8s ] - Login registration\n[ %-8s ] - To end process\n[ %-8s ] - Add a friend in chat list\n[ %-8s ] - List of friends in chat list\n[ %-8s ] - Chat with your friends in list\n[ %-8s ] - Group message to all friends in list\n[ %-8s ] - Share file with your friends [FTP]\n","help","login","logout","reg","exit","add","list","chat","gchat","ftp");
      //printf("\n[ %-8s ] - Information about commands to be used\n[ %-8s ] - User can login\n[ %-8s ] - User can logout\n[ %-8s ] - Login registration\n[ %-8s ] - To end process\n[ %-8s ] - Add a friend in chat list\n[ %-8s ] - List of friends in chat list\n[ %-8s ] - Chat with your friends in list\n","help","login","logout","reg","exit","add","list","chat");
    }
    else if(!strcmp(cmd,"login"))
    {
      if(strcmp(usr,"guest"))
        printf("\n You need to logout first..........\n");
      else
      {
        userLogin(sockFd,usr);
        if(strcmp(usr,"guest"))
        {
          pthread_create(&updtListThread,NULL,updateFriendsList,(void *)NULL);
          pthread_create(&chatThread,NULL,chatWithFriends,(void *)NULL);
          createSenderUDPSocket();
          pthread_create(&serverFTPThread,NULL,serverFTPFunction,(void *)NULL);
        }
      }
    }
    else if(!strcmp(cmd,"add") && strcmp(usr,"guest"))
    {
      char ausr[15];
      while(1)
      {
        printf("\nEnter Friend User Name: ");
        __fpurge(stdin);
        scanf("%[^\n]s",ausr);
        if(strlen(ausr) >= 15)
          continue;
        else 
          break;
      }
      if(strcmp(usr,ausr))
        addFriend(sockFd,usr,ausr);
      else
        printf("\nYourself can't add into friend list\n");
    }
    else if(!strcmp(cmd,"list") && strcmp(usr,"guest"))
    {
      //memset(fList,0,sizeof(fList));
      //friendsContactList(sockFd,usr,(frnd_t *)fList);
      displayFriendsList(fList);
    }
    else if(!strcmp(cmd,"logout") && strcmp(usr,"guest"))
    {
      pthread_cancel(updtListThread);
      pthread_cancel(chatThread);
      pthread_cancel(serverFTPThread);
      if(cnt == 1)
      {
        cnt=0;
        close(cSockFd); 
        close(sSockFd); 
        close(serFTPSockFd); 
      }
      userLogout(sockFd,usr);
    }
    else if(!strcmp(cmd,"reg") && !strcmp(usr,"guest"))
      userRegistration(sockFd);
    else if(!strcmp(cmd,"chat") && strcmp(usr,"guest"))
    {
      int kk,f;
      f=0;
      memset(fusr,0,sizeof(fusr));
      printf("To (Friend username): ");
      __fpurge(stdin);
      scanf("%[^\n]s",fusr);
      for(kk=0;kk<100 && fList[kk].id != 0;kk++)
      {
        if(!strcmp(fusr,fList[kk].userName))
        {
          if(fList[kk].status != (short int)LOGOUT)
          {
            memset(&cCliAdr,0,sizeof(cCliAdr));
            //printf("\n-------send---- %d",fList[kk].uport);
            cCliAdr.sin_family=AF_INET;
            cCliAdr.sin_addr.s_addr=inet_addr(fList[kk].ip);
            cCliAdr.sin_port=htons(fList[kk].uport);
            
            memset(tMsg,0,sizeof(tMsg));
            printf("Enter Message: ");
            __fpurge(stdin);
            scanf("%[^\n]s",tMsg);
            memset(buff,0,sizeof(buff));
            sprintf(buff,"%-15s : %s",usr,tMsg); 
            //printf("\n%s",buff);
            memset(txMsg,0,sizeof(txMsg));
            cReq = (short int)CHAT;
            memcpy(txMsg,&cReq,sizeof(cReq));
            sln = sizeof(cReq)+1;
            strcpy(txMsg+sln,buff);
            sln += strlen(buff)+1;
            if(sendto(cSockFd,txMsg,sln,0,(struct sockaddr *)&cCliAdr,sizeof(cCliAdr)) != sln)
              errMessage("UDP send message error\n"); 
            FILE *fp;
            fp=fopen("./temp.txt","a");
            time(&now);
            memset(iTime,0,sizeof(iTime));
            strcpy(iTime,ctime(&now));
            iTime[strlen(iTime)-1] = 0;
            fprintf(fp,"SEND TO : %-18s (IP)|%d (PORT)|%-28s|%s\n",inet_ntoa(cCliAdr.sin_addr),ntohs(cCliAdr.sin_port),iTime,buff); 
            fclose(fp);
            f=1;
          }
          else
          {
            FILE *fp;
            fp=fopen("./temp.txt","a");
            time(&now);
            memset(iTime,0,sizeof(iTime));
            strcpy(iTime,ctime(&now));
            iTime[strlen(iTime)-1] = 0;
            fprintf(fp,"SENDFAIL: %-15s (Sender)|%-15s (Receiver)|%-28s|Receiver is In-Active\n",usr,fusr,iTime); 
            fclose(fp);
            f=1;
            printf("\nUsername '%s' is not logged in",fusr);
          }
          break;
        }
      }
      if(f == 0)
        printf("\n Username '%s', not exist, you need to add in friends list",fusr);
    }
    else if(!strcmp(cmd,"gchat") && strcmp(usr,"guest"))
    {
      int kk,f;
      if(fList[0].id != 0)
      {
        memset(tMsg,0,sizeof(tMsg));
        printf("Enter Message: ");
        __fpurge(stdin);
        scanf("%[^\n]s",tMsg);
        memset(buff,0,sizeof(buff));
        sprintf(buff,"%-15s : %s",usr,tMsg); 
        //printf("\n%s",buff);
        memset(txMsg,0,sizeof(txMsg));
        cReq = (short int)CHAT;
        memcpy(txMsg,&cReq,sizeof(cReq));
        sln = sizeof(cReq)+1;
        strcpy(txMsg+sln,buff);
        sln += strlen(buff)+1;
        for(kk=0;kk<100 && fList[kk].id != 0;kk++)
        {
          if(fList[kk].status != (short int)LOGOUT)
          {
            memset(&cCliAdr,0,sizeof(cCliAdr));
            //printf("\n-------send---- %d",fList[kk].uport);
            cCliAdr.sin_family=AF_INET;
            cCliAdr.sin_addr.s_addr=inet_addr(fList[kk].ip);
            cCliAdr.sin_port=htons(fList[kk].uport);
            if(sendto(cSockFd,txMsg,sln,0,(struct sockaddr *)&cCliAdr,sizeof(cCliAdr)) != sln)
              errMessage("UDP send message error\n"); 
            FILE *fp;
            fp=fopen("./temp.txt","a");
            time(&now);
            memset(iTime,0,sizeof(iTime));
            strcpy(iTime,ctime(&now));
            iTime[strlen(iTime)-1] = 0;
            fprintf(fp,"GROUPMSG: %-18s (IP)|%d (PORT)|%-28s|%s\n",inet_ntoa(cCliAdr.sin_addr),ntohs(cCliAdr.sin_port),iTime,buff); 
            fclose(fp);
          }
        }
      }
      else
        printf("\n Username '%s', friends list is empty you need to add",usr);
    }
    else if(!strcmp(cmd,"ftp") && strcmp(usr,"guest"))
    {
      memset(fileName,0,sizeof(fileName));
      printf("Enter File Name (With Extension): ");
      __fpurge(stdin);
      scanf("%[^\n]s",fileName);
  
      memset(pathFile,0,sizeof(pathFile));
      sprintf(pathFile,"%s/%s",getFolder,fileName);
      //printf("\n%s",pathFile);

      tfd = open(pathFile,O_RDONLY);
      if(tfd < 0)
        printf("\nFile '%s' doesn't exist",fileName);
      else
      {
        memset(fusr,0,sizeof(fusr));
        printf("To (Friend username): ");
        __fpurge(stdin);
        scanf("%[^\n]s",fusr);
        pthread_create(&clientFTPThread,NULL,clientFTPFunction,(void *)fusr);
      }
    }
    else if(!strcmp(cmd,"exit"))
    {
      char pkt[10];
      short int req;
      int len;
      if(strcmp(usr,"guest"))
      {
        pthread_cancel(updtListThread);
        pthread_cancel(chatThread);
        pthread_cancel(serverFTPThread);
        if(cnt == 1)
        {
          cnt=0;
          close(cSockFd); 
          close(sSockFd); 
          close(serFTPSockFd); 
        }
        userLogout(sockFd,usr); 
      }
      req = (short int) EXT;
      memset(pkt,0,sizeof(pkt));
      memcpy(pkt,&req,sizeof(req));
      len=sizeof(req)+1;
      if(send(sockFd,pkt,len,0) != len)
        errMessage("Exit status error\n");
      break;
    }
    else
    {
      //sleep(3);
      printf("\nCommand Doesn't Exist, for some commands you need to login/logout\nTo know more use 'help' command\n");
    }
  }
  printf("\nClient Is Shutting Down...........\nClient Ended.\n");
  close(sockFd);
}

void *serverFTPFunction(void *arg)
{
  if((serFTPSockFd=socket(AF_INET,SOCK_STREAM,0))<0)
    errMessage("Can't Open Server FTP STREAM Socket\n");

  while(1)
  {
    if(fList[0].id != 0)
    {
      memset(&ftpSrvAdr,0,sizeof(ftpSrvAdr));
      ftpSrvAdr.sin_family=AF_INET;
      ftpSrvAdr.sin_addr.s_addr=htonl(INADDR_ANY);
      ftpSrvAdr.sin_port=htons((unsigned short int)(fList[0].mprt+1000));
      break;
    }
  }

  if(bind(serFTPSockFd,(struct sockaddr*)&ftpSrvAdr,sizeof(ftpSrvAdr))<0)
    errMessage("Can't BIND FTP Local Address\n");

  listen(serFTPSockFd,5);

  while(1)
  {
    memset(&ftpCliAdr,0,sizeof(ftpCliAdr));
    //printf("Server Waiting For FTP New Connection:\n");
    cliLen=sizeof(ftpCliAdr);
    newSerFTPSockFd=accept(serFTPSockFd,(struct sockaddr*)&ftpCliAdr,&cliLen);
    if(newSerFTPSockFd<0)
      errMessage("FTP Accept Error\n");
    //printf("\nConnected Client IP: %s and Port No: %d\n\n",inet_ntoa(ftpCliAdr.sin_addr),ntohs(ftpCliAdr.sin_port));
    memset(&ftpCliAdr1,0,sizeof(ftpCliAdr1));
    ftpCliAdr1 = ftpCliAdr;
    pthread_create(&subServerFTPThread,NULL,serverFTPThreadFunction,(void *)newSerFTPSockFd);
  }
}

void *serverFTPThreadFunction(void *arg)
{
  int n, freq,tlen;
  int ftpSck = (int) arg;
  char fBuff[PKT_LEN],rPath[200];

  pthread_detach(pthread_self());

  memset(fBuff,0,sizeof(fBuff));
  n = recv(ftpSck,fBuff,PKT_LEN,0);
  if(n < 0)
  {
    printf("FTP, initial file receive error\n");
    return;
  }

  memcpy(&freq,fBuff,sizeof(freq));
  tlen=sizeof(freq)+1;
  if(freq == (short int)FILEREQ)
  {
    int num;
    num = (rand()%2);
    if(num == 1)
    {
      int fpt;
      //char dwnFile[100];
      //memset(dwnFile,0,sizeof(dwnFile));
      memset(rPath,0,sizeof(rPath));
      sprintf(rPath,"%s/%s",dwnFolder,(fBuff+tlen));
      //printf("\n-----Create File-------- %s",rPath);

      fpt = open(rPath,O_WRONLY|O_CREAT|O_TRUNC,0777);
      
      while(1)
      {
        memset(fBuff,0,sizeof(fBuff));
        freq = (short int)SUCCESS;
        tlen = sizeof(freq)+1;
        send(ftpSck,fBuff,tlen,0);

        memset(fBuff,0,sizeof(fBuff));
        n = recv(ftpSck,fBuff,PKT_LEN,0);
        //printf("\n nlen: %d",n); 
        memcpy(&freq,fBuff,sizeof(freq));
        if(freq == (short int)FIN)
        {
          close(fpt);
          break;
        }
        write(fpt,fBuff,n);
      }
    }
    else
    {
      memset(fBuff,0,sizeof(fBuff));
      freq = (short int)ERROR;
      tlen = sizeof(freq)+1;
      send(ftpSck,fBuff,tlen,0);
    }
  }
  close(ftpSck);
}

void *clientFTPFunction(void *arg)
{
  int cliFTPSockFd;
  struct sockaddr_in 	ftpAdr;
  int kk,f,fdt,freq,flen,rl;
  char fPkt[PKT_LEN],tfile[100],path[100];
  FILE *fp;
  fdt = tfd;
  f=0;
  
  pthread_detach(pthread_self());

  strcpy(tfile,fileName);
  strcpy(path,pathFile);

  if((cliFTPSockFd=socket(AF_INET,SOCK_STREAM,0))<0)
    errMessage("Can't Open client FTP STREAM Socket\n");

  //printf("\n---------------- %s",tfile);
  for(kk=0;kk<100 && fList[kk].id != 0;kk++)
  {
    if(!strcmp(arg,fList[kk].userName))
    {
      if(fList[kk].status != (short int)LOGOUT)
      {
        memset(&ftpAdr,0,sizeof(ftpAdr));
        //printf("\n-------send---- %d",fList[kk].uport);
        ftpAdr.sin_family=AF_INET;
        ftpAdr.sin_addr.s_addr=inet_addr(fList[kk].ip);
        ftpAdr.sin_port=htons((unsigned short int)(fList[kk].uport+1000));

        if(connect(cliFTPSockFd,(struct sockaddr*)&ftpAdr,sizeof(ftpAdr))<0)
        {
          printf("Can't Connect To FTP Server\n");
          return;
        }
            
        memset(fPkt,0,sizeof(fPkt));
        freq = (short int)FILEREQ;
        memcpy(fPkt,&freq,sizeof(freq));
        flen = sizeof(freq)+1;
        strcpy(fPkt+flen,tfile);
        flen +=strlen(tfile)+1;
        
        if(send(cliFTPSockFd,fPkt,flen,0) != flen)
        {
          printf("FTP, initial file transfer error\n");
          return;
        }

        memset(fPkt,0,sizeof(fPkt));
        rl = recv(cliFTPSockFd,fPkt,PKT_LEN,0);
        if(rl < 0)
        {
          printf("FTP, ACK file transfer error\n");
          return;
        }
    
        memcpy(&freq,fPkt,sizeof(freq));
        if(freq == (short int)SUCCESS)
        {
          int nlen;
          while(1)
          {
             memset(fPkt,0,sizeof(fPkt));
             nlen = read(fdt,fPkt,READLEN);
             if(nlen ==  0)
             {
               memset(fPkt,0,sizeof(fPkt));
               freq = (short int)FIN;
               memcpy(fPkt,&freq,sizeof(freq));
               flen = sizeof(freq)+1;
               send(cliFTPSockFd,fPkt,flen,0);
               close(fdt);
               break;
             }
             
             send(cliFTPSockFd,fPkt,nlen,0);
             //printf("\n nlen: %d",nlen); 
             memset(fPkt,0,sizeof(fPkt));
             recv(cliFTPSockFd,fPkt,PKT_LEN,0);
          }
          f=1;
        }
        else if(freq == (short int)ERROR)
        {
          f=2;
        } 
      }
      else
      {
        fp=fopen("./temp.txt","a");
        time(&now);
        memset(iTime,0,sizeof(iTime));
        strcpy(iTime,ctime(&now));
        iTime[strlen(iTime)-1] = 0;
        fprintf(fp,"FTP FAIL: %-15s (Sender)|%-15s (Receiver)|%s|%-28s|Receiver is In-Active\n",usr,arg,tfile,iTime); 
        fclose(fp);
        f=1;
        printf("\nUsername '%s' is not logged in",fusr);
        printf("\n");
      }
      break;
    }
  }

  fp=fopen("./temp.txt","a");
  time(&now);
  memset(iTime,0,sizeof(iTime));
  strcpy(iTime,ctime(&now));
  iTime[strlen(iTime)-1] = 0;

  if(f == 1)
    fprintf(fp,"FTPTRNSF: %-18s (IP)|%d (PORT)|%-28s|File '%s' Accepted\n",inet_ntoa(ftpAdr.sin_addr),ntohs(ftpAdr.sin_port),iTime,tfile); 
  else if(f == 2)
    fprintf(fp,"FTPTRNSF: %-18s (IP)|%d (PORT)|%-28s|File '%s' Rejected\n",inet_ntoa(ftpAdr.sin_addr),ntohs(ftpAdr.sin_port),iTime,tfile); 
  else if(f == 0)
    printf("\n Username '%s', not exist, you need to add in friends list",fusr);
  
  fclose(fp);
  close(cliFTPSockFd);
}

void *chatWithFriends(void *arg)
{
  while(1)
  {
    if(fList[0].id != 0)
    {
      //printf("---------------recv--------: %d\n",fList[0].mprt);

      if((sSockFd = socket(AF_INET,SOCK_DGRAM,0)) < 0)
        errMessage("Can't open datagram socket\n");

      memset(&cSrvAdr,0,sizeof(cSrvAdr));
      cSrvAdr.sin_family=AF_INET;
      cSrvAdr.sin_addr.s_addr=htonl(INADDR_ANY);
      cSrvAdr.sin_port=htons(fList[0].mprt);
  
      if(bind(sSockFd,(struct sockaddr *)&cSrvAdr,sizeof(cSrvAdr)) < 0)
        errMessage("can't bind UDP local address\n"); 
      cnt = 1;
      //printf("datagram socket created\n");
      break;
    }
  }
  while(1)
  {
    FILE *fp;
    int rlen,cLen;
    short int rReq;
    memset(&tcCliAdr,0,sizeof(tcCliAdr));
    memset(rxMsg,0,sizeof(rxMsg));
    rlen = sizeof(tcCliAdr);
    cN=recvfrom(sSockFd,rxMsg,PKT_LEN,0,(struct sockaddr *)&tcCliAdr,&rlen);
    if(cN < 0)
      errMessage("UDP receive error\n");
    memcpy(&rReq,rxMsg,sizeof(rReq));
    cLen = sizeof(rReq)+1;
    if(rReq == (short int) CHAT)
    {
      printf("\n%s",(rxMsg+cLen));
      fp=fopen("./temp.txt","a");
      time(&now);
      memset(iTime,0,sizeof(iTime));
      strcpy(iTime,ctime(&now));
      iTime[strlen(iTime)-1] = 0;
      fprintf(fp,"RECV FRM: %-18s (IP)|%d (PORT)|%-28s|%s\n",inet_ntoa(tcCliAdr.sin_addr),ntohs(tcCliAdr.sin_port),iTime,(rxMsg+cLen)); 
      fclose(fp);
      printf("\n");
    }
  }
}

void *updateFriendsList(void *arg)
{
  while(1)
  {
    alarm(1);
    sleep(15);
  }
}

void displayFriendsList(frnd_t *fList)
{
  int ii;
  printf("\nUser '%s' Friend List",usr);
  printf("\n--------------------------------------");
  for(ii=0;ii<100 && fList[ii].id != 0;ii++)
  {
    printf("\n%-3d | %-15s | ",(ii+1),fList[ii].userName,fList[ii].ip,fList[ii].port);
    if(fList[ii].status == (short int)LOGOUT)
      printf("[%-9s]","In Active");
    else if(fList[ii].status == (short int)LOGIN)
      printf("[%-9s]","Active");
    else if(fList[ii].status == (short int)IDLE)
      printf("[%-9s]","Idle");
  }
  if(ii == 0)
    printf("\nEmpty Friend List");
  printf("\n--------------------------------------\n");
}

void initialProcess(void)
{
  int fd;
  fd = open("./temp.txt",O_WRONLY|O_CREAT|O_TRUNC,0777);
  close(fd);
}

void createSenderUDPSocket()
{
  if((cSockFd = socket(AF_INET,SOCK_DGRAM,0)) < 0)
    errMessage("Can't open chat datagram socket\n");
}

