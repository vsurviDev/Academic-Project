#include "im.h"

void addFriend(int sockFd,char *usr,char *ausr)
{
  usr_t u;
  char pkt[PKT_LEN];
  short int req;
  int len=0,n;
  char res[100];
  time_t now;
  memset(&u,0,sizeof(u));
  strcpy(u.userName,usr);
  strcpy(u.passWord,ausr);
  time(&now);
  strcpy(u.inTime,ctime(&now));
  u.inTime[strlen(u.inTime)-1] = 0;

  memset(pkt,0,sizeof(pkt));
  req = (short int)ADD_FRND;
  memcpy(pkt,&req,sizeof(req));
  len=sizeof(req)+1;
  memcpy(pkt+len,&u,sizeof(u));
  len+=sizeof(u);
  if(send(sockFd,pkt,len,0) != len)
    errMessage("Friend adding packet sending error\n");   
  memset(pkt,0,sizeof(pkt));
  n=recv(sockFd,pkt,PKT_LEN,0);
  if(n < 0)
    errMessage("ACK Receive error\n");   

  memcpy(&req,pkt,sizeof(req));
  len=sizeof(req)+1;
  if(req == (short int)ACK)
  {
    FILE *fp;
    printf("\n%s",pkt+len);
    fp=fopen("./temp.txt","a");
    fprintf(fp,"ADD LIST: %-15s|%-15s|%-28s|%s",u.userName,u.passWord,u.inTime,pkt+len);
    fclose(fp);
  }
}
