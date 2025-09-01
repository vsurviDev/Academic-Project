#include <stdio.h>
#include <conio.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define ADM 1
#define USR 2
#define NOACC 0
#define SL 1
#define AC 2
#define NSL 12
#define NAC 8
#define WSL 4
#define WAC 4

typedef struct
{
    int user_id;
    char passwd[7];
    char user_name[30];
    enum Gender{Male=0,Female=1} gender;
    unsigned short int age;
    char address[100];
    char account[16];
}user_t;

typedef struct
{
    short int train_no;
    char train_name[31];
    char train_source[31];
    char train_destination[31];
    struct tm departure_time;
    struct tm arrival_time;
    short int sc_total_seats;
    short int ac_total_seats;
    short int sc_fare;
    short int ac_fare;
}train_t;

typedef struct Header
{
   int n_seatsSL;
   int n_seatsAC;
   int n_seatsSLW;
   int n_seatsACW;
   char seatNSL[12];
   char seatNAC[8];
   char seatNSLW[4];
   char seatNACW[4];
   int seatno;
   char type[4];
}head_t;

typedef struct TRAIN_TRIP
{ 
    int trip_id;
    short int trip_train_no;
    struct tm  trip_scheduled_dt;
    unsigned short int trip_max_sc;
    unsigned short int trip_max_ac;
    unsigned short int trip_max_wl_sc;
    unsigned short int trip_max_wl_ac;
}train_trip_t;

typedef struct PNR
{
    short int train_no;
    int trip_id;
    short int seatno;
    short int noOfseatsBooked;
    char type[4]; //AC or Sleeper SL
	char status[4]; //Reserved (R) or waiting list(WL)
}pnr_t;

typedef struct RESERVATIONS
{
        pnr_t pnr; //Generated PNR number
        int user_id; //ID of the user booked
        char passenger_name[31];//Name of the Passenger Travelling
        short int age; //Age of the passenger Travelling
        char gender[2];//= Female --> F Male --> M
        int seatno;
        char type[4];
        time_t booked_time; //Time of booking
}reservations_t;

//User Booking History Structure
typedef struct BOOKING_HISTORY
{
  pnr_t pnr;
  int user_id;
  time_t booking_time; //Booking date and time  
  char passenger_name[31];
  short int age;
  char gender[2];//= Female --> F Male --> M
  short int seatno;
  char type[4]; //AC or Sleeper SL  
  char status[4]; //Reserved (R) or waiting list(WL)
  int cost;//Cost of the seat 
}booking_history_t;

typedef struct  UserNode
{
	user_t u;
	struct UserNode *next;
}unode_t;
 
typedef struct  TrainDetailsNode
{
	train_t t;
	struct TrainDetailsNode *next;
}tnode_t;
 
typedef struct  TrainTripNode
{
	train_trip_t ttrip;
	struct TrainTripNode *next;
}ttripnode_t;

unode_t *uHead;
tnode_t *tHead;
ttripnode_t *rpHead;

int chkFun(char *,char *);

int addUser();
void disAll();
void ullist();
int addTrain();
void dispTrain();
void tllist();
void sheduleTrain();
void dispTrainTrip();
void tripllist();
void resTrain();
void addLl();
void endTrip(train_trip_t);
char eTrip[30];

int serSrc(char *);
int serDest(char *);
int serSD(char *,char *);
int serBrth(int);
int serDate(int);
int serTSch(int);
int serTiDt(int);

int bkTicket();
int bkHistory(reservations_t);
void printDet(int);
int clTicket();





