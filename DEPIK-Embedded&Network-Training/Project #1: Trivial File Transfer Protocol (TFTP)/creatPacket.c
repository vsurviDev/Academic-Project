#include "header.h"

int creatPkt(char *pkt)
{
  int i=2,fp,stat;
  short int req;
  memcpy(&req,pkt,2);
  req=htons(req);
  printf("Enter File Name to Read From or Write To Server: ");
  __fpurge(stdin);
  scanf("%[^\n]",rFile);

  if(req==(short)WRQ)
  {
    t:
    memset(wFile,0,F_SIZE);
    strcpy(wFile,"/tftpboot/");
    stringConcat();
    if((fp=open(wFile,O_RDONLY))<0)
    {
      if((fp=open(wFile,O_WRONLY|O_CREAT,0666))<0)
        errExit("File Not Creat\n");
      printf("Changing The File Permissions.........");
      if(fork()==0)
      {
        execl("/bin/chmod","chmod","0777",wFile,0);   
      }
      wait(&stat);
      printf("\tOK\n");
      memset(wFile,0,F_SIZE);
      close(fp);
    }
    else
    {
      printf("File Already Exist\n");
      memset(rFile,0,F_SIZE);
      printf("Enter File Name To Write: ");
      __fpurge(stdin);
      scanf("%[^\n]",rFile);
      goto t;
    }
  }

  strcpy(pkt+i,rFile);
  i+=strlen(rFile)+1;
  strcpy(pkt+i,"octet");
  i+=strlen(pkt+i)+1;
  return i;
}
