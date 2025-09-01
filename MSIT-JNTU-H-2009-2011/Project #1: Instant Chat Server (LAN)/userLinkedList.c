#include "im.h"

int addUserLL(usr_t u)
{
  uNode_t *pTemp;
  pTemp = malloc(sizeof(uNode_t));
  memset(pTemp,0,sizeof(uNode_t));
  u.ix = 0;
  u.status = (short int)LOGOUT;
  pTemp->usr = u;
  //printf("\n@@@@@@@@@@@@@@@@@@@@");
  if(pHead)
  {
    //printf("\n@@@@@@@@@@@1@@@@@@@@@ %d",idno);
    idno = pTemp->usr.id = idno+1;
    pTemp->usr.uport = (7000+idno);
    pTemp->pNext = pTail->pNext;
    pTail->pNext = pTemp;
    pTail = pTemp; 
  }
  else
  {
  //printf("\n@@@@@@@@@@@@2@@@@@@@@");
    idno= pTemp->usr.id = 1001;
    pTemp->usr.uport = (7000+idno);
    pTemp->pNext = pHead;
    pTail = pHead = pTemp; 
  }
}

int raddUserLL(usr_t u)
{
  uNode_t *pTemp;
  pTemp = malloc(sizeof(uNode_t));
  memset(pTemp,0,sizeof(uNode_t));
  u.status = (short int)LOGOUT;
  pTemp->usr = u;
  //printf("\n@@@@@@@@@@@@@@@@@@@@");
  if(pHead)
  {
  //printf("\n@@@@@@@@@@@1@@@@@@@@@");
    pTemp->pNext = pTail->pNext;
    pTail->pNext = pTemp;
    pTail = pTemp; 
  }
  else
  {
  //printf("\n@@@@@@@@@@@@2@@@@@@@@");
    pTemp->pNext = pHead;
    pTail = pHead = pTemp; 
  }
}
