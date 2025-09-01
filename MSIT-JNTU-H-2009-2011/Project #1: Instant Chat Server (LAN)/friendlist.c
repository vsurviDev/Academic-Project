#include "im.h"

void friendsContactList(int sockFd,char *usr,frnd_t *fList)
{
  usr_t u;
  frnd_t flst;
  char pkt[PKT_LEN];
  short int req;
  int len=0,n,idx=0;
  char res[100];
  time_t now;
  memset(&u,0,sizeof(u));
  strcpy(u.userName,usr);
  time(&now);
  strcpy(u.inTime,ctime(&now));
  u.inTime[strlen(u.inTime)-1] = 0;

  memset(pkt,0,sizeof(pkt));
  req = (short int)GET_FRND;
  memcpy(pkt,&req,sizeof(req));
  len=sizeof(req)+1;
  memcpy(pkt+len,&u,sizeof(u));
  len+=sizeof(u);
  if(send(sockFd,pkt,len,0) != len)
    errMessage("Get friend packet sending error\n");   

  while(1)
  {
    memset(pkt,0,sizeof(pkt));
    n=recv(sockFd,pkt,PKT_LEN,0);
    if(n < 0)
      errMessage("ACK Receive error\n");   
    memcpy(&req,pkt,sizeof(req));
    len=sizeof(req)+1;
    if(req == (short int)ACK)
    {
      memset(&flst,0,sizeof(flst));
      memcpy(&flst,pkt+len,sizeof(flst));

    /*printf("\n%-3d %-5d|%-15s|%-18s|%-10d\t",idx,flst.id,flst.userName,flst.ip,flst.port);
    if(flst.status == (short int)LOGOUT)
      printf("( %-10s )","In Active");
    else if(flst.status == (short int)LOGIN)
      printf("( %-10s )","Active");
    else if(flst.status == (short int)IDLE)
      printf("( %-10s )","Idle");*/

      fList[idx++] = flst;   
    /*printf("\n%-3d %-5d|%-15s|%-18s|%-10d\t",(idx-1),fList[idx-1].id,fList[idx-1].userName,fList[idx-1].ip,fList[idx-1].port);
    if(fList[idx-1].status == (short int)LOGOUT)
      printf("( %-10s )","In Active");
    else if(fList[idx-1].status == (short int)LOGIN)
      printf("( %-10s )","Active");
    else if(fList[idx-1].status == (short int)IDLE)
      printf("( %-10s )","Idle");*/

    }
    else if(req == (short int)FIN)
    {
      FILE *fp;
      //printf("\n%s",pkt+len);
      fp=fopen("./temp.txt","a");
      fprintf(fp,"GET LIST: %-15s|%-28s|%s",u.userName,u.inTime,pkt+len);
      fclose(fp);
      break;
    }
    if(send(sockFd,pkt,len,0) != len)
      errMessage("Get friend packet sending error\n");   
  }
}
