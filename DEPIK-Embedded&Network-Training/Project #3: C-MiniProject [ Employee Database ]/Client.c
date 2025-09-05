			/* Client Program */
#include "Header.h"
main()
{
  int ch;
  char reqMsg[MAX_MSG],resMsg[MAX_MSG];
  while(1)
  {
    memset(reqMsg,0,MAX_MSG);
    memset(resMsg,0,MAX_MSG);
    printf("\n\t\t\t...::::: Employee MENU :::::...\n\n\t\tEnter '1': To ADD Employee Record\n\t\tEnter '2': To DELETE Employee Record\n\t\tEnter '3': To GET Employee Record\n\t\tEnter '4': To MODIFY Employee Record\n\t\tEnter '5': To DISPLAY All Employee Records\n\t\tEnter '0': To EXIT Program\n\n\t\tEnter U R Choice: ");
    scanf("%d",&ch);
    switch(ch)
    {
      case ADD:
        prepareAddMsg(reqMsg);
        sendMsg(reqMsg,resMsg);
        if(resMsg[0]==SUCCESS)
          printf("\n\t\t..::: Message Stored Successfully :::..\n");
        else if(resMsg[0]==DET_NOT_INSERTED)
          printf("\n\t\t..::: Details Are NOT Stored :::..\n");
        else if(resMsg[0]==INVALID_COMMAND)
          printf("\n\t\t..::: Recieved INVALID Message :::..\n");
        if(resMsg[0]==MSG_TOO_LONG)
          printf("\n\t\t..::: The Given Message Is TOO LONG :::..\n");
        break;
      case DEL:
        if(cnt==0)
          printf("\n\t\t..::: DATA BASE EMPTY :::..\n\n");
        else
        {
          prepareDelMsg(reqMsg);
          sendMsg(reqMsg,resMsg);
          if(resMsg[0]==SUCCESS)
            printf("\n\t\t..::: Message Removed Successfully :::..\n");
          else if(resMsg[0]==ID_NOT_FOUND)
            printf("\n\t\t..::: Given ID Is INVALID :::..\n");
        }
        break;
      case GET:
        if(cnt==0)
          printf("\n\t\t..::: DATA BASE EMPTY :::..\n\n");
        else
        {
          prepareGetMsg(reqMsg);
          printf("\n\t\t..::: Searching Employee Details :::..\n\n");
          printf("\nIDNO   EMP_NAME            EMP_SAL   EMP_ADDRESS                    EMP_PHNO\n");
          printf("--------------------------------------------------------------------------------\n");
          sendMsg(reqMsg,resMsg);
          if(resMsg[0]==SUCCESS)
          {
            displayRespMsg(resMsg);
            printf("--------------------------------------------------------------------------------\n");
            printf("\n\t\t..::: Given ID Details DISPLAYED Successfully :::..\n");
          }
          else if(resMsg[0]==ID_NOT_FOUND)
            printf("\n\t\t..::: Given ID Is INVALID :::..\n");
        }
        break;
      case MOD:
        if(cnt==0)
          printf("\n\t\t..::: DATA BASE EMPTY :::..\n\n");
        else
        {
          prepareModMsg(reqMsg);
          sendMsg(reqMsg,resMsg);
          if(resMsg[0]==SUCCESS)
            printf("\n\t\t..::: Message Modify Successfully :::..\n");
          else if(resMsg[0]==ID_NOT_FOUND)
            printf("\n\t\t..::: Given ID Is INVALID :::..\n");
        }
        break;
      case DIS:
        if(cnt==0)
          printf("\n\t\t..::: DATA BASE EMPTY :::..\n\n");
        else
        {
          reqMsg[0]=DIS;
          printf("\nIDNO   EMP_NAME            EMP_SAL   EMP_ADDRESS                    EMP_PHNO\n");
          printf("--------------------------------------------------------------------------------\n");
          sendMsg(reqMsg,resMsg);
          printf("--------------------------------------------------------------------------------\n");
          if(resMsg[0]==SUCCESS)
            printf("\n\t\t..::: Employee Records DIPLAYED Successfully :::..\n");
        }
        break;
      case EXI:
        exit(1);
        break;
      default:
        printf("\n\t\t! VALID   Please Check MENU Again\n");
        break;
    } 
    printf("\n");   
  }
}

void prepareAddMsg(char *reqMsg)
{
  int ix=0;
  emp_t r;
  memset(&r,0,sizeof(r));
  reqMsg[ix++]=ADD;
  printf("\nEnter Employee ID\t: ");
  scanf("%d",&r.id);
  memcpy(reqMsg+ix,&r.id,sizeof(int));
  ix+=sizeof(int);
  printf("Enter Employee NAME\t: ");
  scanf(" %[^\n]",r.name);
  strcpy(reqMsg+ix,r.name);
  ix+=(strlen(r.name)+1);
  printf("Enter Employee PHONE No\t: ");
  scanf(" %[^\n]",r.phno);
  strcpy(reqMsg+ix,r.phno);
  ix+=(strlen(r.phno)+1);
  printf("Enter Employee ADDRESS\t: ");
  scanf(" %[^\n]",r.addr);
  strcpy(reqMsg+ix,r.addr);
  ix+=(strlen(r.addr)+1);
  printf("Enter Employee SALARY\t: ");
  scanf("%d",&r.sal);
  memcpy(reqMsg+ix,&r.sal,sizeof(int));
}

void prepareDelMsg(char *reqMsg)
{
  int ix=0,id;
  reqMsg[ix++]=DEL;
  printf("\n\t\tEnter Employee ID: ");
  scanf("%d",&id);
  memcpy(reqMsg+ix,&id,sizeof(int));
}

void prepareGetMsg(char *reqMsg)
{
  int ix=0,id;
  reqMsg[ix++]=GET;
  printf("\n\t\tEnter Employee ID: ");
  scanf("%d",&id);
  memcpy(reqMsg+ix,&id,sizeof(int));
}

void displayRespMsg(char *resMsg)
{
  int ix=1;
  emp_t r;
  memset(&r,0,sizeof(r));
  memcpy(&r.id,resMsg+ix,sizeof(int));
  ix+=sizeof(int);
  strcpy(r.name,resMsg+ix);
  ix+=(strlen(r.name)+1);
  strcpy(r.phno,resMsg+ix);
  ix+=(strlen(r.phno)+1);
  strcpy(r.addr,resMsg+ix);
  ix+=(strlen(r.addr)+1);
  memcpy(&r.sal,resMsg+ix,sizeof(int));
  printf("%-07d%-20s%-10d%-31s%s\n",r.id,r.name,r.sal,r.addr,r.phno);
}

void prepareModMsg(char *reqMsg)
{
  int ix=0,n;
  emp_t r;
  memset(&r,0,sizeof(r));
  reqMsg[ix++]=MOD;
  printf("\nEnter Employee ID\t: ");
  scanf("%d",&r.id);
  memcpy(reqMsg+ix,&r.id,sizeof(int));
  ix+=sizeof(int);
  printf("\n\t\t\t...::::: Modify MENU :::::...\n\n\t\tEnter '1': To Modify NAME\n\t\tEnter '2': To Modify PHONE NUMBER\n\t\tEnter '3': To Modify ADDRESS\n\t\tEnter '4': To MODIFY SALARY\n\t\tEnter '5': To MODIFY Complete DATA\n\n\t\tEnter U R Choice: ");
  scanf("%d",&n);
  switch(n)
  { 
    case NAM:
      reqMsg[ix++]=NAM;
      printf("\nEnter New Employee NAME\t: ");
      scanf(" %[^\n]",r.name);
      strcpy(reqMsg+ix,r.name);
      break;
    case PHN:
      reqMsg[ix++]=PHN;
      printf("\nEnter New Employee PHONE No\t: ");
      scanf(" %[^\n]",r.phno);
      strcpy(reqMsg+ix,r.phno);
      break;
    case ADDR:
      reqMsg[ix++]=ADDR;
      printf("\nEnter New Employee ADDRESS\t: ");
      scanf(" %[^\n]",r.addr);
      strcpy(reqMsg+ix,r.addr);
      break;
    case SAL:
      reqMsg[ix++]=SAL;
      printf("\nEnter New Employee SALARY\t: ");
      scanf("%d",&r.sal);
      memcpy(reqMsg+ix,&r.sal,sizeof(int));
      break;
    case COM:
      reqMsg[ix++]=COM;
      printf("\nEnter New Employee NAME\t\t: ");
      scanf(" %[^\n]",r.name);
      strcpy(reqMsg+ix,r.name);
      ix+=(strlen(r.name)+1);
      printf("Enter New Employee PHONE No\t: ");
      scanf(" %[^\n]",r.phno);
      strcpy(reqMsg+ix,r.phno);
      ix+=(strlen(r.phno)+1);
      printf("Enter New Employee ADDRESS\t: ");
      scanf(" %[^\n]",r.addr);
      strcpy(reqMsg+ix,r.addr);
      ix+=(strlen(r.addr)+1);
      printf("Enter New Employee SALARY\t: ");
      scanf("%d",&r.sal);
      memcpy(reqMsg+ix,&r.sal,sizeof(int));
      break;
    default:
      printf("\n\t\t! VALID   Please Check MENU Again\n");
      break;
  }
}
