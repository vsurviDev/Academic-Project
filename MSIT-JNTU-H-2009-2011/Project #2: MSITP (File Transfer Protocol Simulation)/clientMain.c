#include	"header.h"
int 		scFd;
char 		tusr[20],fn[20];
char 		cmd[10];

void errMessage(char *err)
{
  printf("\nError: %s\n",err);
  if(scFd != -1)
    close(scFd);
  exit(0);
}

int main()
{
  int			portNo,rcvLen,sndLen;
  char			pkt[MSG_LEN],srvIp[20];
  struct sockaddr_in	srAddr,clAddr;
  int 			srLen,clLen;
  int 			ch;
  strcpy(usr,gs);
  if((scFd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    errMessage("Socket Stream, Creation Error");
 
  memset(&srAddr,0,sizeof(srAddr));
  srAddr.sin_family		= AF_INET;
  printf("\nEnter Server IP: ");
  while(1)
  {
    scanf("%s",srvIp);
    int cnt = 0,ii;
   
    for(ii=0;ii<strlen(srvIp);ii++)
      if(srvIp[ii] == '.')
        cnt++;
    if(cnt == 3)
      break;
    printf("\nEnter Valid Server IP: ");
  }
  srAddr.sin_addr.s_addr	= inet_addr(srvIp);
  printf("\nEnter Port Number: ");
  while(1)
  {
    scanf("%d",&portNo);
    if(portNo > 5000)
      break;
    printf("\nEnter Valid Port Number > 5000 (Ex: 8001): ");
  }
  srAddr.sin_port		= htons(portNo);

  if(connect(scFd,(struct sockaddr *)&srAddr,sizeof(srAddr)) < 0)
    errMessage("Can't Connect To Server");
  else
    printf("\nConnection Established............"); 
  
  
  while(1)
  {
    memset(cmd,0,sizeof(cmd));

    printf("\n%s> ",usr);
    scanf("%s",cmd);
    
    if(strcmp(cmd,cmdd[0]) == 0)	// to get Help menu
      printf("\nCommands to access this client\n\n[%-6s] - get help menu\n[%-6s] - Full access of the client\n[%-6s] - Come out of the existing user\n[%-6s] - Close the complete client process\n[%-6s] - Get registered\n[%-6s] - Store file in server\n[%-6s] - Get file from server\n[%-6s] - List of the files in current directory\n[%-6s] - Change directory\n[%-6s] - Present directory\n[%-6s] - Creat directory\n[%-6s] - Remove directory or file \n",cmdd[0],cmdd[1],cmdd[2],cmdd[3],cmdd[4],cmdd[5],cmdd[6],cmdd[7],cmdd[8],cmdd[9],cmdd[10],cmdd[11]); 
    else if(strcmp(cmd,cmdd[1]) == 0)	//login process 
    {
      if(strcmp(usr,gs))
        printf("\nAlready logged in  as a \"%s\" user",usr);
      else
      {
        if(userAuthantication() == SUCCESS)
        {
           printf("\nUser Logged In Successfully......\n");
           strcpy(usr,tusr);
        }
        else
           printf("\nLogin error (Check Username or password)\n");
      }
    }
    else if(strcmp(cmd,cmdd[2]) == 0)   //logout process
    {
       if(strcmp(usr,gs))
       {
         if(cmdProcess(cmd) == SUCCESS)
         {
           printf("\nUser Logout Successfully.........\n");
           strcpy(usr,gs);
         }
         else
           printf("\nUser Logout Error........\n");
       }
       else
         printf("\nYou need to login first\n");
    }
    else if(strcmp(cmd,cmdd[7]) == 0 || strcmp(cmd,cmdd[8]) == 0 || strcmp(cmd,cmdd[9]) == 0 || strcmp(cmd,cmdd[10]) == 0 || strcmp(cmd,cmdd[11]) == 0)   //Command Process
    {
       if(strcmp(usr,gs))
       {
         if(cmdProcess(cmd) == SUCCESS)
           printf("\nCommand Successfully Executed.........\n");
         else
           printf("\nCommand Execution Error........\n");
       }
       else
         printf("\nYou need to login first\n");
    }
    else if(strcmp(cmd,cmdd[3]) == 0)  //exit process
      break;
    else if(strcmp(cmd,cmdd[4]) == 0)  //register process
    {
      if(strcmp(usr,gs))
        printf("\nYou need to get logout to get registered\n");
      else
      {
          if(userRegistration() == SUCCESS)
             printf("\nUser Registered Successfully......\n");
          else
             printf("\nUser Registration Error (User Already Exist)\n");
      }
    }
    else if(strcmp(cmd,cmdd[5]) == 0)  //upload process
    {
       if(strcmp(usr,gs))
       {
         if(uplProcess() == SUCCESS)
             printf("\nUser Upload Successfully......\n");
          else
             printf("\nUser Upload Error\n");
       }
       else
         printf("\nYou need to login first\n");
    }
    else if(strcmp(cmd,cmdd[6]) == 0)  //downloadd process
    {
       if(strcmp(usr,gs))
       {
         if(dwlProcess() == SUCCESS)
             printf("\nUser Download Successfully......\n");
          else
             printf("\nUser Download Error\n");
       }
       else
         printf("\nYou need to login first\n");
    }
    else
      printf("\n[%-6s]\t to get commands to process in this client\n",cmdd[0]);
  }
  close(scFd);
}

int uplProcess()
{
  int len;
  short int req;
  memset(pkt,0,sizeof(pkt));
  req = (short)UPL;
  memcpy(pkt,&req,sizeof(req));
  len=createPacket(pkt);
  if(uplProcessPkt(pkt,len) == SUCCESS)
     return SUCCESS;
  else
     return ERROR;
}

int dwlProcess()
{
  int len;
  short int req;
  memset(pkt,0,sizeof(pkt));
  req = (short)DWL;
  memcpy(pkt,&req,sizeof(req));
  len=createPacket(pkt);
  if(dwlProcessPkt(pkt,len) == SUCCESS)
     return SUCCESS;
  else
     return ERROR;
}

int dwlProcessPkt(char *pkt,int len)
{
  int fpw,rcvLen;
  char rMsg[MSG_LEN];
  if(send(scFd,pkt,len,0) != len)
    return ERROR;

  fpw = open(fn,O_WRONLY|O_CREAT,0755);
  
  while(1)
  {
    memset(rMsg,0,sizeof(rMsg));
    rcvLen = recv(scFd,rMsg,MSG_LEN,0);
    if(rcvLen < 0)
      printf("\nReceive Error.....\n");
    
    if(rcvLen == 0)
    {
      close(fpw);
      return SUCCESS;
    }

    write(fpw,rMsg,rcvLen);
  }
  close(fpw);
  return ERROR;
}

int uplProcessPkt(char *pkt,int len)
{
  int fpr,sndLen;
  char sndMsg[MSG_LEN];
  if(send(scFd,pkt,len,0) != len)
    return ERROR;

  if((fpr = open(fn,O_RDONLY)) < 0)
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
      close(fpr);
      return SUCCESS;
    }
     
    if(send(scFd,sndMsg,sndLen,0) != sndLen)
      printf("\nSending Error\n");
  }
  close(fpr);
  return ERROR;
}

int createPacket(char *pkt)
{
   short int req;
   int len=(sizeof(req));
   memcpy(&req,pkt,sizeof(req));
   if(req == (short) DWL)
   {
     len+=sizeof(req)+1;
     file_t fl;
     printf("\nEnter File Name: ");
     __fpurge(stdin);
     scanf("%[^\n]s",fl.flName);
     strcpy(fn,fl.flName);
     /*char temp[100];
     memset(temp,0,sizeof(temp));
     sprintf(temp,"wc -c %s > tm.txt",fl.flName);
     system(temp);
     memset(temp,0,sizeof(temp));
     FILE *fp = fopen("tm.txt","r");
     fgets(temp,sizeof(temp),fp);
     sscanf(temp,"%d %s",&fl.flSize,fn);
     fclose(fp);*/
     strcpy(fl.owner,tusr);
     strcpy(fl.type,"binary");
     fl.status=1;
     memcpy(pkt+len,&fl,sizeof(file_t));
     len+=sizeof(file_t)+1;
   }
   else if(req == (short) UPL)
   {
     len+=sizeof(req)+1;
     file_t fl;
     printf("\nEnter File Name: ");
     __fpurge(stdin);
     scanf("%[^\n]s",fl.flName);
     char temp[100];
     memset(temp,0,sizeof(temp));
     sprintf(temp,"wc -c %s > tm.txt",fl.flName);
     system(temp);
     memset(temp,0,sizeof(temp));
     FILE *fp = fopen("tm.txt","r");
     fgets(temp,sizeof(temp),fp);
     sscanf(temp,"%d %s",&fl.flSize,fn);
     fclose(fp);
     strcpy(fl.owner,tusr);
     strcpy(fl.type,"binary");
     fl.status=0;
     memcpy(pkt+len,&fl,sizeof(file_t));
     len+=sizeof(file_t)+1;
   }
   else if(req == (short) REG)
   {
     usr_t u;
     printf("\nEnter User Name\t: ");
     while(1)
     {
       memset(&u,0,sizeof(usr_t));
       scanf("%s",u.usrName);
       if(strlen(u.usrName) >= 20)
       {
         printf("\nEnter User Name (< 20 characters)\t: ");
         continue;
       }
       break;
     }
     printf("\nEnter Password\t: ");
     while(1)
     {
       scanf("%s",u.passWord);
       if(strlen(u.passWord) >= 10)
       {
	       printf("\nEnter Password (< 10 characters)\t: ");
         continue;
       }
       break;
     }
     printf("\nEnter EmailId\t: ");
     while(1)
     {
       scanf("%s",u.emailID);
       if(strlen(u.emailID) >= 30)
       {
         printf("\nEnter EmailId (< 30 characters)\t: ");
         continue;
       }
       break;
     }
     printf("\nEnter Question\t: ");
     __fpurge(stdin);
     scanf("%[^\n]s",u.secQst);
     __fpurge(stdin);
     printf("\nEnter Answer\t: ");
     scanf("%[^\n]s",u.secAns);
     memcpy(pkt+len,&u,sizeof(usr_t));
     len+=sizeof(usr_t);
   }
   else if(req == (short)ATH)
   {
     usr_t u;
     printf("\nUser Name\t: ");
     while(1)
     {
       memset(&u,0,sizeof(usr_t));
       scanf("%s",u.usrName);
       if(strlen(u.usrName) >= 20)
       {
         printf("\nEnter User Name (< 20 characters)\t: ");
         continue;
       }
       break;
     }
     strcpy(tusr,u.usrName);
     printf("\nPassword\t: ");
     while(1)
     {
       scanf("%s",u.passWord);
       if(strlen(u.passWord) >= 10)
       {
         printf("\nEnter Password (< 10 characters)\t: ");
         continue;
       }
       break;
     }
     memcpy(pkt+len,&u,sizeof(usr_t));
     len+=sizeof(usr_t);
   }
   return len;
}

int userRegistration()
{
  int len;
  short int req;
  memset(pkt,0,sizeof(pkt));
  req = (short)REG;
  memcpy(pkt,&req,sizeof(req));
  len=createPacket(pkt);
  if(processPkt(pkt,len) == SUCCESS)
     return SUCCESS;
  else
     return ERROR;
}

int userAuthantication()
{
  int len;
  short int req;
  memset(pkt,0,sizeof(pkt));
  req = (short)ATH;
  memcpy(pkt,&req,sizeof(req));
  len=createPacket(pkt);
  if(processPkt(pkt,len) == SUCCESS)
     return SUCCESS;
  else
     return ERROR;
}

int cmdProcess(char *cmd)
{
  int len;
  memset(pkt,0,sizeof(pkt));
  len=createPacketCM(pkt,cmd);
  if(processPkt(pkt,len) == SUCCESS)
     return SUCCESS;
  else
     return ERROR;
}

int createPacketCM(char *pkt,char *cmd)
{
  int len;
  short int req;
  req = (short)CMDD;
  memcpy(pkt,&req,sizeof(req));
  len = sizeof(req)+1;
  memcpy(pkt+len,cmd,strlen(cmd));
  len+=(strlen(cmd)+1);
  if(strcmp(cmd,cmdd[2]) == 0)
  {
    memcpy(pkt+len,tusr,strlen(tusr));
    len+=strlen(tusr);
  } 
  else if(strcmp(cmd,cmdd[7]) == 0)
  {
    memcpy(pkt+len,cmd,strlen(cmd));
    len+=strlen(cmd);
  } 
  else if(strcmp(cmd,cmdd[8]) == 0)
  {
    memcpy(pkt+len,cmd,strlen(cmd));
    len+=strlen(cmd)+1;
    char name[10];
    printf("\nEnter Directory Name: ");
    __fpurge(stdin);
    scanf("%[^\n]",name);
    memcpy(pkt+len,name,strlen(name));
    len+=strlen(name)+1;
  } 
  else if(strcmp(cmd,cmdd[9]) == 0)
  {
    memcpy(pkt+len,cmd,strlen(cmd));
    len+=strlen(cmd);
  } 
  else if(strcmp(cmd,cmdd[10]) == 0)
  {
    memcpy(pkt+len,cmd,strlen(cmd));
    len+=strlen(cmd)+1;
    char name[10];
    printf("\nEnter Directory Name: ");
    __fpurge(stdin);
    scanf("%[^\n]",name);
    memcpy(pkt+len,name,strlen(name));
    len+=strlen(name)+1;
  } 
  else if(strcmp(cmd,cmdd[11]) == 0)
  {
    printf("\nremove directory or file\n"); 
  }
  return len;
}

int processPkt(char *pkt,int len)
{
   int ln,ii;
   if(send(scFd,pkt,len,0) != len)
      return ERROR;

   while(1)
   {
     memset(pkt,0,sizeof(pkt));
     if(recv(scFd,pkt,MSG_LEN,0) < 0) 
     {
       printf("\nReceive Error");
       return ERROR;
     }
     else
     {
       short int req;
       memcpy(&req,pkt,sizeof(req));
       if(req == (short) ACK)
       {
         int len = sizeof(req);
         memcpy(&req,pkt+len,sizeof(req));
         if(req == (short) SUCCESS)
           return SUCCESS;
         else
           return ERROR;
       }
       else if(req == (short) MSG)
       {
         int len = sizeof(req)+1;
         char buff[MSG_LEN];
         strcpy(buff,pkt+len);
         printf("%s",buff);
       }
     }
   }
   return ERROR;
}

