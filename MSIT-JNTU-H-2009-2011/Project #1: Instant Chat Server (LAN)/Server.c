/*
 * 	Main Server For Instant Messenger 
 */

#include "im.h" 

void *servClient(void *);
void *updateFile(void *);
void cWriteFile(void);
void freeLL(void);

char dir[] = "usrDataBase",dir2[]="./usrDataBase/usrLogFiles", usrFile[] = "./usrDataBase/usrDetails.bin",logFile[]="./usrDataBase/usrLogFiles/";
struct sockaddr_in 	cliAdr1;

void signalHandler()
{
  cWriteFile();
  if(pHead)
    freeLL();
  printf("\nServer Is Shutting Down...........\nServer Ended.\n");
  exit(0);
}

void signalHandler1()
{
  cWriteFile();
  printf("\nPending Process Updated.........");
  printf("\n");
}

int main()
{
  int 			sockFd,newSockFd;
  struct sockaddr_in 	srvAdr,cliAdr;
  int 			cliLen;
  pthread_t 		srvThread,updtThread;

  //sem_init(&srSemp1,0,0);
  //sem_init(&srSemp2,0,0);

  mkdir(dir,0777);
  mkdir(dir2,0777);
  readFromFile();
  //displayLL(); 

  signal(SIGINT,signalHandler);
  signal(SIGTSTP,signalHandler);
  signal(SIGALRM,signalHandler1);
  
  pthread_create(&updtThread,NULL,updateFile,"\nUpdating Pending Process......");

  if((sockFd=socket(AF_INET,SOCK_STREAM,0))<0)
    errMessage("Can't Open STREAM Socket\n");

  memset(&srvAdr,0,sizeof(srvAdr));
  srvAdr.sin_family=AF_INET;
  srvAdr.sin_addr.s_addr=htonl(INADDR_ANY);
  srvAdr.sin_port=htons(SRV_PORT);

  if(bind(sockFd,(struct sockaddr*)&srvAdr,sizeof(srvAdr))<0)
    errMessage("Can't BIND Local Address\n");

  listen(sockFd,5);

  while(1)
  {
    memset(&cliAdr,0,sizeof(cliAdr));
    printf("Server Waiting For New Connection:\n");
    cliLen=sizeof(cliAdr);
    newSockFd=accept(sockFd,(struct sockaddr*)&cliAdr,&cliLen);
    if(newSockFd<0)
      errMessage("Accept Error\n");
    printf("\nConnected Client IP: %s and Port No: %d\n\n",inet_ntoa(cliAdr.sin_addr),ntohs(cliAdr.sin_port));
    memset(&cliAdr1,0,sizeof(cliAdr1));
    cliAdr1 = cliAdr;
    pthread_create(&srvThread,NULL,servClient,(void *)newSockFd);
  }
}

void *updateFile(void *arg)
{
  while(1)
  {
    sleep(30);
    printf("%s",arg);
    alarm(1);
  }
}

void *servClient(void *arg)
{
  int n;
  int sockfd=(int)arg;
  struct sockaddr_in cliAdr=cliAdr1;
  char pkt[PKT_LEN];
  usr_t u;
  pthread_detach(pthread_self());
  printf("\nServer Waiting, Client to request.........\n");
  while(1)
  {
    short int req;
    int len;
    //usr_t u;
    memset(&req,0,sizeof(req));
    memset(pkt,0,sizeof(pkt));
    //displayLL(); 
    n=recv(sockfd,pkt,PKT_LEN,0);
    if(n < 0)
      return;
    memcpy(&req,pkt,sizeof(req));
    len=sizeof(req)+1;
    if(req == (short int)REG)
    {
      //printf("\nRegistration message received\n");
      //memset(&u,0,sizeof(u));
      //memcpy(&u,pkt+len,sizeof(u));
      //printf("\nusr: %s and pwd: %s,len: %d\n",u.userName,u.passWord,len);
      registerProcess(pkt,&len);
      if(send(sockfd,pkt,len,0) != len)
        errMessage("Registration ACK Error\n");
      //displayLL(); 
    }
    else if(req == (short int)LOGIN)
    {
      //printf("\nLogin message received\n");
      //memset(&u,0,sizeof(u));
      //memcpy(&u,pkt+len,sizeof(u));
      //printf("\nusr: %s and pwd: %s,len: %d, inTime: %s\n",u.userName,u.passWord,len,u.inTime);
      loginProcess(pkt,&len,cliAdr);
      //printf("\n&&&&&&&&&&&&& : %s and %d\n",pkt+3,len);
      if(send(sockfd,pkt,len,0) != len)
        errMessage("Registration ACK Error\n");
    }
    else if(req == (short int)LOGOUT)
    {
      //printf("\nLogout message received\n");
      //memset(&u,0,sizeof(u));
      //memcpy(&u,pkt+len,sizeof(u));
      //printf("\nusr: %s and len: %d, outTime: %s\n",u.userName,len,u.outTime);
      logoutProcess(pkt,&len);
      //printf("\n&&&&&&&&&&&&& : %s and %d\n",pkt+3,len);
      if(send(sockfd,pkt,len,0) != len)
        errMessage("Registration ACK Error\n");
    }
    else if(req == (short int)ADD_FRND)
    {
      //printf("\nAdd friend message received\n");
      //memset(&u,0,sizeof(u));
      //memcpy(&u,pkt+len,sizeof(u));
      //printf("\nusr: %s and friend: %s, len: %d, inTime: %s\n",u.userName,u.passWord,len,u.inTime);
      addFriendProcess(pkt,&len);
      //printf("\n&&&&&&&&&&&&& : %s and %d\n",pkt+3,len);
      if(send(sockfd,pkt,len,0) != len)
        errMessage("Registration ACK Error\n");
      //displayLL(); 
    }
    else if(req == (short int)GET_FRND)
    {
      //printf("\nGet friend message received\n");
      //memset(&u,0,sizeof(u));
      //memcpy(&u,pkt+len,sizeof(u));
      //printf("\nusr: %s and len: %d, inTime: %s\n",u.userName,len,u.inTime);
      getFriendProcess(pkt,&len,sockfd);
      //printf("\n&&&&&&&&&&&&& : %s and %d\n",pkt+3,len);
      if(send(sockfd,pkt,len,0) != len)
        errMessage("Registration ACK Error\n");
      //displayLL(); 
    }
    else if(req == (short int)FIN)
    {
      FILE *fp;
      char fname[50],usr[15];
      memset(fname,0,sizeof(fname));
      memset(usr,0,sizeof(usr));
      //printf("\nFinal message received\n");
      strcpy(usr,pkt+len);
      len+=strlen(usr)+1;
      //printf("\n--------- %s",usr);
      sprintf(fname,"%s%sLog.txt",logFile,usr);
      //printf("\nFile name is: %s",fname);
      fp=fopen(fname,"a");
      fprintf(fp,"%s",pkt+len);
      fclose(fp);
      if(send(sockfd,pkt,len,0) != len)
        errMessage("Registration ACK Error\n");
    }
    else if(req == (short int)EXT)
      break;
  }
  close(sockfd);
}

void readFromFile(void)
{
  int fd,ln;
  usr_t u;
  fd = open(usrFile,O_RDONLY,0777);
  if(fd < 0)
    ;//printf("\n Read File Open Error\n");
  else
  {
    while(1)
    {
      memset(&u,0,sizeof(u));
      ln = read(fd,&u,sizeof(u));
      if(ln != sizeof(u))
        break;
      idno = u.id;
      raddUserLL(u); 
    }
    close(fd);
  }
}

void cWriteFile(void)
{
  int fd;
  uNode_t *pTrv;
  usr_t u;
  
  if(pHead)
  {
    fd = open(usrFile,O_WRONLY|O_CREAT,0777);
    if(fd < 0)
      printf("\n Write File Open Error");
    else
    {
      pTrv = pHead;
      while(pTrv)
      {
        memset(&u,0,sizeof(u));
        u = pTrv->usr;
        //printf("\n%d - %d - %s - %s ",u.id,u.ix,u.userName,u.passWord);
        write(fd,&u,sizeof(u));
        pTrv=pTrv->pNext;
      }
    }
    close(fd);  
  }
}

void displayLL(void)
{
  uNode_t *pTrv;
  pTrv=pHead;
  printf("\n");
  while(pTrv)
  {
    usr_t u;
    u = pTrv->usr;
    printf("\n%d - %d - %s - %s - %s - %d - %s - %s \n",u.id,u.ix,u.userName,u.passWord,u.ip,u.port,u.inTime,u.outTime);
    int ii;
    for(ii=0;ii<100 && u.list[ii] != 0;ii++)
      printf("%d ",u.list[ii]);
    pTrv=pTrv->pNext;
  }
}

void freeLL(void)
{
  uNode_t *pTrv;
  while(pHead)
  {
    pTrv=pHead;
    pHead=pHead->pNext;
    free(pTrv);
  }
}
