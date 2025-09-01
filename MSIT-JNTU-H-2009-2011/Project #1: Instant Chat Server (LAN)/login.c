#include "im.h"

void userLogin(int sockFd,char *usr)
{
  usr_t u;
  char pkt[PKT_LEN];
  short int req;
  int len=0,n;
  char res[100],rUsr[15];
  time_t now;
  memset(&u,0,sizeof(u));
  while(1)
  {
    printf("\nUser Name: ");
    __fpurge(stdin);
    scanf("%[^\n]s",u.userName);
    if(strlen(u.userName) >= 15)
      continue;
    else
      break;
  }
  while(1)
  {
    strcpy(u.passWord,getpass("Password: "));
    //printf("Password: ");
    //__fpurge(stdin);
    //scanf("%[^\n]s",u.passWord);
    if(strlen(u.passWord) >= 15)
      continue;
    else
      break;
  }
  time(&now);
  strcpy(u.inTime,ctime(&now));
  u.inTime[strlen(u.inTime)-1] = 0;

  memset(pkt,0,sizeof(pkt));
  req = (short int) LOGIN;
  memcpy(pkt,&req,sizeof(req));
  len=sizeof(req)+1;
  memcpy(pkt+len,&u,sizeof(u));
  len+=sizeof(u);
  if(send(sockFd,pkt,len,0) != len)
    errMessage("Login packet sending error\n");   
  memset(pkt,0,sizeof(pkt));
  n=recv(sockFd,pkt,PKT_LEN,0);
  if(n < 0)
    errMessage("ACK Receive error\n");   

  memcpy(&req,pkt,sizeof(req));
  len=sizeof(req)+1;
  if(req == (short int)ACK)
  {
    memset(rUsr,0,sizeof(rUsr));
    strcpy(rUsr,pkt+len);
    if(!strcmp(rUsr,u.userName))
    {
      len+=strlen(rUsr)+1;
      strcpy(usr,rUsr);
      printf("\n%s",pkt+len);
    } 
    else
      printf("\n%s",pkt+len);
  } 
}
