#include 	<stdio.h>
#include	<string.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<pthread.h>
#include	<stdlib.h>
#include	<fcntl.h>
#include	<signal.h>
#include	<time.h>
//#include	<semaphore.h>

#define		ERROR		-1
#define		SUCCESS		0
#define		LOGIN		1
#define		LOGOUT		2
#define		IDLE		3
#define		REG		4
#define		EXT		5
#define		ACK		6
#define		ADD_FRND	7
#define		FIN		8
#define		GET_FRND	9
#define		CHAT		10
#define		FILEREQ		11

#define		SRV_IP		"172.16.5.90"
//#define		SRV_IP		"172.16.4.209"
//#define		SRV_IP		"127.0.0.1"
#define		SRV_PORT	8000	//TCP Port Number
#define		UDP_PORT	8001	//UDP Port Number
#define 	PKT_LEN		1024
#define		READLEN		513

typedef struct userDetails
{
  int id,ix;
  char userName[15],passWord[15],ip[20],inTime[30],outTime[30];
  unsigned short int port,uport;
  short int status;
  int list[100];
}usr_t;

typedef struct userLL
{
  struct userDetails usr;
  struct userLL *pNext;
}uNode_t;

typedef struct friendsList
{
  int id;
  char userName[15],ip[20];
  unsigned short int port,uport,mprt;
  short int status;
}frnd_t;

void errMessage(char *);
void userRegistration(int);
void userLogin(int,char *);
void addFriend(int,char *,char *);
void friendsContactList(int,char *,frnd_t *);
void userLogout(int,char *);
void processExit(void);
void delspaces(char *);
void registerProcess(char *,int *);
void loginProcess(char *,int *,struct sockaddr_in);
void logoutProcess(char *,int *);
void addFriendProcess(char *,int *);
void getFriendProcess(char *,int *,int);
int addUserLL(usr_t);
int raddUserLL(usr_t);
void displayLL(void);
void readFromFile(void);
void createLogFile(usr_t);
void finalWriteFile(char *,int);
void initialProcess(void);
void displayFriendsList(frnd_t *);
void createSenderUDPSocket();
void createSenderFTPSocket();
uNode_t *pHead,*pTail;
//sem_t clSemp1,clSemp2,srSemp1,srSemp2;
int idno;

