#include	"header.h"
int nScFd,flag,fflag,fds;
char fln[20];
struct sockaddr_in clAdr;

void signalHandler(int scFd)
{
  if(pHead)
  {
    writeToFile();
    writeToReport();
  }
  printf("\nServer Is Shutting Down...........\nServer Ended.\n");
  close(scFd);
  exit(0);
}

void signalHandler1()
{
  if(pHead)
  {
    printf("\nUpdating Pending Process......");
    writeToFile();
    writeToReport();
    printf("\nPending Process Updated.........");
  }
}

int main()
{
  firstProcess();
  userLL();
  //displayULL();
  signal(SIGINT,signalHandler);
  signal(SIGTSTP,signalHandler);
  signal(SIGALRM,signalHandler1);
  alarm(10);
  serverProcess();
  return;
}

void errMessage(char *err,int scFd)
{
  printf("\nError: %s\n",err);
  if(scFd != -1)
    close(scFd);
  exit(0);
}

void serverProcess()
{
  int			scFd,portNo,rcvLen,sndLen,nCl;
  char			rMsg[MSG_LEN];
  struct sockaddr_in	srAddr,clAddr;
  int 			srLen,clLen,stat;
  fd_set		rfd,tfd;
  
  if((scFd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    errMessage("Socket Stream, Creation Error",scFd);
 
  memset(&srAddr,0,sizeof(srAddr));
  srAddr.sin_family		= AF_INET;
  srAddr.sin_addr.s_addr	= htonl(INADDR_ANY);
  printf("\nEnter Port Number: ");
  while(1)
  {
    scanf("%d",&portNo);
    if(portNo > 5000)
      break;
    printf("\nEnter Valid Port Number > 5000 (Ex: 8001): ");
  }
  srAddr.sin_port		= htons(portNo);

  if(bind(scFd,(struct sockaddr *)&srAddr,sizeof(srAddr)) < 0)
    errMessage("Can't Bind Local Address",scFd);

  printf("\nServer Waiting..., Client To Connect\n");
  
  listen(scFd,5);

  FD_ZERO(&rfd);
  FD_SET(scFd,&rfd);

  while(1)
  {
     tfd = rfd;
     struct timeval t;
     t.tv_sec = 10;
     t.tv_usec = 0;
     stat = select(FD_SETSIZE,&tfd,(fd_set *)0,(fd_set *)0,&t);
     //stat = select(FD_SETSIZE,&tfd,(fd_set *)0,(fd_set *)0,(struct timeval *)0);
     if(stat < 1)
     {
	printf("\nServer Time Out......, No Client Is Active\n");
        continue;
     }
     else
     { 
       for(fds=0;fds<FD_SETSIZE;fds++)
       {
         if(FD_ISSET(fds,&tfd))
         {
           memset(&clAddr,0,sizeof(clAddr));
           if(fds == scFd)
           {
             if((nScFd = accept(scFd,(struct sockaddr *)&clAddr,&clLen)) < 0)
               errMessage("Client Accept",scFd);
             FD_SET(nScFd,&rfd);
             printf("\nConnected Client (%s)\n",inet_ntoa(clAddr.sin_addr));
             clAdr = clAddr;
           }
           else
           {
             struct sockaddr_in clientAddr;
             int ln = sizeof(clientAddr);
             memset(rMsg,0,sizeof(rMsg));
             rcvLen = recv(fds,rMsg,MSG_LEN,0);
             if(rcvLen < 0)
               errMessage("Recieve Message",scFd);       
             else if(rcvLen == 0)
             {
               close(fds);
               FD_CLR(fds,&rfd);
               //printf("\nRemoving Client fds From Read Set fds is : %d\n",fds);
               //printf("\nConnected Client (%s)\n",inet_ntoa(clientAddr.sin_addr));
             }
             else
             {
               sndLen=mainProcess(rMsg);
               if(sndLen != 0)
                 if(send(fds,rMsg,sndLen,0) != sndLen)
                   errMessage("Message Sending",scFd); 	
             }
           }
         }
       }
     }
  }
  close(scFd);
}

int upload(char *pkt,file_t ft)
{
  int fpw,rcvLen;
  char rMsg[MSG_LEN],buff[100],c;
  memset(buff,0,sizeof(buff));
  sprintf(buff,"./%s/%s",ft.owner,ft.flName);
  fpw = open(buff,O_WRONLY|O_CREAT,0755);
  
  while(1)
  {
    memset(rMsg,0,sizeof(rMsg));
    rcvLen = recv(fds,rMsg,MSG_LEN,0);
    if(rcvLen < 0)
      printf("\nReceive Error.....\n");
    
    if(rcvLen == 0)
    {
      memset(pkt,0,MSG_LEN);
      rcvLen=0;
      break;
    }

    write(fpw,rMsg,rcvLen);
  }
  close(fpw);
  return rcvLen;
}

int download(char *pkt,file_t ft)
{
  int fpr,sndLen;
  char sndMsg[MSG_LEN];
  
  if((fpr = open(fln,O_RDONLY)) < 0)
  {
    printf("\nFile Doesn't Exist........");
    return ERROR;
  }

  sleep(2);

  while(1)
  {
    memset(sndMsg,0,sizeof(sndMsg));
    
    if((sndLen = read(fpr,sndMsg,(sizeof(sndMsg)-1))) == 0)
    {
      memset(pkt,0,MSG_LEN);
      sndLen=0;
      break;
    }
     
    if(send(fds,sndMsg,sndLen,0) != sndLen)
      printf("\nSending Error\n");
  }
  close(fpr);
  return sndLen;
}

int mainProcess(char *pkt)
{
  int len,ii;
  short int req;
  memcpy(&req,pkt,sizeof(req));
  len = sizeof(req);
  if(req == (short) DWL)
  {
    len+=3;
    file_t ft;
    memcpy(&ft,pkt+len,sizeof(file_t));
    char temp[100];
    memset(temp,0,sizeof(temp));
    sprintf(temp,"wc -c %s > tm.txt",ft.flName);
    system(temp);
    memset(temp,0,sizeof(temp));
    FILE *fp = fopen("tm.txt","r");
    fgets(temp,sizeof(temp),fp);
    sscanf(temp,"%d %s",&ft.flSize,fln);
    fclose(fp);
    fNode_t *pTrv;
    pTrv = malloc(sizeof(fNode_t));
    pTrv->data = ft;
    if(fH)
    {
      pTrv->pNext = fTl->pNext;
      fTl->pNext = pTrv;
    }
    else
    {
       pTrv->pNext = fH;
       fTfl = fH = fTl = pTrv;
    }
    len=download(pkt,ft);
  }
  else if(req == (short) UPL)
  {
    len+=3;
    file_t ft;
    memcpy(&ft,pkt+len,sizeof(file_t));
    fNode_t *pTrv;
    pTrv = malloc(sizeof(fNode_t));
    pTrv->data = ft;
    if(fH)
    {
      pTrv->pNext = fTl->pNext;
      fTl->pNext = pTrv;
    }
    else
    {
       pTrv->pNext = fH;
       fTfl = fH = fTl = pTrv;
    }
    len=upload(pkt,ft);
  }
  else if(req == (short) CMDD)
  {
    char cm[10];
    len+=1;
    strcpy(cm,pkt+len);
    len+=(strlen(cm)+1);
    if(strcmp(cm,cmdd[10]) == 0)   // Create Directory
    {
       char buff[100];
       char f[100];
       strcpy(f,pkt+len);
       len+=strlen(f)+1;
       strcpy(buff,pkt+len);
       if(mkdir(buff,0755) < 0)
       {
         memset(pkt,0,MSG_LEN);
         req = (short) ACK;
         memcpy(pkt,&req,sizeof(req));
         len=sizeof(req);
         req = (short) ERROR;
         memcpy(pkt+len,&req,sizeof(req));
         len+=sizeof(req);
         return len; 
       }
       memset(pkt,0,MSG_LEN);
       req = (short) ACK;
       memcpy(pkt,&req,sizeof(req));
       len=sizeof(req);
       req = (short) SUCCESS;
       memcpy(pkt+len,&req,sizeof(req));
       len+=sizeof(req);
       return len; 
    }
    else if(strcmp(cm,cmdd[9]) == 0)   // Present Directory
    {
      char buff[500];
      int flg=0;
      system("pwd > tm.txt");
      FILE *fp = fopen("tm.txt","r");
      memset(buff,0,500);
      while(1)
      {
        memset(buff,0,sizeof(buff));
        sleep(2);
        flg=1;
        if(!fgets(buff,MSG_LEN,fp))
           break;
        buff[strlen(buff)]=0;
        req = (short) MSG;
        memset(pkt,0,MSG_LEN);
        memcpy(pkt,&req,sizeof(req));
        len=(sizeof(req)+1);
        memcpy(pkt+len,buff,strlen(buff));
        len+=strlen(buff);

        send(fds,pkt,len,0);
      }
      fclose(fp);
      if(flg == 1)
      {
        memset(pkt,0,MSG_LEN);
        req = (short) ACK;
        memcpy(pkt,&req,sizeof(req));
        len=sizeof(req);
        req = (short) SUCCESS;
        memcpy(pkt+len,&req,sizeof(req));
        len+=sizeof(req);
        return len; 
      }
    }
    else if(strcmp(cm,cmdd[8]) == 0)   // Change Directory
    {
       char buff[100];
       char f[100];
       strcpy(f,pkt+len);
       len+=strlen(f)+1;
       strcpy(buff,pkt+len);
       if(chdir(buff) < 0)
       {
         memset(pkt,0,MSG_LEN);
         req = (short) ACK;
         memcpy(pkt,&req,sizeof(req));
         len=sizeof(req);
         req = (short) ERROR;
         memcpy(pkt+len,&req,sizeof(req));
         len+=sizeof(req);
         return len; 
       }
       memset(pkt,0,MSG_LEN);
       req = (short) ACK;
       memcpy(pkt,&req,sizeof(req));
       len=sizeof(req);
       req = (short) SUCCESS;
       memcpy(pkt+len,&req,sizeof(req));
       len+=sizeof(req);
       return len; 
    }
    if(strcmp(cm,cmdd[7]) == 0)   // list of files
    {
      char buff[MSG_LEN];
      int flag=0;
      system("ls -l  > list.txt");
      FILE *fp = fopen("list.txt","r");
      memset(buff,0,sizeof(buff));
      while(1)
      {
        memset(buff,0,sizeof(buff));
        sleep(2);
        flag=1;
        if(!fgets(buff,MSG_LEN,fp))
           break;
        buff[strlen(buff)]=0;
        req = (short) MSG;
        memset(pkt,0,MSG_LEN);
        memcpy(pkt,&req,sizeof(req));
        len=(sizeof(req)+1);
        memcpy(pkt+len,buff,strlen(buff));
        len+=strlen(buff);

        send(fds,pkt,len,0);
      }
      fclose(fp);
      if(flag == 1)
      {
        memset(pkt,0,MSG_LEN);
        req = (short) ACK;
        memcpy(pkt,&req,sizeof(req));
        len=sizeof(req);
        req = (short) SUCCESS;
        memcpy(pkt+len,&req,sizeof(req));
        len+=sizeof(req);
        return len; 
      }
    }
    else if(strcmp(cm,cmdd[2]) == 0) //logout
    {
      char usrr[20];
      strcpy(usrr,pkt+len);
      len+=strlen(usrr);
      if(strcmp(pH->data.user,usrr) == 0)
      {
        int fd = open(logFile,O_WRONLY|O_APPEND,0755);
        pH->data.status = 0;
        write(fd,&pH->data,sizeof(connNode_t));
        close(fd);
        if(pH == pTl)
          pTl = pH = pH->pNext;
        else
          pH = pH->pNext;
        memset(pkt,0,MSG_LEN);
        req = (short) ACK;
        memcpy(pkt,&req,sizeof(req));
        len=sizeof(req);
        req = (short) SUCCESS;
        memcpy(pkt+len,&req,sizeof(req));
        len+=sizeof(req);
        return len; 
      }
      else
      {
        connNode_t *pTrv,*pT;
        pTrv = pH;
        while(pTrv)
        {
           if(strcmp(pTrv->data.user,usrr) == 0)
           {
             int fd = open(logFile,O_WRONLY|O_APPEND,0755);
             pTrv->data.status = 0;
             write(fd,&pTrv->data,sizeof(connNode_t));
             close(fd);
             pT->pNext = pTrv->pNext;
             free(pTrv);
             memset(pkt,0,MSG_LEN);
             req = (short) ACK;
             memcpy(pkt,&req,sizeof(req));
             len=sizeof(req);
             req = (short) SUCCESS;
             memcpy(pkt+len,&req,sizeof(req));
             len+=sizeof(req);
             return len; 
           }
           pT = pTrv;
           pTrv = pTrv->pNext;
        }
      }
    }
  }
  else if(req == (short) REG)  //Registration
  {
    usr_t u;
    usrNode_t *pT;
    memcpy(&u,pkt+len,sizeof(usr_t));
    pT = pHead;
    while(pT)
    {
      if(strcmp(pT->data.usrName,u.usrName) == 0)
      {
        memset(pkt,0,MSG_LEN);
        req = (short) ACK;
        memcpy(pkt,&req,sizeof(req));
        len=sizeof(req);
        req = (short) ERROR;
        memcpy(pkt+len,&req,sizeof(req));
        len+=sizeof(req);
        return len; 
      }
      pT = pT->pNext;
    } 
    char file[100];
    sprintf(file,"./%s/%s",dir,u.usrName);
    mkdir(file,0755);
    u.status = 1; 
    usrNode_t *pTrv;
    pTrv = malloc(sizeof(usrNode_t));
    pTrv->data = u;
    if(pHead)
    {
      pTrv->pNext = pTail->pNext;
      pTail->pNext = pTrv;
      pTail = pTrv;
    }
    else
    {
       pTrv->pNext = pHead;
       pTfl=pTail=pHead=pTrv;
    }
    //displayULL();
    memset(pkt,0,MSG_LEN);
    req = (short) ACK;
    memcpy(pkt,&req,sizeof(req));
    len=sizeof(req);
    req = (short) SUCCESS;
    memcpy(pkt+len,&req,sizeof(req));
    len+=sizeof(req);
    return len; 
  }
  else if(req == (short)ATH) //Login
  {
    usr_t u;
    usrNode_t *pT;
    memcpy(&u,pkt+len,sizeof(usr_t));
    pT = pHead;
    while(pT)
    {
      if(strcmp(pT->data.usrName,u.usrName) == 0)
      {
        if(strcmp(pT->data.passWord,u.passWord) == 0)
        {
          //chdir(u.usrName);
          pT->data.status=u.status = 1; 
          writeToLog(u);
          memset(pkt,0,MSG_LEN);
          req = (short) ACK;
          memcpy(pkt,&req,sizeof(req));
          len=sizeof(req);
          req = (short) SUCCESS;
          memcpy(pkt+len,&req,sizeof(req));
          len+=sizeof(req);
          return len; 
        }
      }
      pT = pT->pNext;
    } 
  }
  memset(pkt,0,MSG_LEN);
  req = (short) ACK;
  memcpy(pkt,&req,sizeof(req));
  len=sizeof(req);
  req = (short) ERROR;
  memcpy(pkt+len,&req,sizeof(req));
  len+=sizeof(req);
  return len; 
}


void writeToLog(usr_t u)
{
  conn_t cn;
  char buff[500];
  strcpy(cn.user,u.usrName);
  cn.clAddr = clAdr;
  cn.status = u.status;
  system("pwd > tm.txt");
  FILE *fp = fopen("tm.txt","r");
  memset(buff,0,500);
  fgets(buff,sizeof(buff),fp);
  fclose(fp);
  strcpy(cn.curDir,buff);
  connNode_t *pTrv,*pTr;
  pTr = pH;
  int fd = open(logFile,O_WRONLY|O_APPEND,0755);
  while(pTr)
  {
     if(strcmp(pTr->data.user,cn.user) == 0)
     {
       pTr->data = cn;
       write(fd,&cn,sizeof(cn));
     }
     pTr = pTr->pNext;
  } 
  write(fd,&cn,sizeof(cn));
  close(fd);
  pTrv = malloc(sizeof(connNode_t));
  pTrv->data = cn;
  if(pH)
  {
    pTrv->pNext = pTl->pNext;
    pTl->pNext = pTrv;
  }
  else
  {
    pTrv->pNext = pH;
    pH=pTl=pTrv;
  }
}

void writeToReport()
{
  fNode_t *pTrv;
  int fd;
  if(fTfl == fH && fflag == 0)
  {
    fflag = 1;
    if((fd = open(reportFile,O_RDWR|O_CREAT,0775)) < 0)
      printf("\nFILE Open Error\n");

    pTrv = fTfl;
    fTfl = fTl;
    while(pTrv)
    {
        lseek(fd,0,SEEK_END);
        write(fd,&pTrv->data,sizeof(file_t));
        pTrv=pTrv->pNext;
    }       
    close(fd);
  }
  else if(fTfl->pNext)
  {
    if((fd = open(reportFile,O_RDWR|O_CREAT,0775)) < 0)
      printf("\nFILE Open Error\n");

    pTrv = fTfl->pNext;
    fTfl = fTl;
    while(pTrv)
    {
        lseek(fd,0,SEEK_END);
        write(fd,&pTrv->data,sizeof(usr_t));
        pTrv=pTrv->pNext;
    }       
    close(fd);
  }
}

void writeToFile()
{
  usrNode_t *pTrv;
  int fd;
  if(pTfl == pHead && flag == 0)
  {
    flag = 1;
    if((fd = open(usrFile,O_RDWR|O_CREAT,0775)) < 0)
      printf("\nFILE Open Error\n");

    pTrv = pTfl;
    pTfl = pTail;
    while(pTrv)
    {
        lseek(fd,0,SEEK_END);
        write(fd,&pTrv->data,sizeof(usr_t));
        pTrv=pTrv->pNext;
    }       
    close(fd);
  }
  else if(pTfl->pNext)
  {
    if((fd = open(usrFile,O_RDWR|O_CREAT,0775)) < 0)
      printf("\nFILE Open Error\n");

    pTrv = pTfl->pNext;
    pTfl = pTail;
    while(pTrv)
    {
        lseek(fd,0,SEEK_END);
        write(fd,&pTrv->data,sizeof(usr_t));
        pTrv=pTrv->pNext;
    }       
    close(fd);
  }
}

void displayULL()
{
   usrNode_t *pTrv;
   pTrv = pHead;
   while(pTrv)
   {
     printf("%s|%s|%s\n",pTrv->data.usrName,pTrv->data.passWord,pTrv->data.emailID);
     pTrv=pTrv->pNext;
   }
}

void userLL()
{
  int fd;
  usr_t usr;
  if((fd = open(usrFile,O_RDONLY)) < 0)
    printf("\nRead FILE Open Error\n");
  
  memset(&usr,0,sizeof(usr_t));
  while(read(fd,&usr,sizeof(usr_t)) == sizeof(usr_t))
  {
    usrNode_t *pTrv;
    pTrv = (usrNode_t *)malloc(sizeof(usrNode_t));
    pTrv->data = usr;
    if(pHead)
    {
      pTrv->pNext = pTail->pNext;
      pTail->pNext=pTrv;
      pTail=pTfl=pTrv;
    }
    else
    {
      pTrv->pNext = pHead;
      pHead=pTail=pTfl=pTrv;
    }
    memset(&usr,0,sizeof(usr_t));
  }
  close(fd);
}

void firstProcess()
{
  int fd;
  mkdir(dir,0755);
  if(fork() == 0)
    execl("/bin/touch","touch",usrFile,logFile,reportFile,0);
  wait();
}
