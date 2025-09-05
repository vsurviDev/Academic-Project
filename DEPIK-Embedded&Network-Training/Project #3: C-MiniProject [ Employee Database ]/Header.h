#include <stdio.h>
#define SUCCESS 0
#define EXI 0
#define INVALID_COMMAND -1
#define ADD 1
#define DEL 2
#define GET 3
#define MOD 4
#define DIS 5
#define MSG_TOO_LONG 5
#define ID_NOT_FOUND 6
#define DET_NOT_INSERTED 7
#define MAX_MSG 256 
#define MAX_HASH 1024
#define NAM 1
#define PHN 2
#define ADDR 3
#define SAL 4
#define COM 5
typedef struct emp_det
{
  int id;
  char name[30];
  char phno[13];
  char addr[30];
  int sal;
}emp_t;

typedef struct dataBase
{
  emp_t r;
  struct dataBase *pNext;
}dB_t;

void prepareAddMsg(char *);
void prepareDelMsg(char *);
void prepareGetMsg(char *);
void displayRespMsg(char *);
void prepareModMsg(char *);


void sendMsg(char *,char *);
void msgToServer(char *,char *);

int addDataBase(char *,char *);
int delDataBase(char *,char *);
int getDataBase(char *,char *);
int modDataBase(char *,char *);
int disDataBase(char *,char *);

int insertEmpDet(emp_t *,char *);
int deleteEmpDet(int,char *);
int getEmpDet(int,char *);

int hashFun(int);
dB_t *hash[MAX_HASH];
int hix ;
int cnt;
