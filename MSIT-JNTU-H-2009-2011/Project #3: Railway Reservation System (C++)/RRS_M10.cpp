#include "RRS.h"
int trId=1;
int usrID;
int main()
{
    int ch,uch,z,ii;
    char usr[20],pwd[10];
    mkdir(".\\RRS");
    mkdir(".\\RRS\\MasterData");
    mkdir(".\\RRS\\TrainData");
    mkdir(".\\RRS\\UserHistory");
    while(1)
    {
       cout<<"\n\t---------------------Railway Reservation System---------------------\n";
       cout<<"\n\t\t\tUsername: ";
       fflush(stdin);
       cin.getline(usr,20);
       cout<<"\t\t\tPassword: ";
       fflush(stdin);
       cin.getline(pwd,10);
       uch=chkFun(usr,pwd);
       cout<<"\n\t--------------------------------------------------------------------\n";
       if(uch == 0)
       {
            cout<<"\n\t\t\tAdminstrator ("<<usr<<") Logged In\n";
            cout<<"\n\t\tUser Id Is: "<<usrID;
            while(1)
            {
                cout<<"\n\t---------------------RailWay Administration---------------------\n";
                cout<<"\n\t\t1. Add New User\n\t\t2. Add New Train Details\n\t\t3. Display all Users.\n\t\t4. Display all Train Details\n\t\t5. Display Trip Schedule\n\n\t\t0. Exit\n";
                cout<<"\n\t----------------------------------------------------------------\n";
                cout<<"\n\t\tEnter Choice: ";
                cin>>ch;
                if(ch == 0)
                {
                    cout<<"\n\tAdminstrator ("<<usr<<") Logged Out\n";
                    break;
                }
                else if(ch == 1)
                     userDet();
                else if(ch == 2)
                     trainDet(); 
                else if(ch == 3)
                    printDet();
                else if(ch == 4)
                    printTrDet();
                else if(ch == 5)
                {
                    for(ii=0;ii<6;ii++)
                    {
                        crSchd(ii);
                    }
                    printSch();
                }
                else 
                  cout<<"\n\t\tWrong Choice, Check Menu...........\n";
            }
       }
       else if(uch == 1)
       {
            cout<<"\n\t\t\tUser ("<<usr<<") Logged In\n";
            cout<<"\n\t\tUser Id Is: "<<usrID;
            mklist();
            while(1)
            {
                cout<<"\n\t----------------------RailWay User Process----------------------\n";
                cout<<"\n\t\t1. Search Train by Source\n\t\t2. Search Train by Destination\n\t\t3. Search Train by Date\n\t\t4. Search Train by Date and Time duration\n\t\t5. Search Train by Source and Destination\n\t\t6. Show Train Schedule\n\t\t7. Show Berth Availability in each class\n\t\t8. Book Ticket\n\n\t\t0. Exit\n";
                cout<<"\n\t----------------------------------------------------------------\n";
                cout<<"\n\t\tEnter Choice: ";
                cin>>ch;
                if(ch == 0)
                {
                    cout<<"\n\tUser ("<<usr<<") Logged Out\n";
                    break;
                }
                else if(ch == 1)
                     srTsrc(lt);
                else if(ch == 2)
                     srTdst(lt); 
                else if(ch == 3)
                    srTdt(ltr);
                else if(ch == 4)
                    srTtd(ltr);
                else if(ch == 5)
                     srTsd(lt);
                else if(ch == 6)
                    srTsch(ltr);
                else if(ch == 7)
                    srTbrt(ltr);
                else if(ch == 8)
                     ;
                else 
                  cout<<"\n\t\tWrong Choice, Check Menu...........\n";
            }
       }
       else if(uch == -1)
          cout<<"\n\t\tNo Such Users, Check Username & Password\n";
       cout<<"\n\tDo You Want To Sop Complete Process (Enter 0): ";
       cin>>z;
       if(z==0)
          break;
    }
    
    cout<<"\n\tEnter Any Key.....";
    getch();
}

int srTtd(list<trainTrip> ls)
{
     int date;
     list<trainTrip> :: iterator p;
     cout<<"\n\t\tEnter Date: ";
     cin>>date;
     for(p=ls.begin();p!=ls.end();++p)
     {
        p->tdData(date,lt);
     }
}

int srTbrt(list<trainTrip> ls)
{
     int num;
     list<trainTrip> :: iterator p;
     cout<<"\n\t\tEnter Trip Number: ";
     cin>>num;
     for(p=ls.begin();p!=ls.end();++p)
     {
        p->brData(num);
     }
}

int srTsch(list<trainTrip> ls)
{
     int num;
     list<trainTrip> :: iterator p;
     cout<<"\n\t\tEnter Train Number: ";
     cin>>num;
     for(p=ls.begin();p!=ls.end();++p)
     {
        p->scData(num);
     }
}

int srTdt(list<trainTrip> ls)
{
     int date;
     list<trainTrip> :: iterator p;
     cout<<"\n\t\tEnter Date: ";
     cin>>date;
     for(p=ls.begin();p!=ls.end();++p)
     {
        p->dtData(date);
     }
}

int srTsd(list<trainDetails> ls)
{
     char dst[40];
     char src[40];
     list<trainDetails> :: iterator p;
     cout<<"\n\t\tEnter Source Station: ";
     fflush(stdin);
     cin.getline(src,40);
     cout<<"\n\t\tEnter Destination Station: ";
     fflush(stdin);
     cin.getline(dst,40);
     for(p=ls.begin();p!=ls.end();++p)
     {
          if(p->sdData(src,dst))
             return 1;
     }
     cout<<"\n\t\tDetails Not Found\n";
     return 1;
}

int srTdst(list<trainDetails> ls)
{
     char dst[40];
     list<trainDetails> :: iterator p;
     cout<<"\n\t\tEnter Destination Station: ";
     fflush(stdin);
     cin.getline(dst,40);
     for(p=ls.begin();p!=ls.end();++p)
     {
          if(p->dstData(dst))
             return 1;
     }
     cout<<"\n\t\tDetails Not Found\n";
     return 1;
}

int srTsrc(list<trainDetails> ls)
{
     char src[40];
     list<trainDetails> :: iterator p;
     cout<<"\n\t\tEnter Source Station: ";
     fflush(stdin);
     cin.getline(src,40);
     for(p=ls.begin();p!=ls.end();++p)
     {
          if(p->srData(src))
             return 1;
     }
     cout<<"\n\t\tDetails Not Found\n";
     return 1;
}

/*void udis(list<userDetails> &ls)
{
     list<userDetails> :: iterator p;
     for(p=ls.begin();p!=ls.end();++p)
        p->putData();
}

void tdis(list<trainDetails> &ls)
{
     list<trainDetails> :: iterator p;
     for(p=ls.begin();p!=ls.end();++p)
        p->putData();
}

void trdis(list<trainTrip> &ls)
{
     list<trainTrip> :: iterator p;
     for(p=ls.begin();p!=ls.end();++p)
        p->putData();
}*/

void mklist()
{
                     //User List
    userDetails u;
    ifstream iufile(".\\RRS\\MasterData\\userDetails.binary");
     
    if(!iufile)
    {
       cout << "File cannot be opened for reading\n";
    }
    
    while(iufile.read(reinterpret_cast<char*>(&u),sizeof(u)))
    {
       lu.push_back(u);
    }
    //udis(lu);
    iufile.close();
                     //Train List
    trainDetails t;
    ifstream itfile(".\\RRS\\MasterData\\trainDetails.binary");
     
    if(!itfile)
    {
       cout << "File cannot be opened for reading\n";
    }
    
    while(itfile.read(reinterpret_cast<char*>(&t),sizeof(t)))
    {
       lt.push_back(t);
    }
     //tdis(lt);
     itfile.close();                
                     //Train Trip List
    trainTrip tr;
    ifstream itrfile(".\\RRS\\MasterData\\trainTrip.binary");
     
    if(!itrfile)
    {
       cout << "File cannot be opened for reading\n";
    }
    
    while(itrfile.read(reinterpret_cast<char*>(&tr),sizeof(tr)))
    {
       ltr.push_back(tr);
    }
    //trdis(ltr);
    itrfile.close();
}

void rsHead(trainTrip tr)
{
     headerTrip hr;
     char dR[100],fl[100];
     sprintf(dR,".\\RRS\\TrainData\\%d",tr.trNo);
     sprintf(fl,".\\RRS\\TrainData\\%d\\%d_reservations.binary",tr.trNo,tr.tripNo);
     mkdir(dR);
     ofstream fp;
     fp.open(fl,ios::out | ios::binary);
     if(!fp)
       cout<<"\n\t\tFile Open Error\n";
     memset(&hr,0,sizeof(hr));
     hr.getData(tr);
     fp.write(reinterpret_cast<char*>(&hr),sizeof(hr));
}

void printSch()
{
    ifstream ft;
    trainTrip tr;
    
    ft.open(".\\RRS\\MasterData\\trainTrip.binary");
    if(!ft)
       cout<<"\n\tFile Open Error\n";
    
    while(!ft.eof())
    {
        memset(&tr,0,sizeof(trainTrip));
        if(ft.read(reinterpret_cast<char*>(&tr),sizeof(tr))==0) break;
        tr.putData();
        rsHead(tr);
    }
    ft.close(); 
}

void crSchd(int ii)
{
    ofstream ftr;
    ifstream ft;
    trainTrip tr;
    trainDetails t;
    int jj,cnt;
    ftr.open(".\\RRS\\MasterData\\trainTrip.binary",ios::app | ios::binary);
    if(!ftr)
      cout<<"\n\tFile Open Error\n";
    
         ft.open(".\\RRS\\MasterData\\trainDetails.binary");
         if(!ft)
            cout<<"\n\t\tFILE Open Error\n";
         cnt=0;
         while(!ft.eof())
         {
                memset(&tr,0,sizeof(trainTrip));
                memset(&t,0,sizeof(trainDetails));
                if(ft.read(reinterpret_cast<char*>(&t),sizeof(t))==0) break;
                tr.getData(trId,t,ii);
                
                ftr.write(reinterpret_cast<char*>(&tr),sizeof(tr));
                trId++;
                cnt++;
         }
         ft.close();
    ftr.close();
}

void trainDet()
{
     ofstream fp;
     int n,pos;
     trainDetails tr;
     fp.open(".\\RRS\\MasterData\\trainDetails.binary",ios::app | ios::binary);
     if(!fp)
            cout<<"\n\tFile Open Error\n";

     tr.getData();
     tr.putData();
     fp.write(reinterpret_cast<char*>(&tr),sizeof(tr));
     fp.close();
}
void printTrDet()
{
     ifstream fp;
     trainDetails tr;
     int n,pos;
     fp.open(".\\RRS\\MasterData\\trainDetails.binary");
     if(!fp)
        cout<<"\n\t\tFILE Open Error\n";
     while(!fp.eof())
     {
        memset(&tr,0,sizeof(trainDetails));
        if(fp.read(reinterpret_cast<char*>(&tr),sizeof(tr))==0) break;
        tr.putData();
     }
     fp.close();
}
int chkFun(char *usr,char *pwd)
{
     ifstream fp;
     userDetails ur;
     int u1,p1,u2,p2;
     u1=strlen(usr);
     p1=strlen(pwd);
     fp.open(".\\RRS\\MasterData\\userDetails.binary");
     if(!fp)
        cout<<"\n\t\tFILE Open Error\n";
     memset(&ur,0,sizeof(userDetails));
     fp.read(reinterpret_cast<char*>(&ur),sizeof(ur));
     u2=strlen(ur.uName);
     p2=strlen(ur.passW);
     if(u1 == u2 && p1==p2)
     {
         if(strcmp(usr,ur.uName) == 0 && strcmp(pwd,ur.passW) == 0)
         {
             usrID=ur.uId;
             fp.close();
             return 0;
         }
     }
     while(!fp.eof())
     {
        memset(&ur,0,sizeof(userDetails));
        fp.read(reinterpret_cast<char*>(&ur),sizeof(ur));
        u2=strlen(ur.uName);
        p2=strlen(ur.passW);
        if(u1 == u2 && p1==p2)
        {
              if(strcmp(usr,ur.uName) == 0 && strcmp(pwd,ur.passW) == 0)
              {
                 usrID=ur.uId;
                 fp.close();
                 return 1;
              }
        }
     }
     fp.close();
     return -1;
}

void userDet()
{
     ofstream fp;
     int n,pos;
     userDetails ur;
     fp.open(".\\RRS\\MasterData\\userDetails.binary",ios::app | ios::binary);
     if(!fp)
            cout<<"\n\tFile Open Error\n";

     ur.getData();
     fp.write(reinterpret_cast<char*>(&ur),sizeof(ur));
     fp.close();
}

void printDet()
{
     ifstream fp;
     userDetails ur;
     int n,pos;
     fp.open(".\\RRS\\MasterData\\userDetails.binary");
     if(!fp)
        cout<<"\n\t\tFILE Open Error\n";
     while(!fp.eof())
     {
        memset(&ur,0,sizeof(userDetails));
        if(fp.read(reinterpret_cast<char*>(&ur),sizeof(ur))==0) break;
        ur.putData();
     }
     fp.close();
}
