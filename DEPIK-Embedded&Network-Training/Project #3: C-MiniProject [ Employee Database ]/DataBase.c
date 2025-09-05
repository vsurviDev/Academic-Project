			/* Data Base Program */
#include "Header.h"

int addDataBase(char *reqMsg,char *resMsg)
{
  int ix=1;
  emp_t r;
  memcpy(&r.id,reqMsg+ix,sizeof(int));
  ix+=sizeof(int);
  strcpy(r.name,reqMsg+ix);
  ix+=(strlen(r.name)+1);
  if(strlen(r.name)>30)
  {
    resMsg[0]=MSG_TOO_LONG;
    return;
  }
  strcpy(r.phno,reqMsg+ix);
  if(strlen(r.phno)>13)
  {
    resMsg[0]=MSG_TOO_LONG;
    return;
  }
  ix+=(strlen(r.phno)+1);
  strcpy(r.addr,reqMsg+ix);
  ix+=(strlen(r.addr)+1);
  if(strlen(r.addr)>30)
  {
    resMsg[0]=MSG_TOO_LONG;
    return;
  }
  memcpy(&r.sal,reqMsg+ix,sizeof(int));
  insertEmpDet(&r,&resMsg[0]);
}

int insertEmpDet(emp_t *pR,char *resMsg)
{
  dB_t *pTemp,*pTrv;
  pTemp=(dB_t *) malloc(sizeof(dB_t));
  pTemp->r=*pR;
  hix=hashFun(pR->id);
  if(hix<MAX_HASH)
  {
    pTrv=hash[hix];
    if(pTrv=='\0')
    {
      pTemp->pNext=pTrv;
      hash[hix]=pTemp;
      resMsg[0]=SUCCESS;
      cnt++;
      return;
    }
    else
    {
      while(pTrv)
      {
        if(pTrv->pNext=='\0')
        {
          pTemp->pNext=pTrv->pNext;
          pTrv->pNext=pTemp;
          resMsg[0]=SUCCESS;
          cnt++;
          return;
        }
        pTrv=pTrv->pNext;
      }
    }
  }
  resMsg[0]=DET_NOT_INSERTED;
  return;
}

int delDataBase(char *reqMsg,char *resMsg)
{
  int id;
  memcpy(&id,reqMsg+1,sizeof(int));
  deleteEmpDet(id,&resMsg[0]);
}

int deleteEmpDet(int id,char *resMsg)
{
  dB_t *pTrv,*pFree;
  hix=hashFun(id);
  pTrv=hash[hix];
  if(pTrv=='\0')
  {
    resMsg[0]=ID_NOT_FOUND;
    return;
  }
  else if(pTrv->r.id==id)
  {
    pFree=pTrv;
    hash[hix]=pTrv->pNext;
    free(pFree);
    resMsg[0]=SUCCESS;
    cnt--;
    return;
  }
  else
  {
    while(pTrv)
    {
      if(pTrv->pNext->r.id==id)
      {
        pFree=pTrv->pNext;
        pTrv->pNext=pTrv->pNext->pNext;
        free(pFree);
        resMsg[0]=SUCCESS;
        cnt--;
        return;
      }
      pTrv=pTrv->pNext;
    }
  }
  resMsg[0]=ID_NOT_FOUND;
  return;
}


int getDataBase(char *reqMsg,char *resMsg)
{
  int id;
  memcpy(&id,reqMsg+1,sizeof(int));
  getEmpDet(id,&resMsg[0]);
}

int getEmpDet(int id,char *resMsg)
{
  dB_t *pTrv;
  int ix=1,ii;
  hix=hashFun(id);
  pTrv=hash[hix];
  if(pTrv=='\0')
  {
    resMsg[0]=ID_NOT_FOUND;
    return;
  }
  while(pTrv)
  {
    if(pTrv->r.id==id)
    {
      memcpy(resMsg+ix,&pTrv->r.id,sizeof(int));
      ix+=sizeof(int);
      strcpy(resMsg+ix,pTrv->r.name);
      ix+=(strlen(pTrv->r.name)+1);
      strcpy(resMsg+ix,pTrv->r.phno);
      ix+=(strlen(pTrv->r.phno)+1);
      strcpy(resMsg+ix,pTrv->r.addr);
      ix+=(strlen(pTrv->r.addr)+1);
      memcpy(resMsg+ix,&pTrv->r.sal,sizeof(int));
      resMsg[0]=SUCCESS;
      return;
    }
    pTrv=pTrv->pNext;
  }
  resMsg[0]=ID_NOT_FOUND;
  return;
}

int modDataBase(char *reqMsg,char *resMsg)
{
  int ix=1;
  dB_t *pTrv;
  emp_t r;
  switch(reqMsg[5])
  {
    case NAM:
      memcpy(&r.id,reqMsg+ix,sizeof(int));
      ix+=(sizeof(int)+1);
      strcpy(r.name,reqMsg+ix);
      hix=hashFun(r.id);
      pTrv=hash[hix];
      while(pTrv)
      {
        if(pTrv->r.id==r.id)
        {
           strcpy(pTrv->r.name,r.name);
           resMsg[0]=SUCCESS;
           return;
        }
        pTrv=pTrv->pNext;
      }
      resMsg[0]=ID_NOT_FOUND;
      break;
    case PHN:
      memcpy(&r.id,reqMsg+ix,sizeof(int));
      ix+=(sizeof(int)+1);
      strcpy(r.phno,reqMsg+ix);
      hix=hashFun(r.id);
      pTrv=hash[hix];
      while(pTrv)
      {
        if(pTrv->r.id==r.id)
        {
           strcpy(pTrv->r.phno,r.phno);
           resMsg[0]=SUCCESS;
           return;
        }
        pTrv=pTrv->pNext;
      }
      resMsg[0]=ID_NOT_FOUND;
      break;
    case ADDR:
      memcpy(&r.id,reqMsg+ix,sizeof(int));
      ix+=(sizeof(int)+1);
      strcpy(r.addr,reqMsg+ix);
      hix=hashFun(r.id);
      pTrv=hash[hix];
      while(pTrv)
      {
        if(pTrv->r.id==r.id)
        {
           strcpy(pTrv->r.addr,r.addr);
           resMsg[0]=SUCCESS;
           return;
        }
        pTrv=pTrv->pNext;
      }
      resMsg[0]=ID_NOT_FOUND;
      break;
    case SAL:
      memcpy(&r.id,reqMsg+ix,sizeof(int));
      ix+=(sizeof(int)+1);
      memcpy(&r.sal,reqMsg+ix,sizeof(int));
      hix=hashFun(r.id);
      pTrv=hash[hix];
      while(pTrv)
      {
        if(pTrv->r.id==r.id)
        {
           pTrv->r.sal=r.sal;
           resMsg[0]=SUCCESS;
           return;
        }
        pTrv=pTrv->pNext;
      }
      resMsg[0]=ID_NOT_FOUND;
      break;
    case COM:
      memcpy(&r.id,reqMsg+ix,sizeof(int));
      ix+=(sizeof(int)+1);
      strcpy(r.name,reqMsg+ix);
      ix+=(strlen(reqMsg+ix)+1);
      strcpy(r.phno,reqMsg+ix);
      ix+=(strlen(reqMsg+ix)+1);
      strcpy(r.addr,reqMsg+ix);
      ix+=(strlen(reqMsg+ix)+1);
      memcpy(&r.sal,reqMsg+ix,sizeof(int));
      hix=hashFun(r.id);
      pTrv=hash[hix];
      while(pTrv)
      {
        if(pTrv->r.id==r.id)
        {
           strcpy(pTrv->r.name,r.name);
           strcpy(pTrv->r.phno,r.phno);
           strcpy(pTrv->r.addr,r.addr);
           pTrv->r.sal=r.sal;
           resMsg[0]=SUCCESS;
           return;
        }
        pTrv=pTrv->pNext;
      }
      resMsg[0]=ID_NOT_FOUND;
      break;
    default:
      resMsg[0]=INVALID_COMMAND;
      printf("\n\t\tSend Message To The Server Is ! VALID\n");
  }
}

int disDataBase(char *reqMsg,char *resMsg)
{
  int ii;
  dB_t *pTrv;
  for(ii=0;ii<MAX_HASH;ii++)
  {
    if(hash[ii]!='\0')
    {
      pTrv=hash[ii];
      while(pTrv)
      {
        printf("%-07d%-20s%-10d%-31s%s\n",pTrv->r.id,pTrv->r.name,pTrv->r.sal,pTrv->r.addr,pTrv->r.phno);
        pTrv=pTrv->pNext;
      }
    }
  }
  resMsg[0]=SUCCESS;
}

int hashFun(int id)
{
  int val=0,bm;
  while(id)
  {
    bm=id&0xFF;
    id=id>>8;
    val=val+(bm*2);
  }
  return (val);
}
