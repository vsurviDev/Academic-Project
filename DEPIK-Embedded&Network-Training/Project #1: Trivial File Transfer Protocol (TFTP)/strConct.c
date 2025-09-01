#include "header.h"

void stringConcat(void)
{
  int len,ii=0;
  len=strlen(wFile);

  while(rFile[ii]!='\0')
    wFile[len++]=rFile[ii++];

  wFile[len]='\0';
}
