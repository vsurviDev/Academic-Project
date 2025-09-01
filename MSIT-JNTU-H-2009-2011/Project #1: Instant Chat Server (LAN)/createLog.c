#include "im.h"
extern char logFile[];
void createLogFile(usr_t u)
{
  FILE *fp;
  char fname[50];
  sprintf(fname,"%s%sLog.txt",logFile,u.userName);
  //printf("\nfile name is: %s",fname);
  fp = fopen(fname,"a");
  if(u.status == (short int)LOGIN)
    fprintf(fp,"LOGIN\t: %-5d|%-15s|%-18s|%-10d(TCP Port)|%-10d(UDP Port)|%-28s|%-28s(Prev Logout)\n",u.id,u.userName,u.ip,u.port,u.uport,u.inTime,u.outTime);
  else
    fprintf(fp,"LOGOUT\t: %-5d|%-15s|%-18s|%-10d(TCP Port)|%-10d(UDP Port)|%-28s|%-28s\n",u.id,u.userName,u.ip,u.port,u.uport,u.inTime,u.outTime);

  fclose(fp);
}
