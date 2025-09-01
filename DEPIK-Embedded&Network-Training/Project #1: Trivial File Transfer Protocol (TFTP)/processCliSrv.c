#include "header.h"

void processPkt(char *pkt,int len)
{
  int sockFd,n,newSerlen;
  struct sockaddr_in srvAdr;
  short int req, rq;
  memcpy(&req,pkt,2);
  req=htons(req);

  if((sockFd=socket(AF_INET,SOCK_DGRAM,0))<0)
    errExit("Can't Open DATAGRAM Socket\n");
  
  memset(&srvAdr,0,sizeof(srvAdr));
  srvAdr.sin_family=AF_INET;
  srvAdr.sin_addr.s_addr=inet_addr(TFTP_SER_IP);
  srvAdr.sin_port=htons(TFTP_SER_PORT);

  if(sendto(sockFd,pkt,len,0,
           (struct sockaddr*)&srvAdr,sizeof(srvAdr))!=len)
    errExit("SendTo Error\n");

  memset(&srvAdr,0,sizeof(srvAdr)); 

  if((n=recvfrom(sockFd,pkt,MAX_MSG,0,
                (struct sockaddr *)&srvAdr,&newSerlen))<0)
    errExit("Recive Error\n");

  if(n<MAX_MSG && req==(short)RRQ) 
    flag=1;
  
  if(req == (short)RRQ)
    readFromSer(srvAdr,pkt,n,sockFd);
  else if(req == (short)WRQ)
    writeToSer(srvAdr,pkt,sockFd);
}

void readFromSer(struct sockaddr_in srvAdr,char *pkt,int n,int sockFd)
{
  int fp,newSerlen;
  short int sb,cb=0,req;
  t:
  printf("\nEnter File Name To Write: ");
  __fpurge(stdin);
  scanf("%[^\n]",wFile);

  if((fp=open(wFile,O_RDONLY))<0)
  {
    if((fp=open(wFile,O_CREAT|O_WRONLY|O_APPEND,0666))<0)
      errExit("Error In Opening Client File\n");  
  }
  else
  {
    printf("\tFile Already Exist\n");
    goto t;
  }

  while(1)
  {
    memcpy(&req,pkt,2);
    req=htons(req);
    if(req != DATA)
      errExit("Data Not Received\n");
    memcpy(&sb,pkt+2,2);
    if(cb+1==htons(sb))
    {
      if(write(fp,pkt+4,n-4)<(n-4))
        errExit("Write Error\n");
      cb++;
    }

    if(flag==1)
    {
      flag=0;
      printf("\n\tFile Downloaded Successfully From TFTP Server...\n");
      close(sockFd);
      return;
    }

   memset(pkt,0,MAX_MSG);
   n=createACK(htons(cb),pkt);

   if(sendto(sockFd,pkt,n,0,
            (struct sockaddr*)&srvAdr,sizeof(srvAdr))!=n)
     errExit("SendTo Error\n");

   if((n=recv(sockFd,pkt,MAX_MSG,0))<0)
     errExit("Recive Error\n");

   if(n<MAX_MSG) 
     flag=1;
  }
}

void writeToSer(struct sockaddr_in srvAdr,char *pkt,int sockFd)
{
  int fp,req,ii=0,n=0,newSerlen;
  short int sb,cb=0,tb;
  t:
  printf("Enter File Name: ");
  __fpurge(stdin);
  scanf("%[^\n]",wFile);

  if((fp=open(wFile,O_RDONLY))<0)
  {
    printf("\n\tInvalid, Enter Existed File Name\n");
    goto t;
  }

  while(1)
  {
    memcpy(&req,pkt,2);
    if(htons(req) == (short)ACK)
    {
      if(flag==1)
      {
        flag=0;
        printf("\n\tFile Uploaded Successfully To TFTP Server...\n");
        close(sockFd);
        return;
      }
      memcpy(&sb,pkt+2,2);
       
      if(cb==htons(sb)) 
      {
        ii=0;
        memset(pkt,0,MAX_MSG);
        req=(short)DATA;
        req=htons(req);
        memcpy(pkt,&req,2);
        ii+=2;
        cb++;
        tb=htons(cb);
        memcpy(pkt+ii,&tb,2);
        ii+=2;

        if((n=read(fp,pkt+ii,512))<0)
          errExit("Read Error\n");   
        ii+=n;

        if(n<512)
          flag=1;

        if(sendto(sockFd,pkt,ii,0,
	   	 (struct sockaddr*)&srvAdr,sizeof(srvAdr))!=ii)
          errExit("SendTo Error\n");
        memset(pkt,0,MAX_MSG);
      }

      if((n=recv(sockFd,pkt,MAX_MSG,0))<0)
        errExit("Recive Error\n");
    } 
    else
    {
      printf("\nRequest: %hd\nPacket: %s\n",htons(req),pkt+4);
      errExit("\n\tAcknowledgement Receive Error\n");
    }
  }
}
   
int createACK(short int cb,char *pkt)
{
  short int req;
  int ii=0;
  req=(short int)ACK;
  req=htons(req);
  memcpy(pkt,&req,2);
  ii+=2;
  memcpy(pkt+ii,&cb,2);
  ii+=2;
  return ii;
}
