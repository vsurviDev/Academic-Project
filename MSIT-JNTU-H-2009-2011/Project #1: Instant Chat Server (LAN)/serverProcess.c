#include "im.h"

void registerProcess(char *pkt,int *len)
{
  uNode_t *pTrv;
  int flag = 0;
  short int req;
  usr_t u;
  char res[100];
  //printf("\nRegistration Packet start process, len: %d",(*len));
  memcpy(&u,pkt+(*len),sizeof(u));
  //printf("############# usr: %s and pwd: %s\n",u.userName,u.passWord);
  pTrv=pHead;
  while(pTrv)
  {
    //printf("\n######1######");
    if(strcmp(pTrv->usr.userName,u.userName) == 0)
    {
    //printf("\n######22######");
      flag=1;
      break;
    }
    pTrv=pTrv->pNext;
  }
    //printf("\n######333######");
  memset(res,0,sizeof(res));
  if(flag == 0)
  {
    addUserLL(u);
    sprintf(res,"\nRegistration Success....,\nUsername is: %s\tPassword is: %s\n",u.userName,u.passWord);
  }
  else
    sprintf(res,"\nRegistration Failure...., Username already exist\n");

  memset(pkt,0,PKT_LEN);
  req = (short int)ACK;
  memset(pkt,0,sizeof(pkt));
  memcpy(pkt,&req,sizeof(req));
  (*len)=sizeof(req)+1;
  strcpy(pkt+(*len),res);
  (*len)+=strlen(res);
}

void loginProcess(char *pkt,int *len,struct sockaddr_in cliAdr)
{
  uNode_t *pTrv;
  int flag = 0;
  short int req;
  usr_t u;
  char res[100];
//  printf("\nRegistration Packet start process, len: %d",(*len));
  memcpy(&u,pkt+(*len),sizeof(u));
  //printf("############# usr: %s and pwd: %s\n",u.userName,u.passWord);
  pTrv=pHead;
  while(pTrv)
  {
    //printf("\n######1######");
    if(strcmp(pTrv->usr.userName,u.userName) == 0 && strcmp(pTrv->usr.passWord,u.passWord) == 0)
    {
    //printf("\n######22######");
      strcpy(pTrv->usr.ip,inet_ntoa(cliAdr.sin_addr));
      strcpy(pTrv->usr.inTime,u.inTime);
      pTrv->usr.port = ntohs(cliAdr.sin_port);
      pTrv->usr.status = (short int)LOGIN;
      flag=1;
      u = pTrv->usr;
      break;
    }
    pTrv=pTrv->pNext;
  }
    //printf("\n######333######");
  
  memset(pkt,0,PKT_LEN);
  req = (short int)ACK;
  memset(pkt,0,sizeof(pkt));
  memcpy(pkt,&req,sizeof(req));
  (*len)=sizeof(req)+1;
  memset(res,0,sizeof(res));
  if(flag == 1)
  {
    strcpy(pkt+(*len),u.userName);
    (*len)+=strlen(u.userName)+1;
    sprintf(res,"User '%s' authentication successes....\n",u.userName); 
    createLogFile(u);     
  }
  else
    sprintf(res,"User '%s' authentication Failure....\n",u.userName);
  
  strcpy(pkt+(*len),res);
  (*len)+=strlen(res);
}

void logoutProcess(char *pkt,int *len)
{
  uNode_t *pTrv;
  int flag = 0;
  short int req;
  usr_t u;
  char res[100];
//  printf("\nRegistration Packet start process, len: %d",(*len));
  memcpy(&u,pkt+(*len),sizeof(u));
  //printf("############# usr: %s and pwd: %s\n",u.userName,u.passWord);
  pTrv=pHead;
  while(pTrv)
  {
    //printf("\n######1######");
    if(strcmp(pTrv->usr.userName,u.userName) == 0)
    {
    //printf("\n######22######");
      strcpy(pTrv->usr.outTime,u.outTime);
      pTrv->usr.status = (short int)LOGOUT;
      flag=1;
      u = pTrv->usr;
      break;
    }
    pTrv=pTrv->pNext;
  }
    //printf("\n######333######");
  
  memset(pkt,0,PKT_LEN);
  req = (short int)ACK;
  memset(pkt,0,sizeof(pkt));
  memcpy(pkt,&req,sizeof(req));
  (*len)=sizeof(req)+1;
  memset(res,0,sizeof(res));
  if(flag == 1)
  {
    sprintf(res,"User '%s' logout successes....\n",u.userName); 
    createLogFile(u);     
  }
  
  strcpy(pkt+(*len),res);
  (*len)+=strlen(res);
}

void addFriendProcess(char *pkt,int *len)
{
  uNode_t *pTrv,*pT;
  int flag = 0,id=0;
  short int req;
  usr_t u;
  char res[100];
//  printf("\nRegistration Packet start process, len: %d",(*len));
  memcpy(&u,pkt+(*len),sizeof(u));
  //printf("############# usr: %s and pwd: %s\n",u.userName,u.passWord);
  pT=pHead;
  while(pT)
  {
    if(strcmp(pT->usr.userName,u.passWord) == 0)
    {
      id=pT->usr.id;
      pTrv=pHead;
      while(pTrv)
      {
        //printf("\n######1######");
        if(strcmp(pTrv->usr.userName,u.userName) == 0)
        {
          //printf("\n######22######");
          int ii=0;
          for(ii=0;ii<100 && pTrv->usr.list[ii] != 0;ii++)
          {
            if(pTrv->usr.list[ii] == id)
            {
              flag=2;
              break;
            }
          }
          if(flag != 2)
          {
            pTrv->usr.list[pTrv->usr.ix++] = id;
            flag=1;
          }
          break;
        }
        pTrv=pTrv->pNext;
      }
      break;
    }
    pT=pT->pNext;
  }
    //printf("\n######333######");
  
  memset(pkt,0,PKT_LEN);
  req = (short int)ACK;
  memset(pkt,0,sizeof(pkt));
  memcpy(pkt,&req,sizeof(req));
  (*len)=sizeof(req)+1;
  memset(res,0,sizeof(res));
  if(flag == 1)
    sprintf(res,"Add Username '%s' successes....\n",u.passWord);
  else if(flag == 2)
    sprintf(res,"Add Username '%s' failure...., Already exist\n",u.passWord);
  else 
    sprintf(res,"Add Username '%s' failure...., Doesn't exist\n",u.passWord); 
  
  strcpy(pkt+(*len),res);
  (*len)+=strlen(res);
}

void getFriendProcess(char *pkt,int *len,int sockfd)
{
  uNode_t *pTrv;
  int flag = 0,ii,n;
  short int req;
  usr_t u;
  frnd_t flst;
  char res[100];
  //printf("\nRegistration Packet start process, len: %d",(*len));
  memcpy(&u,pkt+(*len),sizeof(u));
  //printf("############# usr: %s and pwd: \n",u.userName);
  pTrv=pHead;
  while(pTrv)
  {
    //printf("\n######1######");
    if(strcmp(pTrv->usr.userName,u.userName) == 0)
    {
      memset(&u,0,sizeof(u));
      u=pTrv->usr;
      break;
    }
    pTrv=pTrv->pNext;
  }
    //printf("\n######333######");
  for(ii=0;ii<100 && u.list[ii] != 0;ii++)
  {
    pTrv=pHead;
    while(pTrv)
    {
      if(pTrv->usr.id == u.list[ii])
      {
       // printf("%s - %s - %d\n",pTrv->usr.userName,pTrv->usr.ip,pTrv->usr.port);

        memset(pkt,0,PKT_LEN);
        req = (short int)ACK;
        memset(pkt,0,sizeof(pkt));
        memcpy(pkt,&req,sizeof(req));
        (*len)=sizeof(req)+1;
        memset(&flst,0,sizeof(flst));
        flst.id = pTrv->usr.id;
        strcpy(flst.userName,pTrv->usr.userName);
        strcpy(flst.ip,pTrv->usr.ip);
        flst.port = pTrv->usr.port;
        flst.uport = pTrv->usr.uport;
        flst.mprt = u.uport; 
        flst.status = pTrv->usr.status;

//        printf("%s - %s - %d\n",flst.userName,flst.ip,flst.port);

        memcpy(pkt+(*len),&flst,sizeof(flst));
        (*len)+=sizeof(flst)+1;
        if(send(sockfd,pkt,(*len),0) != (*len))
          errMessage("Friend List ACK Error\n");
        n=recv(sockfd,pkt,PKT_LEN,0);
        if(n<0)
          errMessage("Friend List -ACK- Error\n");
        break;
      }
      pTrv=pTrv->pNext;
    }
  }
    //printf("\n######  ######");
  memset(pkt,0,PKT_LEN);
  req = (short int)FIN;
  memset(pkt,0,sizeof(pkt));
  memcpy(pkt,&req,sizeof(req));
  (*len)=sizeof(req)+1;
  memset(res,0,sizeof(res));
  sprintf(res,"User '%s' get list successes....\n",u.userName); 
  strcpy(pkt+(*len),res);
  (*len)+=strlen(res);
}
