#include <fstream> //for file streams
#include <iostream>
#include <conio.h>
#include<iomanip>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <algorithm>
#include <vector>
using namespace std;
class userDetails
{
    public:
       char uName[20];
       char passW[7];
       unsigned int uId;
    private:
       char gender;
       unsigned int age;
       char address[50];
       char accNumber[20];
    public:
       void getData()
       {
             cout<<"User ID: ";
             cin>>uId;
             cout<<"Username: ";
             fflush(stdin);
             cin.getline(uName,20);
             cout<<"Password: ";
             fflush(stdin);
             cin.getline(passW,7);
             cout<<"Gender: ";
             fflush(stdin);
             cin>>gender;
             cout<<"Age: ";
             cin>>age;
             cout<<"Address: ";
             fflush(stdin);
             cin.getline(address,50);
             cout<<"Accoount Number: ";
             fflush(stdin);
             cin.getline(accNumber,20);     
       }
       void putData()
       {
            cout<<"\n"<<uId<<" - "<<uName<<" - "<<passW<<" - "<<gender<<" - "<<age<<" - "<<address<<" - "<<accNumber;
       }
};

class trainDetails
{
    public:
       int trNo;
       int scFare;
       int acFare;
    private:
       char trName[20];
       char srStation[40];
       char deStation[40];
       struct tm depTime;
       struct tm arrTime;
       unsigned short int scTotalSeats; 
       unsigned short int acTotalSeats; 
    public:
       void getData()
       {
             cout<<"Train Number: ";
             cin>>trNo;
             cout<<"Train Name: ";
             fflush(stdin);
             cin.getline(trName,20);
             cout<<"Source Station: ";
             fflush(stdin);
             cin.getline(srStation,40);
             cout<<"Destination Station: ";
             fflush(stdin);
             cin.getline(deStation,40);
             scTotalSeats=12;
             acTotalSeats=8;
             
             cout<<"Departure Hour: ";
             cin>>depTime.tm_hour;
             cout<<"Departure Minutes: ";
             cin>>depTime.tm_min;
        
             depTime.tm_mday=5; //day of the month 
             depTime.tm_mon=9; //month 
             depTime.tm_year=00; //year does not include century 
             depTime.tm_wday=5; //day of the week 
             depTime.tm_yday=0; //does not show in asctime 
             depTime.tm_isdst=0; //is Daylight SavTime, does not show in asctime /* converts structure to null terminates string */ 
             
             cout<<"Arrival Hour: ";
             cin>>arrTime.tm_hour;
             cout<<"Arrival Minutes: ";
             cin>>arrTime.tm_min;
        
             arrTime.tm_mday=5; //day of the month 
             arrTime.tm_mon=9; //month 
             arrTime.tm_year=00; //year does not include century 
             arrTime.tm_wday=5; //day of the week 
             arrTime.tm_yday=0; //does not show in asctime 
             arrTime.tm_isdst=0; //is Daylight SavTime, does not show in asctime /* converts structure to null terminates string */ 

             cout<<"SC Fare: ";
             cin>>scFare;
             cout<<"AC Fare: ";
             cin>>acFare;
       }
       void putData()
       {
            char b1[100],b2[100];
            strftime(b1,100,"%I:%M %p.",&depTime);
            strftime(b2,100,"%I:%M %p.",&arrTime);

            cout<<"\n"<<trNo<<" - "<<trName<<" - "<<srStation<<" - "<<deStation<<" - "<<b1<<" - "<<b2<<" - "<<scTotalSeats<<" - "<<acTotalSeats<<" - "<<scFare<<" - "<<acFare;
       }
       void trData(int n)
       {
            char b1[100],b2[100];
            if(n==trNo)
            {
                strftime(b1,100,"%I:%M %p.",&depTime);
                strftime(b2,100,"%I:%M %p.",&arrTime);
    
                cout<<"\n"<<trNo<<" - "<<trName<<" - "<<srStation<<" - "<<deStation<<" - "<<b1<<" - "<<b2<<" - "<<scTotalSeats<<" - "<<acTotalSeats<<" - "<<scFare<<" - "<<acFare;
            }
       }
       int srData(char *src)
       {
            char b1[100],b2[100];
            if(strcmp(src,srStation)==0)
            {
                strftime(b1,100,"%I:%M %p.",&depTime);
                strftime(b2,100,"%I:%M %p.",&arrTime);
    
                cout<<"\n"<<trNo<<" - "<<trName<<" - "<<srStation<<" - "<<deStation<<" - "<<b1<<" - "<<b2<<" - "<<scTotalSeats<<" - "<<acTotalSeats<<" - "<<scFare<<" - "<<acFare<<endl;
                return 1;
            }
            return 0;
       }
       int dstData(char *src)
       {
            char b1[100],b2[100];
            if(strcmp(src,deStation)==0)
            {
                strftime(b1,100,"%I:%M %p.",&depTime);
                strftime(b2,100,"%I:%M %p.",&arrTime);
    
                cout<<"\n"<<trNo<<" - "<<trName<<" - "<<srStation<<" - "<<deStation<<" - "<<b1<<" - "<<b2<<" - "<<scTotalSeats<<" - "<<acTotalSeats<<" - "<<scFare<<" - "<<acFare<<endl;
                return 1;
            }
            return 0;
       }
       int sdData(char *src,char *dst)
       {
            char b1[100],b2[100];
            if(strcmp(src,srStation)==0 && strcmp(dst,deStation)==0)
            {
                strftime(b1,100,"%I:%M %p.",&depTime);
                strftime(b2,100,"%I:%M %p.",&arrTime);
    
                cout<<"\n"<<trNo<<" - "<<trName<<" - "<<srStation<<" - "<<deStation<<" - "<<b1<<" - "<<b2<<" - "<<scTotalSeats<<" - "<<acTotalSeats<<" - "<<scFare<<" - "<<acFare<<endl;
                return 1;
            }
            return 0;
       }
};

class trainTrip : public trainDetails
{
    public:
       int tripNo;
       unsigned short int maxSC;
       unsigned short int maxAC;
       unsigned short int maxSCW;
       unsigned short int maxACW;
    private:
       struct tm  tripSchdt;
    public:
       void getData(int n,trainDetails t,int ii)
       {
            int date;
            char buff[100],cnv[3];
            time_t curtime;
            struct tm *loctime;
            time_t now;   /// taking 2 variable for time_t datatype
            
            tripNo=n;
            trNo=t.trNo; //train number
     
            curtime=time(NULL);
            loctime = localtime(&curtime);
            strftime(buff,100,"%A%B%d",loctime);
            cnv[0]=buff[strlen(buff)-2];
            cnv[1]=buff[strlen(buff)-1];
            cnv[2]=0;
            sscanf(cnv,"%d",&date);
            time(&now);
            tripSchdt=(*localtime(&now));  /// converting into localtime format
            tripSchdt.tm_mday=(date+ii+1);
            
            maxSC=12;
            maxAC=8;
            maxSCW=4;
            maxACW=4;
            
        }
       void putData()
       {
                time_t re;
                int uqId,jj,ii;
                char buff[100],pb[100];
                re=mktime(&tripSchdt);
                memset(buff,0,sizeof(buff));
                memset(pb,0,sizeof(pb));
                sprintf(buff,"%s",ctime(&re));
                buff[strlen(buff)-1]=0;
                for(jj=0,ii=0;jj<strlen(buff);jj++)
                {
                    if(jj<11 || jj>19)
                       pb[ii++]=buff[jj];
                }
                cout<<"\n"<<tripNo<<"\t - "<<trNo<<" - "<<pb<<" - "<<maxSC<<" - "<<maxAC<<" - "<<maxSCW<<" - "<<maxACW<<endl;
       }
       void dtData(int date)
       {
                time_t re;
                int uqId,jj,ii;
                char buff[100],pb[100];
                if(date == tripSchdt.tm_mday)
                {
                    re=mktime(&tripSchdt);
                    memset(buff,0,sizeof(buff));
                    memset(pb,0,sizeof(pb));
                    sprintf(buff,"%s",ctime(&re));
                    buff[strlen(buff)-1]=0;
                    for(jj=0,ii=0;jj<strlen(buff);jj++)
                    {
                        if(jj<11 || jj>19)
                           pb[ii++]=buff[jj];
                    }
                    cout<<"\n"<<tripNo<<"\t - "<<trNo<<" - "<<pb<<" - "<<maxSC<<" - "<<maxAC<<" - "<<maxSCW<<" - "<<maxACW<<endl;
                }
       }
       void tdData(int date,list<trainDetails> ls)
       {
                time_t re;
                int uqId,jj,ii;
                char buff[100],pb[100];
                if(date == tripSchdt.tm_mday)
                {
                    list<trainDetails> :: iterator p;
                    for(p=ls.begin();p!=ls.end();++p)
                    {
                       p->trData(trNo);
                    }
                    re=mktime(&tripSchdt);
                    memset(buff,0,sizeof(buff));
                    memset(pb,0,sizeof(pb));
                    sprintf(buff,"%s",ctime(&re));
                    buff[strlen(buff)-1]=0;
                    for(jj=0,ii=0;jj<strlen(buff);jj++)
                    {
                        if(jj<11 || jj>19)
                           pb[ii++]=buff[jj];
                    }
                    cout<<"\n"<<tripNo<<"\t - "<<trNo<<" - "<<pb<<" - "<<maxSC<<" - "<<maxAC<<" - "<<maxSCW<<" - "<<maxACW<<endl;
                }
       }
       void scData(int num)
       {
                time_t re;
                int uqId,jj,ii;
                char buff[100],pb[100];
                if(num == trNo)
                {
                    re=mktime(&tripSchdt);
                    memset(buff,0,sizeof(buff));
                    memset(pb,0,sizeof(pb));
                    sprintf(buff,"%s",ctime(&re));
                    buff[strlen(buff)-1]=0;
                    for(jj=0,ii=0;jj<strlen(buff);jj++)
                    {
                        if(jj<11 || jj>19)
                           pb[ii++]=buff[jj];
                    }
                    cout<<"\n"<<tripNo<<"\t - "<<trNo<<" - "<<pb<<" - "<<maxSC<<" - "<<maxAC<<" - "<<maxSCW<<" - "<<maxACW<<endl;
                }
       }
       void brData(int num)
       {
                time_t re;
                int uqId,jj,ii;
                char buff[100],pb[100];
                if(num == tripNo)
                {
                    re=mktime(&tripSchdt);
                    memset(buff,0,sizeof(buff));
                    memset(pb,0,sizeof(pb));
                    sprintf(buff,"%s",ctime(&re));
                    buff[strlen(buff)-1]=0;
                    for(jj=0,ii=0;jj<strlen(buff);jj++)
                    {
                        if(jj<11 || jj>19)
                           pb[ii++]=buff[jj];
                    }
                    cout<<"\n"<<tripNo<<"\t - "<<trNo<<" - "<<pb<<" - "<<maxSC<<" - "<<maxAC<<" - "<<maxSCW<<" - "<<maxACW<<endl;
                }
       }
};
class headerTrip : public trainTrip
{
    private:
       char seatNSL[12];
       char seatNAC[8];
       char seatNSLW[4];
       char seatNACW[4];
       int seatno;
       char type[4];
    public:
       void getData(trainTrip tr)
       {
             maxSC=tr.maxSC;
             maxAC=tr.maxAC;
             maxSCW=tr.maxSCW;
             maxACW=tr.maxACW;
             memset(seatNSL,'0',sizeof(seatNSL));
             memset(seatNAC,'0',sizeof(seatNAC));
             memset(seatNSLW,'0',sizeof(seatNSLW));
             memset(seatNACW,'0',sizeof(seatNACW));
             seatno=0;
             memset(type,0,sizeof(type));
       }
       void putData()
       {
       }
};

class pnr : public trainTrip
{
};

class reserv
{
      public:
         friend class pnr;
};
void userDet();
void printDet();
int chkFun(char *,char *);
void trainDet();
void printTrDet();
void printSch();
void crSchd(int);
void rsHead(trainTrip);
void mklist();

list<userDetails> lu;
list<trainDetails> lt;
list<trainTrip> ltr;

int srTsrc(list<trainDetails>);
int srTdst(list<trainDetails>);
int srTsd(list<trainDetails>);
int srTdt(list<trainTrip>);
int srTsch(list<trainTrip>);
int srTbrt(list<trainTrip>);
int srTtd(list<trainTrip>);
