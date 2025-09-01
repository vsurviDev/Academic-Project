#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define TFTP_SER_IP "124.125.105.24"
#define TFTP_SER_PORT 69
#define CLI_PORT 9999
#define MAX_MSG 516
#define F_SIZE 50 
#define RRQ  1
#define WRQ  2
#define DATA 3
#define ACK  4
#define ERR  5
#define EXT  0

int creatPkt(char *); 
void processPkt(char *,int);
void readFromSer(struct sockaddr_in,char *,int,int);
void writeToSer(struct sockaddr_in,char *,int);
int createACK(short int,char *);
void stringConcat(void);
char rFile[F_SIZE],wFile[F_SIZE];
int flag;
