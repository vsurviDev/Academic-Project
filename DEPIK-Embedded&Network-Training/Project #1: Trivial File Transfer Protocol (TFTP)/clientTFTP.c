#include "header.h"

int main()
{
  int ch,len;
  short int req;
  char pkt[MAX_MSG];
  while(1)
  {
    memset(rFile,0,sizeof(rFile));
    memset(wFile,0,sizeof(wFile));
    printf("\n\t\tTFTP Server Menu\n\t\tEnter '1': DOWNLOAD File From TFTP Server\n\t\tEnter '2': UPLOAD File Into Server\n\t\tEnter '0': EXIT Program\n\n\t\tEnter U R Choice: ");
    scanf("%d",&ch);
    switch(ch)
    {
      case EXT:
        exit(1);
        break;
      case RRQ:
        memset(pkt,0,MAX_MSG);
        req=(short)RRQ;
        req=htons(req);
        memcpy(pkt,&req,2);
        len=creatPkt(pkt);
        processPkt(pkt,len); 
        break;
      case WRQ:
        memset(pkt,0,MAX_MSG);
        req=(short)WRQ;
        req=htons(req);
        memcpy(pkt,&req,2);
        len=creatPkt(pkt);
        processPkt(pkt,len); 
        break;
      default:
        printf("\n\t\tCheck MENU Again\n");
        break;
    }
  }
}
