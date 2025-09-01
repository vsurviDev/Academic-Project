#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<sys/stat.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include 	<unistd.h>
#include	<fcntl.h>
#include	<signal.h>

#define		SUCCESS			0
#define		ERROR			-1
#define		ACK			1
#define		FILE_NOT_FOUND		2
#define		FILE_ALREADY_EXIST	3		
#define		MSG_TOO_LONG		4
#define		ATH			5
#define		REG			6
#define		CMDD			7
#define		MSG			8
#define		UPL			9
#define		DWL			10
#define		MSG_LEN			1024
#define		TMSG			512

typedef struct 
{
  char 	usrName[20];
  char 	passWord[10];
  char	emailID[20];
  char	secQst[30];
  char	secAns[50];
  char  lastLog[15];
  int 	status;
}usr_t;

typedef struct
{
  char	flName[20];
  int	flSize;
  char  owner[20];
  char  type[10];
  int 	status;
}file_t;

typedef struct
{
  char		user[20];
  struct 	sockaddr_in clAddr;
  int		status;
  char		curDir[500];
}conn_t;

typedef struct fileLL
{
  file_t data;
  struct fileLL  *pNext;
}fNode_t;

typedef struct userLL
{
  usr_t data;
  struct userLL  *pNext;
}usrNode_t;

typedef struct connLL
{
  conn_t data;
  struct connLL  *pNext;
}connNode_t;

int userAuthantication();
int createPacket();
int createPacketCM();
int userRegistration();
int mainProcess(char *);
int cmdProcess(char *);
int uplProcess();
int uplProcessPkt(char *,int);
int dwlProcess();
int dwlProcessPkt(char *,int);
void firstProcess();
void serverProcess();
void userLL();
void displayULL();
void writeToFile();
void writeToLog(usr_t);
void writeToReport();
int upload(char *,file_t);
int download(char *,file_t);

usrNode_t *pHead,*pTail,*pTfl;
connNode_t *pH,*pTl;
fNode_t *fH,*fTl,*fTfl;

char dir[] = "Database", usrFile[] = "./Database/usrDetails.bin",logFile[]="./Database/log.bin",reportFile[]="./Database/report.bin";

char pkt[MSG_LEN],cmdd[][10]={"help","login","logout","exit","reg","upl","dwn","ls","cd","pwd","mkdir","rm"},usr[20],gs[]="guest";
