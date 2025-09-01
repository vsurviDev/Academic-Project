#include "im.h"

void userLogout(int sockFd,char *usr)
{
  usr_t u;
  char pkt[PKT_LEN];
  short int req;
  int len=0,n;
  char res[100],rUsr[15];
  time_t now;
  finalWriteFile(usr,sockFd);
  memset(&u,0,sizeof(u));
  strcpy(u.userName,usr);
  
  time(&now);
  strcpy(u.outTime,ctime(&now));
  u.outTime[strlen(u.outTime)-1] = 0;

  memset(pkt,0,sizeof(pkt));
  req = (short int) LOGOUT;
  memcpy(pkt,&req,sizeof(req));
  len=sizeof(req)+1;
  memcpy(pkt+len,&u,sizeof(u));
  len+=sizeof(u);
  if(send(sockFd,pkt,len,0) != len)
    errMessage("Logout packet sending error\n");   
  memset(pkt,0,sizeof(pkt));
  n=recv(sockFd,pkt,PKT_LEN,0);
  if(n < 0)
    errMessage("ACK Receive error\n");   

  memcpy(&req,pkt,sizeof(req));
  len=sizeof(req)+1;
  if(req == (short int)ACK)
  {
    strcpy(usr,"guest");
    printf("\n%s",pkt+len);
  } 
}

void finalWriteFile(char *usr,int sockFd)
{
  FILE *fp;
  char pkt[PKT_LEN];
  short int req;
  int len,n;
  fp = fopen("./temp.txt","r");
  if(!fp)
    ;
  else
  {
    char buff[1024];
    memset(buff,0,sizeof(buff));
    while(fgets(buff,sizeof(buff),fp))
    {
      len=0;
      memset(pkt,0,sizeof(pkt));
      req = (short int)FIN;
      memcpy(pkt,&req,sizeof(req));
      len=sizeof(req)+1;
      strcpy(pkt+len,usr);
      len+=strlen(usr)+1;
      strcpy(pkt+len,buff);
      len+=strlen(buff)+1;
      if(send(sockFd,pkt,len,0) != len)
        errMessage("Final packet sending error\n");   
      memset(buff,0,sizeof(buff));
      n=recv(sockFd,pkt,PKT_LEN,0);
      if(n < 0)
        errMessage("ACK Receive error\n");   
    }
    fclose(fp);
  }
  initialProcess();
}
