#include "im.h"

void userRegistration(int sockFd)
{
  usr_t u;
  char pkt[PKT_LEN];
  short int req;
  int len=0,n;
  char res[100];
  memset(&u,0,sizeof(u));
  while(1)
  {
    printf("\nEnter User Name: ");
    __fpurge(stdin);
    scanf("%[^\n]s",u.userName);
    if(strlen(u.userName) >= 15)
      continue;
    else
    {
      delspaces(u.userName);
      break;
    }
  }
  while(1)
  {
    strcpy(u.passWord,getpass("Enter Password: "));
    //printf("Enter Password: ");
    //__fpurge(stdin);
    //scanf("%[^\n]s",u.passWord);
    if(strlen(u.passWord) >= 15)
      continue;
    else
    {
      delspaces(u.passWord);
      break;
    }
  }
  memset(pkt,0,sizeof(pkt));
  req = (short int) REG;
  memcpy(pkt,&req,sizeof(req));
  len=sizeof(req)+1;
  memcpy(pkt+len,&u,sizeof(u));
  len+=sizeof(u);
  if(send(sockFd,pkt,len,0) != len)
    errMessage("Registration packet sending error\n");   
  memset(pkt,0,sizeof(pkt));
  n=recv(sockFd,pkt,PKT_LEN,0);
  if(n < 0)
    errMessage("ACK Receive error\n");   
  memcpy(&req,pkt,sizeof(req));
  len = sizeof(req)+1;
  if(req == (short int)ACK)
  {
    memset(res,0,sizeof(res));
    strcpy(res,pkt+len);
    printf("%s",res);
  } 
}

void delspaces(char *str)
{
  char str2[15];
  int ii=0,jj=0;
  memset(str2,0,sizeof(str2));
  for(ii=0;str[ii];ii++)
  {
    if(str[ii] != ' ')
    {
      str2[jj++] = str[ii];
    }
  }
  str2[jj]=0;
  memset(str,0,sizeof(str));
  strcpy(str,str2);  
}
