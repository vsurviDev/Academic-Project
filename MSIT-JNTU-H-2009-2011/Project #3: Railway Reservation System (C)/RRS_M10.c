#include "RRS.h"
char mDir[]=".\\RRS";
char chDir[]=".\\RRS\\MasterData";
char chDir1[]=".\\RRS\\TrainData";
char chDir2[]=".\\RRS\\UserHistory";
int uID;
int main()
{
    int ch,get,ii=0,cl=1;
    int num,nT;
    char usrname[30],passwd[7],ser1[40],ser2[40];
    user_t ur;
    mkdir(mDir);
    mkdir(chDir);
    mkdir(chDir1);
    mkdir(chDir2);
    addLl();
    while(cl)
    {
        printf("\n\tUSER NAME\t: ");
        fflush(stdin);
        scanf("%[^\n]s",usrname);
        printf("\tPASSWORD\t: ");
        fflush(stdin);
        scanf("%[^\n]s",passwd);
        get=chkFun(usrname,passwd);
        switch(get)
        {
            case NOACC:
                 printf("\n\tNo Account...... Contact ADMINISTRATOR\n");
                 break;
            case ADM:
                 printf("\n\tADMINISTRATOR (%s) Logged IN\n",usrname);
                 while(1)
                 {
                    printf("\n\n--------------ADD NEW USER & TRAIN Details--------------\n");
                    printf("\n\t1. Add New User\n\t2. Add New Train Details\n\t3. Scheduling the trains\n\t4. Display all Users\n\t5. Display all Train Details\n\t6. Display all the scheduled trains from the current date\n\n\t0. Exit This Menu"); 
                    printf("\n\n-----------------------------------------------------\n");
                    printf("Enter Option: ");
                    scanf("%d",&ch);
                    printf("-----------------------------------------------------\n");
                    if(ch == 0)
                    {
                       printf("\n\tAdministrator (%s) Logged Out\n",usrname);
                       break;
                    } 
                    switch(ch)
                    {
                              case 1:
                                   if(addUser())
                                     ullist();
                                   break;
                              case 2:
                                   if(addTrain())
                                      tllist();
                                   break;
                              case 3:
                                   if(rpHead == '\0')
                                   {
                                     sheduleTrain();
                                     tripllist();
                                   }
                                   else
                                     printf("\n\tTrip Shedule Created Upto %s \n",eTrip);
                                   break;
                              case 4:
                                   if(uHead)
                                      disAll();
                                   else
                                      printf("\n\tNo Users..... \n");
                                   break;
                              case 5:
                                   if(tHead)
                                      dispTrain();
                                   else
                                      printf("\n\tNo Train Shedule.........\n");
                                   break;
                              case 6:
                                   if(rpHead)
                                   {
                                      dispTrainTrip();
                                      resTrain();
                                   }
                                   else
                                      printf("\n\tNo Trip Shedule...........\n");
                                   break;
                              default:
                                   printf("\n\tWrong Choice....... Check MENU\n");
                                   break;
                    }
                 }
                 break;
            case USR:
                 printf("\n\tUSER (%s) Logged IN\n",usrname);
                 while(1)
                 {
                    printf("\n\n---------------------------Railway Reservation Process---------------------------\n");
                    printf("\n\t1. Search Train by Source\n\t2. Search Train by Destination\n\t3. Search Train by Date\n\t4. Search Train by Date and Time duration\n\t5. Search Train by Source and Destination\n\t6. Show Train Schedule\n\t7. Show Berth Availability in each class\n\t8. Book Tickets\n\t9. Cancel Tickets\n\n\t0. Exit This Menu"); 
                    printf("\n\n---------------------------------------------------------------------------------\n");
                    printf("Enter Option: ");
                    scanf("%d",&ch);
                    printf("---------------------------------------------------------------------------------\n");
                    if(ch == 0)
                    {
                       printf("\n\tUSER (%s) Logged Out\n",usrname);
                       break;
                    } 
                    switch(ch)
                    {
                              case 1:
                                   memset(ser1,0,sizeof(ser1));
                                   printf("\n\tEnter Source: ");
                                   fflush(stdin);
                                   scanf("%[^\n]s",ser1);
                                   if(serSrc(ser1))
                                   ;
                                   else
                                      printf("\n\tThe Details Not Found Using %s\n",ser1);
                                   break;
                              case 2:
                                   memset(ser1,0,sizeof(ser1));
                                   printf("\n\tEnter Destination: ");
                                   fflush(stdin);
                                   scanf("%[^\n]s",ser1);
                                   if(serDest(ser1))
                                   ;
                                   else
                                      printf("\n\tThe Details Not Found Using %s\n",ser1);
                                   break;
                              case 3:
                                   printf("\n\tEnter Date: ");
                                   scanf("%d",&num);
                                   if(serDate(num))
                                   ;
                                   else
                                      printf("\n\tThe Details Not Found Using Date (%d)\n",num);
                                   break;
                              case 4:
                                   printf("\n\tEnter Date: ");
                                   scanf("%d",&num);
                                   if(serTiDt(num))
                                   ;
                                   else
                                      printf("\n\tThe Details Not Found Using Date (%d)\n",num);
                                   break;
                              case 5:
                                   memset(ser1,0,sizeof(ser1));
                                   memset(ser2,0,sizeof(ser2));
                                   printf("\n\tEnter Source: ");
                                   fflush(stdin);
                                   scanf("%[^\n]s",ser1);
                                   printf("\n\tEnter Destination: ");
                                   fflush(stdin);
                                   scanf("%[^\n]s",ser2);
                                   if(serSD(ser1,ser2))
                                   ;
                                   else
                                      printf("\n\tThe Details Not Found Using %s & %s\n",ser1,ser2);
                                   break;
                              case 6:
                                   printf("\n\tEnter Train Number: ");
                                   scanf("%d",&num);
                                   if(serTSch(num))
                                   ;
                                   else
                                      printf("\n\tThe Details Not Found Using Train Number (%d)\n",num);
                                   break;
                              case 7:
                                   printf("\n\tEnter Train Number: ");
                                   scanf("%d",&num);
                                   if(serBrth(num))
                                   ;
                                   else
                                      printf("\n\tThe Details Not Found Using Train Number (%d)\n",num);
                                   break;
                              case 8:
                                   if((nT=bkTicket()))
                                       printDet(nT);
                                   break;
                              case 9:
                                   clTicket();
                                   break;
                              default:
                                   printf("\n\tWrong Choice....... Check MENU\n");
                                   break;
                    }
                 }
                 break;
        }
        fflush(stdin);
        printf("\n\tTo Turn Off Complete Process (Enter 0): ");
        if(getchar() == '0')
        {
            printf("\n\tComplete Process Is Turned OFF\n");
            cl=0;
        }
    }
    fflush(stdin);
    getchar();
}

int clTicket()
{
    FILE *fp;
    booking_history_t hr;
    char buff[100],chk[100];;
    
    if(!(fp=fopen(".\\RRS\\UserHistory\\user_history.binary","r+b")))
      printf("\n\tRead File Open Error\n");
    
    //printf("\n\t\tPNR Number: ");
    //fflush(stdin);
    //scanf("%[^\n]s",chk);
    while(!feof(fp))
    {
         memset(buff,0,sizeof(buff));
         if(fread(&hr,sizeof(booking_history_t),1,fp)<1) break;
         sprintf(buff,"%d-%d-%d-%d-%s-%s",hr.pnr.train_no,hr.pnr.trip_id,hr.seatno,hr.pnr.noOfseatsBooked,hr.type,hr.status);
         if(strcmp(buff,chk) == 0)
         {
         } 
         printf("\nPNR No: %d-%d-%d-%d-%s-%s",hr.pnr.train_no,hr.pnr.trip_id,hr.seatno,hr.pnr.noOfseatsBooked,hr.type,hr.status);
         printf("\n\t\t\t%-18s\t%d\t%s\t%s\t%d\t%s\t%d",hr.passenger_name,hr.age,hr.gender,hr.type,hr.seatno,hr.status,hr.cost);
    }
    fclose(fp);
}

void printDet(int n)
{
     FILE *fp,*fr,*fs;
     booking_history_t hr;
     train_t tr;
     train_trip_t ts;
     time_t re;
     int jj;
     char buff[100],pb[100],b1[100];
     struct tm *loctime;
     int ii=1,sum=0;
     
     char hfl[]=".\\RRS\\UserHistory\\user_history.binary";
     if(!(fp=fopen(hfl,"rb")))
        printf("\n\tRead File Open Error\n");

     if(!(fr=fopen(".\\RRS\\MasterData\\train_details.binary","rb")))
        printf("\n\tRead File Error\n");
        
     fseek(fp,0,SEEK_END);
     fseek(fp,((-1) * n * sizeof(booking_history_t)),SEEK_CUR);
     memset(&hr,0,sizeof(booking_history_t));
     fread(&hr,sizeof(booking_history_t),1,fp);
     printf("\n\n\t--------------------------------Railway Reservation System--------------------------------\n\n");
     printf("\n\t\tPNR No: %d-%d-%d-%d-%s-%s",hr.pnr.train_no,hr.pnr.trip_id,hr.seatno,hr.pnr.noOfseatsBooked,hr.type,hr.status);
     loctime=localtime(&hr.booking_time);
     printf("\n\t\tBooked Time & Date: %s",asctime(loctime));
     printf("\t\tBooked User Id: %d",hr.user_id);
     
     fseek(fr,sizeof(int),SEEK_SET);
     while(!feof(fr))
     {
         memset(&tr,0,sizeof(train_t));
         if(fread(&tr,sizeof(train_t),1,fr)<1) break;
         if(hr.pnr.train_no == tr.train_no)
         {
             printf("\n\t\tTrain No: %d\t\t\tTrain Name: %s\t\tTrip No: %d",hr.pnr.train_no,tr.train_name,hr.pnr.trip_id);
             printf("\n\t\tSource Station: %s\t\tDestination Station: %s",tr.train_source,tr.train_destination);
             memset(b1,0,sizeof(b1));
             printf("\n\t\tTotal Seats Booked By: %d",hr.pnr.noOfseatsBooked);
             strftime(b1,100,"%I:%M %p.",&tr.departure_time);
         }
     }
     fclose(fr);
     
     if(!(fs=fopen(".\\RRS\\MasterData\\train_trip.binary","rb")))
        printf("\n\tFile Read Error\n");

     fseek(fs,sizeof(int),SEEK_SET);
     while(!feof(fs))
     {
          memset(&ts,0,sizeof(train_trip_t));
          if(fread(&ts,sizeof(train_trip_t),1,fs)<1) break;
          if(ts.trip_id == hr.pnr.trip_id)
          {
                re=mktime(&ts.trip_scheduled_dt);
                memset(buff,0,sizeof(buff));
                memset(pb,0,sizeof(pb));
                sprintf(buff,"%s",ctime(&re));
                buff[strlen(buff)-1]=0;
                for(jj=0,ii=0;jj<strlen(buff);jj++)
                {
                    if(jj<11 || jj>19)
                       pb[ii++]=buff[jj];
                }
                printf("\n\t\tTravel Date & Time: %s, %s",pb,b1);
          }
     }
     fclose(fs);
     printf("\n\n\t\tPassenger Details\n");
     ii=1;
     while(!feof(fp))
     {
         printf("\n\t\t%-2d\t%-18s\t%d\t%s\t%s\t%d\t%s\t%d",ii++,hr.passenger_name,hr.age,hr.gender,hr.type,hr.seatno,hr.status,hr.cost);
         sum=sum+hr.cost; 
         memset(&hr,0,sizeof(booking_history_t));
         if(fread(&hr,sizeof(booking_history_t),1,fp)<1) break;
     }
     printf("\n\n\t------------------------------------------------------------------------------------------\n");
     printf("\n\t\t\t\t\tTotal Ticket Charges: %d",sum);
     printf("\n\n\t------------------------------------------------------------------------------------------\n\n");
     fclose(fp);
}

int bkTicket()
{
    FILE *fp,*fr;
    reservations_t ur;
    train_trip_t tr;
    head_t hR;
    char fl[100];
    int ii,n,ts,trn,nT;
        if(!(fp=fopen(".\\RRS\\MasterData\\train_trip.binary","rb")))
            printf("\n\tFile Read Error\n");
    
        memset(&ur,0,sizeof(reservations_t));
        printf("\n\tTrip Number: ");
        scanf("%d",&ur.pnr.trip_id);
        fread(&trn,sizeof(int),1,fp);
        if(ur.pnr.trip_id<=0 || ur.pnr.trip_id>trn)
        {
            printf("\n\tNot A Valid trip Id, Trip Id Should Be > 0  And < %d\n",(trn+1));
            fclose(fp);
            return 0;
        }
        fseek(fp,sizeof(int),SEEK_SET);
        while(!feof(fp))
        {
            memset(&tr,0,sizeof(train_trip_t));
            if(fread(&tr,sizeof(train_trip_t),1,fp)<1) break;
            if(ur.pnr.trip_id == tr.trip_id)
            {
               ur.pnr.train_no=tr.trip_train_no;
            }
        }
        fclose(fp);
        memset(fl,0,sizeof(fl));
        sprintf(fl,".\\RRS\\TrainData\\%d\\%d_reservations.binary",ur.pnr.train_no,ur.pnr.trip_id);
    
        if(!(fr=fopen(fl,"r+b")))
            printf("\n\tFile Read Error\n");
            
        memset(&hR,0,sizeof(head_t));
        
        fread(&hR,sizeof(head_t),1,fr);
        if(hR.n_seatsSL == 0 && hR.n_seatsAC == 0 && hR.n_seatsSLW == 0 && hR.n_seatsACW == 0)
        {
           printf("\n\tThis Trip Is Full, Try In Other Trip\n");
           fclose(fr);
           return 0;
        }   
        printf("\n\tn_seatsSL\t:\t%2d\n\tn_seatsAC\t:\t%2d\n\tn_seatsSLW\t:\t%2d\n\tn_seatsACW\t:\t%2d\n",hR.n_seatsSL,hR.n_seatsAC,hR.n_seatsSLW,hR.n_seatsACW);
        printf("\n\tClass Type\t\t");
        for(ii=0;ii<12;ii++)
        printf("%-2d  ",ii+1);
        printf("\n\n\tSL Class\t:\t");
        for(ii=0;ii<12;ii++)
        printf("%c   ",hR.seatNSL[ii]);
        printf("\n\tAC Class\t:\t");
        for(ii=0;ii<8;ii++)
        printf("%c   ",hR.seatNAC[ii]);
        printf("\n\tW-SL Class\t:\t");
        for(ii=0;ii<4;ii++)
        printf("%c   ",hR.seatNSLW[ii]);
        printf("\n\tW-AC Class\t:\t");
        for(ii=0;ii<4;ii++)
        printf("%c   ",hR.seatNACW[ii]);
        printf("\n");
        while(1)
        {
          printf("\n\tNo Of Seats To Book: ");
          scanf("%d",&ur.pnr.noOfseatsBooked);
          if(ur.pnr.noOfseatsBooked == 1 || ur.pnr.noOfseatsBooked == 2)
            break;
          else
            printf("\n\tMIN 1 And MAX 2, To Book A Tickets\n");
        } 
        nT=ur.pnr.noOfseatsBooked; 
        printf("\n\tClass Type (1 - SL/2 - AC): ");
        scanf("%d",&n);
        memset(ur.pnr.type,0,sizeof(ur.pnr.type));
        
        switch(n)
        {
                 case SL:
                      printf("\n\tSL Account\n");
                      ts=(hR.n_seatsSL+hR.n_seatsSLW);
                      if(ur.pnr.noOfseatsBooked <= ts)
                      {
                          strcpy(ur.pnr.type,"SL");
                          for(ii=0;ii<nT;ii++)
                          {
                              if(hR.n_seatsSL == 0)
                              {
                                  printf("\n\tWaiting List\n");
                                  strcpy(ur.pnr.type,"SL");
                                  printf("\n\tPassenger Name: ");
                                  fflush(stdin);
                                  scanf("%[^\n]s",ur.passenger_name);
                                  printf("\n\tAge: ");
                                  scanf("%d",&ur.age);
                                  printf("\n\tGender (M/F): ");
                                  scanf("%s",ur.gender);
                                  ur.pnr.noOfseatsBooked=nT;
                                  while(1)
                                  {
                                      while(1)
                                      {
                                          printf("\n\tSeat Number: ");
                                          scanf("%d",&ur.pnr.seatno);
                                          if (ur.pnr.seatno<=WSL)
                                             break;
                                          else
                                             printf("\n\tNot A Valid Seat Number\n");
                                      }
                                      if(hR.seatNSLW[ur.pnr.seatno-1]=='X')
                                         printf("\n\tWrong Selection, Seat Already Reserved\n");
                                      else
                                         break;
                                  }
                                  ur.pnr.noOfseatsBooked=nT;
                                  ur.seatno=ur.pnr.seatno;
                                  ur.pnr.noOfseatsBooked=nT;
                                  strcpy(ur.pnr.status,"WL");
                                  ur.user_id=uID;
                                  strcpy(ur.type,ur.pnr.type);
                                  hR.n_seatsSLW--;
                                  hR.seatNSLW[ur.seatno-1]='X';
                              }
                              else
                              {
                                  printf("\n\tPassenger Name: ");
                                  fflush(stdin);
                                  scanf("%[^\n]s",ur.passenger_name);
                                  printf("\n\tAge: ");
                                  scanf("%d",&ur.age);
                                  printf("\n\tGender (M/F): ");
                                  scanf("%s",ur.gender);
                                  ur.pnr.noOfseatsBooked=nT;
                                  while(1)
                                  {
                                      while(1)
                                      {
                                          printf("\n\tSeat Number: ");
                                          scanf("%d",&ur.pnr.seatno);
                                          if (ur.pnr.seatno<=NSL)
                                             break;
                                          else
                                             printf("\n\tNot A Valid Seat Number\n");
                                      }
                                      if(hR.seatNSL[ur.pnr.seatno-1]=='X')
                                         printf("\n\tWrong Selection, Seat Already Reserved\n");
                                      else
                                         break;
                                  }
                                  ur.pnr.noOfseatsBooked=nT;
                                  ur.seatno=ur.pnr.seatno;
                                  ur.pnr.noOfseatsBooked=nT;
                                  strcpy(ur.pnr.status,"R");
                                  ur.user_id=uID;
                                  strcpy(ur.type,ur.pnr.type);
                                  hR.n_seatsSL--;
                                  hR.seatNSL[ur.seatno-1]='X';
                              }
                              fseek(fr,0,SEEK_SET);
                              fwrite(&hR,sizeof(head_t),1,fr);
                              fseek(fr,0,SEEK_END);
                              ur.booked_time=time(NULL);
                              fwrite(&ur,sizeof(reservations_t),1,fr);
                              bkHistory(ur);
                          }
                      }
                      else if (ur.pnr.noOfseatsBooked > ts)
                      {
                          printf("\n\tOnly %d - Available In SL Waiting List\n",ts);
                          fclose(fr);
                          return 0;
                      }
                      else if (ts == 0)
                      {
                          printf("\n\tNo Booking In SL Class, Try In Other Trip\n");
                          fclose(fr);
                          return 0;
                      }
                      break;
                 case AC:
                      printf("\n\tAC Account\n");
                      ts=(hR.n_seatsAC+hR.n_seatsACW);
                      if(ur.pnr.noOfseatsBooked <= ts)
                      {
                          strcpy(ur.pnr.type,"AC");
                          for(ii=0;ii<nT;ii++)
                          {
                              if(hR.n_seatsAC == 0)
                              {
                                  printf("\n\tWaiting List\n");
                                  strcpy(ur.pnr.type,"AC");
                                  printf("\n\tPassenger Name: ");
                                  fflush(stdin);
                                  scanf("%[^\n]s",ur.passenger_name);
                                  printf("\n\tAge: ");
                                  scanf("%d",&ur.age);
                                  printf("\n\tGender (M/F): ");
                                  scanf("%s",ur.gender);
                                  ur.pnr.noOfseatsBooked=nT;
                                  while(1)
                                  {
                                      while(1)
                                      {
                                          printf("\n\tSeat Number: ");
                                          scanf("%d",&ur.pnr.seatno);
                                          if (ur.pnr.seatno<=WAC)
                                             break;
                                          else
                                             printf("\n\tNot A Valid Seat Number\n");
                                      }
                                      if(hR.seatNACW[ur.pnr.seatno-1]=='X')
                                         printf("\n\tWrong Selection, Seat Already Reserved\n");
                                      else
                                         break;
                                  }
                                  ur.pnr.noOfseatsBooked=nT;
                                  ur.seatno=ur.pnr.seatno;
                                  ur.pnr.noOfseatsBooked=nT;
                                  strcpy(ur.pnr.status,"WL");
                                  ur.user_id=uID;
                                  strcpy(ur.type,ur.pnr.type);
                                  hR.n_seatsACW--;
                                  hR.seatNACW[ur.seatno-1]='X';
                              }
                              else
                              {
                                  printf("\n\tPassenger Name: ");
                                  fflush(stdin);
                                  scanf("%[^\n]s",ur.passenger_name);
                                  printf("\n\tAge: ");
                                  scanf("%d",&ur.age);
                                  printf("\n\tGender (M/F): ");
                                  scanf("%s",ur.gender);
                                  ur.pnr.noOfseatsBooked=nT;
                                  while(1)
                                  {
                                      while(1)
                                      {
                                          printf("\n\tSeat Number: ");
                                          scanf("%d",&ur.pnr.seatno);
                                          if (ur.pnr.seatno<=NAC)
                                             break;
                                          else
                                             printf("\n\tNot A Valid Seat Number\n");
                                      }
                                      if(hR.seatNAC[ur.pnr.seatno-1]=='X')
                                         printf("\n\tWrong Selection, Seat Already Reserved\n");
                                      else
                                         break;
                                  }
                                  ur.pnr.noOfseatsBooked=nT;
                                  ur.seatno=ur.pnr.seatno;
                                  ur.pnr.noOfseatsBooked=nT;
                                  strcpy(ur.pnr.status,"R");
                                  ur.user_id=uID;
                                  strcpy(ur.type,ur.pnr.type);
                                  hR.n_seatsAC--;
                                  hR.seatNAC[ur.seatno-1]='X';
                              }
                              fseek(fr,0,SEEK_SET);
                              fwrite(&hR,sizeof(head_t),1,fr);
                              fseek(fr,0,SEEK_END);
                              ur.booked_time=time(NULL);
                              fwrite(&ur,sizeof(reservations_t),1,fr);
                              bkHistory(ur);
                          }
                      }
                      else if (ur.pnr.noOfseatsBooked > ts)
                      {
                          printf("\n\tOnly %d - Available In AC Waiting List\n",ts);
                          fclose(fr);
                          return 0;
                      }
                      else if (ts == 0)
                      {
                          printf("\n\tNo Booking In AC Class, Try In Other Trip\n");
                          fclose(fr);
                          return 0;
                      }
                      break;
        }
        fclose(fr);
    return nT;
}

int bkHistory(reservations_t ur)
{
    FILE *fp,*fr;
    booking_history_t hr;
    train_t tr;
    char hfl[]=".\\RRS\\UserHistory\\user_history.binary";
    
    if(!(fp=fopen(hfl,"r+b")))
    {
       fp=fopen(hfl,"wb");
       fclose(fp);
       fp=fopen(hfl,"r+b");
    }

    memset(&hr,0,sizeof(booking_history_t));   
    hr.age=ur.age;
    hr.booking_time=ur.booked_time;
    strcpy(hr.gender,ur.gender);
    strcpy(hr.passenger_name,ur.passenger_name);
    hr.pnr=ur.pnr;
    hr.seatno=ur.seatno;
    strcpy(hr.status,ur.pnr.status);
    strcpy(hr.type,ur.type);
    hr.user_id=ur.user_id;

    if(!(fr=fopen(".\\RRS\\MasterData\\train_details.binary","rb")))
       printf("\n\tRead File Error\n");
    
    fseek(fr,sizeof(int),SEEK_SET);
    while(!feof(fr))
    {
        memset(&tr,0,sizeof(train_t));
        if(fread(&tr,sizeof(train_t),1,fr)<1) break;
        if(hr.pnr.train_no == tr.train_no)
        {
           if(strcmp(hr.pnr.type,"SL") == 0 || strcmp(hr.pnr.type,"SLW") == 0)
              hr.cost=tr.sc_fare;
           if(strcmp(hr.pnr.type,"AC") == 0 || strcmp(hr.pnr.type,"ACW") == 0)
              hr.cost=tr.ac_fare;
        }
    }
    fclose(fr);
    fseek(fp,0,SEEK_END);
    fwrite(&hr,sizeof(booking_history_t),1,fp);
    fclose(fp);
}

int serTiDt(int date)
{
     ttripnode_t *pTrv;
     tnode_t *pTrv1;
     struct tm  te;
     time_t re;
     int cnt=0,jj,ii;
     char buff[100],pb[100];
     char b1[100],b2[100];
     te.tm_mday=date;
     pTrv=rpHead;
     printf("\n");
     while(pTrv)
     {
         if(te.tm_mday == pTrv->ttrip.trip_scheduled_dt.tm_mday)
         {
                re=mktime(&pTrv->ttrip.trip_scheduled_dt);
                memset(buff,0,sizeof(buff));
                memset(pb,0,sizeof(pb));
                sprintf(buff,"%s",ctime(&re));
                buff[strlen(buff)-1]=0;
                for(jj=0,ii=0;jj<strlen(buff);jj++)
                {
                    if(jj<11 || jj>19)
                       pb[ii++]=buff[jj];
                }
                printf("\n\n");
                printf("%2d\t%d\t%s\t\t%d\t%d\t%d\t%d\n",pTrv->ttrip.trip_id,pTrv->ttrip.trip_train_no,pb,pTrv->ttrip.trip_max_sc,pTrv->ttrip.trip_max_ac,pTrv->ttrip.trip_max_wl_sc,pTrv->ttrip.trip_max_wl_ac);
                pTrv1=tHead;
                while(pTrv1)
                {
                     if(pTrv->ttrip.trip_train_no == pTrv1->t.train_no)
                     {
                         memset(b1,0,sizeof(b1));
                         memset(b2,0,sizeof(b2));
                         strftime(b1,100,"%I:%M %p.",&pTrv1->t.departure_time);
                         strftime(b2,100,"%I:%M %p.",&pTrv1->t.arrival_time);
                         printf("\n%d\t%-21s  %-13s  %-14s  %-10s  %-10s  %-2d  %-2d  %-5d  %-5d",pTrv1->t.train_no,pTrv1->t.train_name,pTrv1->t.train_source,pTrv1->t.train_destination,b1,b2,pTrv1->t.sc_total_seats,pTrv1->t.ac_total_seats,pTrv1->t.sc_fare,pTrv1->t.ac_fare);
                         cnt++;
                     }
                     pTrv1=pTrv1->next;
                }
                cnt++;
                printf("\n\n");
         }
         pTrv=pTrv->next;
     }
     if(cnt)
        return 1;
     else
        return 0;
        
}

int serTSch(int num)
{
     ttripnode_t *pTrv;
     time_t re;
     int cnt=0,jj,ii;
     char buff[100],pb[100];
     pTrv=rpHead;
     printf("\n");
     while(pTrv)
     {
         if(num == pTrv->ttrip.trip_train_no)
         {
                re=mktime(&pTrv->ttrip.trip_scheduled_dt);
                memset(buff,0,sizeof(buff));
                memset(pb,0,sizeof(pb));
                sprintf(buff,"%s",ctime(&re));
                buff[strlen(buff)-1]=0;
                for(jj=0,ii=0;jj<strlen(buff);jj++)
                {
                    if(jj<11 || jj>19)
                       pb[ii++]=buff[jj];
                }
                printf("%2d\t%d\t%s\t\t%d\t%d\t%d\t%d\n",pTrv->ttrip.trip_id,pTrv->ttrip.trip_train_no,pb,pTrv->ttrip.trip_max_sc,pTrv->ttrip.trip_max_ac,pTrv->ttrip.trip_max_wl_sc,pTrv->ttrip.trip_max_wl_ac);
                cnt++;
         }
         pTrv=pTrv->next;
     }
     if(cnt)
        return 1;
     else
        return 0;
}

int serDate(int date)
{
     ttripnode_t *pTrv;
     struct tm  te;
     time_t re;
     int cnt=0,jj,ii;
     char buff[100],pb[100];
     te.tm_mday=date;
     pTrv=rpHead;
     printf("\n");
     while(pTrv)
     {
         if(te.tm_mday == pTrv->ttrip.trip_scheduled_dt.tm_mday)
         {
                re=mktime(&pTrv->ttrip.trip_scheduled_dt);
                memset(buff,0,sizeof(buff));
                memset(pb,0,sizeof(pb));
                sprintf(buff,"%s",ctime(&re));
                buff[strlen(buff)-1]=0;
                for(jj=0,ii=0;jj<strlen(buff);jj++)
                {
                    if(jj<11 || jj>19)
                       pb[ii++]=buff[jj];
                }
                printf("%2d\t%d\t%s\t\t%d\t%d\t%d\t%d\n",pTrv->ttrip.trip_id,pTrv->ttrip.trip_train_no,pb,pTrv->ttrip.trip_max_sc,pTrv->ttrip.trip_max_ac,pTrv->ttrip.trip_max_wl_sc,pTrv->ttrip.trip_max_wl_ac);
                cnt++;
         }
         pTrv=pTrv->next;
     }
     if(cnt)
        return 1;
     else
        return 0;
}

int serBrth(int num)
{
     tnode_t *pTrv;
     int cnt=0;
     pTrv=tHead;
     while(pTrv)
     {
         if(num == pTrv->t.train_no)
         {
             printf("\n%d\t%-21s  %-13s  %-14s  %-2d  %-2d  %-5d  %-5d",pTrv->t.train_no,pTrv->t.train_name,pTrv->t.train_source,pTrv->t.train_destination,pTrv->t.sc_total_seats,pTrv->t.ac_total_seats,pTrv->t.sc_fare,pTrv->t.ac_fare);
             cnt++;
         }
         pTrv=pTrv->next;
     }
     if(cnt)
        return 1;
     else
        return 0;
}

int serSD(char *ser1,char *ser2)
{
     tnode_t *pTrv;
     char b1[100],b2[100];
     int cnt=0;
     pTrv=tHead;
     while(pTrv)
     {
         if(strcmp(ser1,pTrv->t.train_source)==0 && strcmp(ser2,pTrv->t.train_destination)==0)
         {
             memset(b1,0,sizeof(b1));
             memset(b2,0,sizeof(b2));
             strftime(b1,100,"%I:%M %p.",&pTrv->t.departure_time);
             strftime(b2,100,"%I:%M %p.",&pTrv->t.arrival_time);
             printf("\n%d\t%-21s  %-13s  %-14s  %-10s  %-10s  %-2d  %-2d  %-5d  %-5d",pTrv->t.train_no,pTrv->t.train_name,pTrv->t.train_source,pTrv->t.train_destination,b1,b2,pTrv->t.sc_total_seats,pTrv->t.ac_total_seats,pTrv->t.sc_fare,pTrv->t.ac_fare);
             cnt++;
         }
         pTrv=pTrv->next;
     }
     if(cnt)
        return 1;
     else
        return 0;
}

int serSrc(char *ser)
{
     tnode_t *pTrv;
     char b1[100],b2[100];
     int cnt=0;
     pTrv=tHead;
     while(pTrv)
     {
         if(strcmp(ser,pTrv->t.train_source)==0)
         {
             memset(b1,0,sizeof(b1));
             memset(b2,0,sizeof(b2));
             strftime(b1,100,"%I:%M %p.",&pTrv->t.departure_time);
             strftime(b2,100,"%I:%M %p.",&pTrv->t.arrival_time);
             printf("\n%d\t%-21s  %-13s  %-14s  %-10s  %-10s  %-2d  %-2d  %-5d  %-5d",pTrv->t.train_no,pTrv->t.train_name,pTrv->t.train_source,pTrv->t.train_destination,b1,b2,pTrv->t.sc_total_seats,pTrv->t.ac_total_seats,pTrv->t.sc_fare,pTrv->t.ac_fare);
             cnt++;
         }
         pTrv=pTrv->next;
     }
     if(cnt)
        return 1;
     else
        return 0;
}

int serDest(char *ser)
{
     tnode_t *pTrv;
     char b1[100],b2[100];
     int cnt=0;
     pTrv=tHead;
     while(pTrv)
     {
         if(strcmp(ser,pTrv->t.train_destination)==0)
         {
             memset(b1,0,sizeof(b1));
             memset(b2,0,sizeof(b2));
             strftime(b1,100,"%I:%M %p.",&pTrv->t.departure_time);
             strftime(b2,100,"%I:%M %p.",&pTrv->t.arrival_time);
             printf("\n%d\t%-21s  %-13s  %-14s  %-10s  %-10s  %-2d  %-2d  %-5d  %-5d",pTrv->t.train_no,pTrv->t.train_name,pTrv->t.train_source,pTrv->t.train_destination,b1,b2,pTrv->t.sc_total_seats,pTrv->t.ac_total_seats,pTrv->t.sc_fare,pTrv->t.ac_fare);
             cnt++;
         }
         pTrv=pTrv->next;
     }
     if(cnt)
        return 1;
     else
        return 0;
}

int chkFun(char *usr,char *pwd)
{
    FILE *fp;
    user_t ur;
    int u1,p1,u2,p2;
    u1=strlen(usr);
    p1=strlen(pwd);
    if(!(fp=fopen(".\\RRS\\MasterData\\user_details.binary","rb")))
       printf("\n\t\tRead File Error\n");
       
    fseek(fp,sizeof(int),SEEK_SET);
    memset(&ur,0,sizeof(user_t));
    fread(&ur,sizeof(user_t),1,fp);
    u2=strlen(ur.user_name);
    p2=strlen(ur.passwd);
    if(u1 == u2 && p1==p2)
    {
          if(strcmp(usr,ur.user_name) == 0 && strcmp(pwd,ur.passwd) == 0)
          {
             uID=ur.user_id;
             fclose(fp);
             return ADM;
          }
    }
    while(!feof(fp))
    {
        memset(&ur,0,sizeof(user_t));
        if(fread(&ur,sizeof(user_t),1,fp)<1) break;
        u2=strlen(ur.user_name);
        p2=strlen(ur.passwd);
        if(u1 == u2 && p1==p2)
        {
              if(strcmp(usr,ur.user_name) == 0 && strcmp(pwd,ur.passwd) == 0)
              {
                 uID=ur.user_id;
                 fclose(fp);
                 return USR;
              }
        }
    }
    fclose(fp);
    return NOACC;
}

void ullist()
{
    FILE *fu;
    unode_t *pTemp,*pTrv;
    user_t ur;
    
    if(!(fu=fopen(".\\RRS\\MasterData\\user_details.binary","rb")))
       printf("\n\t\tRead File Error\n");

    fseek(fu,0,SEEK_END);
    fseek(fu,(-1*sizeof(user_t)),SEEK_CUR);
           
    while(!feof(fu))
    {
        memset(&ur,0,sizeof(user_t));
        if(fread(&ur,sizeof(user_t),1,fu)<1) break;
        pTemp=(unode_t *)malloc(sizeof(unode_t));
        pTemp->u=ur;
        if(uHead)
        {
           pTrv=uHead;
           while(pTrv->next)
               pTrv=pTrv->next;
           pTemp->next=pTrv->next;
           pTrv->next=pTemp;
        }
        else
        {
            pTemp->next=uHead;
            uHead=pTemp;
        }
    }
}

void tllist()
{
    FILE *ft;
    tnode_t *pTemp,*pTrv;
    train_t ut;
    if(!(ft=fopen(".\\RRS\\MasterData\\train_details.binary","rb")))
       printf("\n\t\tRead File Error\n");

    fseek(ft,0,SEEK_END);
    fseek(ft,(-1*sizeof(train_t)),SEEK_CUR);
           
    while(!feof(ft))
    {
        memset(&ut,0,sizeof(train_t));
        if(fread(&ut,sizeof(train_t),1,ft)<1) break;
        pTemp=(tnode_t *)malloc(sizeof(tnode_t));
        pTemp->t=ut;
        if(tHead)
        {
           pTrv=tHead;
           while(pTrv->next)
               pTrv=pTrv->next;
           pTemp->next=pTrv->next;
           pTrv->next=pTemp;
        }
        else
        {
            pTemp->next=tHead;
            tHead=pTemp;
        }
    }
}

void tripllist()
{
    FILE *ft;
    ttripnode_t *pTemp,*pTrv;
    train_trip_t tr;
    
    if(!(ft=fopen(".\\RRS\\MasterData\\train_trip.binary","rb")))
        printf("\n\tFile Read Error\n");

    fseek(ft,sizeof(int),SEEK_SET);
           
    while(!feof(ft))
    {
        memset(&tr,0,sizeof(train_trip_t));
        if(fread(&tr,sizeof(train_trip_t),1,ft)<1) break;
        pTemp=(ttripnode_t *)malloc(sizeof(ttripnode_t));
        pTemp->ttrip=tr;
        if(rpHead)
        {
           pTrv=rpHead;
           while(pTrv->next)
               pTrv=pTrv->next;
           pTemp->next=pTrv->next;
           pTrv->next=pTemp;
        }
        else
        {
            pTemp->next=rpHead;
            rpHead=pTemp;
        }
    }
}

void resTrain()
{
     FILE *fr,*fp;
     train_trip_t tr;
     reservations_t re,hD;
     head_t hR;
     int n;
     char dR[100],fl[100],sr[10]="ABCDEFGH";
     
     if(!(fr=fopen(".\\RRS\\MasterData\\train_trip.binary","rb")))
        printf("\n\tFile Open Error\n");
        
     fread(&n,sizeof(int),1,fr);
     printf("\n\tNumber Of Records: %d\n\n",n);
     
     while(!feof(fr))
     {
        memset(&tr,0,sizeof(train_trip_t));
        if(fread(&tr,sizeof(train_trip_t),1,fr)<1) break;
        memset(dR,0,sizeof(dR));
        memset(fl,0,sizeof(fl));
        re.pnr.train_no=tr.trip_train_no;
        re.pnr.trip_id=tr.trip_id;
        sprintf(dR,".\\RRS\\TrainData\\%d",re.pnr.train_no);
        sprintf(fl,".\\RRS\\TrainData\\%d\\%d_reservations.binary",re.pnr.train_no,re.pnr.trip_id);
        mkdir(dR);
        if(!(fp=fopen(fl,"r+b")))
        {
             fp=fopen(fl,"wb");
             fclose(fp);
             fp=fopen(fl,"r+b");
        }
        memset(&hR,0,sizeof(head_t));
        hR.n_seatsSL=12;
        hR.n_seatsAC=8;
        hR.n_seatsSLW=4;
        hR.n_seatsACW=4;
        memset(hR.seatNSL,'0',sizeof(hR.seatNSL));
        memset(hR.seatNAC,'0',sizeof(hR.seatNAC));
        memset(hR.seatNSLW,'0',sizeof(hR.seatNSLW));
        memset(hR.seatNACW,'0',sizeof(hR.seatNACW));
        hR.seatno=0;
        memset(hR.type,0,sizeof(hR.type));
        fseek(fp,0,SEEK_SET);
        fwrite(&hR,sizeof(head_t),1,fp);
        memset(&hD,0,sizeof(reservations_t));
        fwrite(&hD,sizeof(reservations_t),1,fp);
        fclose(fp);  
     }
     fclose(fr);
     printf("\n\tTotal Train Number Folders & Files Are Created\n");
}

void sheduleTrain()
{
    FILE *ft,*fr;
    train_trip_t tr;
    train_t ur;
    int uqId=1,date,ii,cnt,r;
    char buff[100],cnv[3];
    time_t curtime;
    struct tm *loctime;
    time_t now;   /// taking 2 variable for time_t datatype

    for(ii=0;ii<5;ii++)
    {
        if(!(ft=fopen(".\\RRS\\MasterData\\train_trip.binary","r+b")))
        {
             ft=fopen(".\\RRS\\MasterData\\train_trip.binary","wb");
             fclose(ft);
             ft=fopen(".\\RRS\\MasterData\\train_trip.binary","r+b");
        }
        
        if(!(fr=fopen(".\\RRS\\MasterData\\train_details.binary","rb")))
               printf("\n\tRead File Error\n");
        
        cnt=0;
        fread(&r,sizeof(int),1,fr);
        while(!feof(fr) && cnt < r)
        {
            memset(&tr,0,sizeof(train_trip_t));
            memset(&ur,0,sizeof(train_t));
            tr.trip_id=uqId;
            if(fread(&ur,sizeof(train_t),1,fr)<1) break;
            tr.trip_train_no=ur.train_no;
     
            curtime=time(NULL);
            loctime = localtime(&curtime);
            strftime(buff,100,"%A%B%d",loctime);
            cnv[0]=buff[strlen(buff)-2];
            cnv[1]=buff[strlen(buff)-1];
            cnv[2]=0;
            sscanf(cnv,"%d",&date);
            time(&now);
            tr.trip_scheduled_dt=(*localtime(&now));  /// converting into localtime format
            tr.trip_scheduled_dt.tm_mday=(date+ii+1);
            
            tr.trip_max_sc=20;
            tr.trip_max_ac=8;
            tr.trip_max_wl_sc=4;
            tr.trip_max_wl_ac=4;
            
            fseek(ft,0,SEEK_SET);
            fwrite(&uqId,sizeof(int),1,ft);
            uqId++;
            fseek(ft,0,SEEK_END);
            fwrite(&tr,sizeof(train_trip_t),1,ft);
            endTrip(tr);
            cnt++;
        }
        fclose(fr);
        fclose(ft);
    }
}

void endTrip(train_trip_t tr)
{
     time_t re;
     char buff[100];
     int ii,jj;
     re=mktime(&tr.trip_scheduled_dt);
     memset(buff,0,sizeof(buff));
     memset(eTrip,0,sizeof(eTrip));
     sprintf(buff,"%s",ctime(&re));
     buff[strlen(buff)-1]=0;
     for(jj=0,ii=0;jj<strlen(buff);jj++)
     {
         if(jj<11 || jj>19)
            eTrip[ii++]=buff[jj];
     }
}

void dispTrainTrip()
{
    FILE *ft;
    train_trip_t tr;
    time_t re;
    int uqId,jj,ii;
    char buff[100],pb[100];
    if(!(ft=fopen(".\\RRS\\MasterData\\train_trip.binary","rb")))
        printf("\n\tFile Read Error\n");
    
    fread(&uqId,sizeof(int),1,ft);
    printf("\n\t\tTotal Records Are: %d\n\n",uqId);
    while(!feof(ft))
    {
        memset(&tr,0,sizeof(train_trip_t));
        if(fread(&tr,sizeof(train_trip_t),1,ft)<1) break;
        re=mktime(&tr.trip_scheduled_dt);
        memset(buff,0,sizeof(buff));
        memset(pb,0,sizeof(pb));
        sprintf(buff,"%s",ctime(&re));
        buff[strlen(buff)-1]=0;
        for(jj=0,ii=0;jj<strlen(buff);jj++)
        {
            if(jj<11 || jj>19)
               pb[ii++]=buff[jj];
        }
        printf("%2d\t%d\t%s\t\t%d\t%d\t%d\t%d\n",tr.trip_id,tr.trip_train_no,pb,tr.trip_max_sc,tr.trip_max_ac,tr.trip_max_wl_sc,tr.trip_max_wl_ac);
    }
    
    fclose(ft); 
}

int addTrain()
{
     FILE *ft;
     train_t tr;
     struct tm t;
     int uqId;
     if(!(ft=fopen(".\\RRS\\MasterData\\train_details.binary","r+b")))
     {
         ft=fopen(".\\RRS\\MasterData\\train_details.binary","wb");
         fclose(ft);
         ft=fopen(".\\RRS\\MasterData\\train_details.binary","r+b");
     }
     fread(&uqId,sizeof(int),1,ft);
     if(uqId<=5)
     {
           printf("\n\tAlready 5 Train Details Available\n");
           return 0;
     }
     uqId++;

     memset(&tr,0,sizeof(train_t));
     printf("\n\tTrain Number: ");
     scanf("%d",&tr.train_no);
     
     while(1)
     {
         printf("\tTrain Name: ");
         fflush(stdin);
         scanf("%[^\n]s",tr.train_name);
         if(strlen(tr.train_name)<30)
           break;
     }
     
     while(1)
     {
         printf("\tSource: ");
         fflush(stdin);
         scanf("%[^\n]s",tr.train_source);
         if(strlen(tr.train_source)<30)
           break;
     }
     
     while(1)
     {
         printf("\tDestination: ");
         fflush(stdin);
         scanf("%[^\n]s",tr.train_destination);
         if(strlen(tr.train_destination)<30)
           break;
     }
     
     printf("\tDeparture Hour: ");
     scanf("%d",&tr.departure_time.tm_hour);
     printf("\tDeparture Minutes: ");
     scanf("%d",&tr.departure_time.tm_min);

     tr.departure_time.tm_mday=18; //day of the month 
     tr.departure_time.tm_mon=8; //month 
     tr.departure_time.tm_year=00; //year does not include century 
     tr.departure_time.tm_wday=3; //day of the week 
     tr.departure_time.tm_yday=0; //does not show in asctime 
     tr.departure_time.tm_isdst=0; //is Daylight SavTime, does not show in asctime /* converts structure to null terminates string */ 
     
     printf("\tArrival Hour: ");
     scanf("%d",&tr.arrival_time.tm_hour);
     printf("\tArrival Minutes: ");
     scanf("%d",&tr.arrival_time.tm_min);
     tr.arrival_time.tm_mday=18; //day of the month 
     tr.arrival_time.tm_mon=8; //month 
     tr.arrival_time.tm_year=00; //year does not include century 
     tr.arrival_time.tm_wday=3; //day of the week 
     tr.arrival_time.tm_yday=0; //does not show in asctime 
     tr.arrival_time.tm_isdst=0; //is Daylight SavTime, does not show in asctime /* converts structure to null terminates string */ 
          
     tr.sc_total_seats=12;
     tr.ac_total_seats=8;
     printf("\tSC Fare: ");
     scanf("%d",&tr.sc_fare);
     printf("\tAC Fare: ");
     scanf("%d",&tr.ac_fare);
     
     fseek(ft,0,SEEK_SET);
     fwrite(&uqId,sizeof(int),1,ft);
     fseek(ft,0,SEEK_END);
     fwrite(&tr,sizeof(train_t),1,ft);
     fclose(ft);
     return 1;
}

void dispTrain()
{
    FILE *ft;
    train_t tr;
    int uqId;
    char b1[100],b2[100];
    
    if(!(ft=fopen(".\\RRS\\MasterData\\train_details.binary","rb")))
       printf("\n\t\tRead File Error\n");
    
    fread(&uqId,sizeof(int),1,ft);
    printf("\n\t\tTotal Records Are: %d\n",uqId);
    while(!feof(ft))
    {
        memset(&tr,0,sizeof(train_t));
        memset(b1,0,sizeof(b1));
        memset(b2,0,sizeof(b2));
        if(fread(&tr,sizeof(train_t),1,ft)<1) break;
        strftime(b1,100,"%I:%M %p.",&tr.departure_time);
        strftime(b2,100,"%I:%M %p.",&tr.arrival_time);
        printf("\n%d\t%-21s  %-13s  %-14s  %-10s  %-10s  %-2d  %-2d  %-5d  %-5d",tr.train_no,tr.train_name,tr.train_source,tr.train_destination,b1,b2,tr.sc_total_seats,tr.ac_total_seats,tr.sc_fare,tr.ac_fare);
    }
    fclose(ft); 
}

int addUser()
{
    FILE *fu;
    user_t ur,tr;
    int uqId,ii=0,cnt,ch;
    
    if(!(fu=fopen(".\\RRS\\MasterData\\user_details.binary","r+b")))
    {
         fu=fopen(".\\RRS\\MasterData\\user_details.binary","wb");
         fclose(fu);
         fu=fopen(".\\RRS\\MasterData\\user_details.binary","r+b");
    }
    fread(&uqId,sizeof(int),1,fu);
    if(uqId<=5)
    {
       printf("\n\tAlready 5 Users, No Users to Create\n");
       return 0;
    }
    uqId++;
    memset(&ur,0,sizeof(user_t));
    ur.user_id=uqId;
    
    while(1)
    {
        cnt=0;
        fseek(fu,4,SEEK_SET);
        memset(ur.user_name,0,sizeof(ur.user_name));
        printf("\n\tUser Name: ");
        fflush(stdin);
        scanf("%[^\n]s",ur.user_name);
        if(strlen(ur.user_name)>30)
        {
           printf("\n\tThe Username Atleat 30 Characters\n");
           continue;
        }
        while(!feof(fu))
        {
             memset(&tr,0,sizeof(user_t));
             fread(&tr,sizeof(user_t),1,fu);
             if(strcmp(tr.user_name,ur.user_name) == 0)
             {
                 printf("\n\tUser Name Already Exist");
                 cnt=1;
                 break;
             }
        }
        if(cnt == 0)
           break;
    }
    
    while(1)
    {
        memset(ur.passwd,0,sizeof(ur.passwd));
        printf("\tPassword (Atleast 6 - Charaters): ");
        fflush(stdin);
        scanf("%s",ur.passwd);
        if(strlen(ur.passwd)<=6)
           break;
    }

    fflush(stdin);
    printf("\tGender (Male 0/Female 1): ");
    scanf("%d",&ch);
    if(ch == 0)
       ur.gender = Male;
    else
       ur.gender = Female;

    fflush(stdin);
    while(1)
    {
        printf("\tAge (> 18 or <150): ");
        scanf("%d",&ur.age);
        if(ur.age>18 && ur.age<150)
           break;
    }
    
    while(1)
    {
       printf("\tAddress: ");
       fflush(stdin);
       scanf("%[^\n]s",ur.address);
       if(strlen(ur.address)>99)
       {
          printf("\n\tThe Address Should Be Atleast 99 Characters\n");
          continue;
       }
       else
          break;
    }
    
    while(1)
    {
       printf("\tAccount Number: ");
       fflush(stdin);
       scanf("%[^\n]s",ur.account);
       if(strlen(ur.account)>14)
       {
          printf("\n\tThe Account Number Should Be Atleast 14 Characters\n");
          continue;
       }
       else
          break;
    }
    
    fseek(fu,0,SEEK_SET);
    fwrite(&uqId,sizeof(int),1,fu);
    fseek(fu,0,SEEK_END);
    fwrite(&ur,sizeof(user_t),1,fu);
    fclose(fu);
    return 1;
}

void disAll()
{
    FILE *fu;
    user_t ur;
    int uqId;
    
    if(!(fu=fopen(".\\RRS\\MasterData\\user_details.binary","rb")))
       printf("\n\t\tRead File Error\n");
    
    fread(&uqId,sizeof(int),1,fu);
    printf("\n\t\tTotal Records Are: %d\n",uqId);
    while(!feof(fu))
    {
        memset(&ur,0,sizeof(user_t));
        if(fread(&ur,sizeof(user_t),1,fu)<1) break;
        printf("\n%-3d  %-6s  %-30s  %-5d  %-3d  %-40s  %s",ur.user_id,ur.passwd,ur.user_name,ur.gender,ur.age,ur.address,ur.account);
    }
    
    fclose(fu); 
}

void addLl()
{
    FILE *tp;

    if((tp=fopen(".\\RRS\\MasterData\\user_details.binary","rb")))
    {
      user_t ut;
      unode_t *uTemp,*pTrv;
      fseek(tp,sizeof(int),SEEK_SET);
      while(!feof(tp))
      {
         memset(&ut,0,sizeof(user_t));
          if(fread(&ut,sizeof(user_t),1,tp)<1) break;
          uTemp=(unode_t *)malloc(sizeof(unode_t));
          uTemp->u=ut;
          if(uHead)
          {
             pTrv=uHead;
             while(pTrv->next!='\0')
                 pTrv=pTrv->next;
             uTemp->next=pTrv->next;
             pTrv->next=uTemp;
          }
          else
          {
              uTemp->next=uHead;
              uHead=uTemp;
          }
          
      }
      fclose(tp);
    }
    
    if((tp=fopen(".\\RRS\\MasterData\\train_details.binary","rb")))
    {
      train_t tt;
      tnode_t *tTemp,*pTrv1; 
      fseek(tp,sizeof(int),SEEK_SET);
      while(!feof(tp))
      {
          memset(&tt,0,sizeof(train_t));
          if(fread(&tt,sizeof(train_t),1,tp)<1) break;
          tTemp=(tnode_t *)malloc(sizeof(tnode_t));
          tTemp->t=tt;
          if(tHead)
          {
             pTrv1=tHead;
             while(pTrv1->next!='\0')
                 pTrv1=pTrv1->next;
             tTemp->next=pTrv1->next;
             pTrv1->next=tTemp;
          }
          else
          {
              tTemp->next=tHead;
              tHead=tTemp;
          }
          
      }
      fclose(tp);
    }
    
    if((tp=fopen(".\\RRS\\MasterData\\train_trip.binary","rb")))
    {
      train_trip_t rt;
      ttripnode_t *rTemp,*pTrv2;
      fseek(tp,sizeof(int),SEEK_SET);
      
      while(!feof(tp))
      {
            memset(&rt,0,sizeof(train_trip_t));
            if(fread(&rt,sizeof(train_trip_t),1,tp)<1) break;
            rTemp=(ttripnode_t *)malloc(sizeof(ttripnode_t));
            rTemp->ttrip=rt;
            endTrip(rt);
            if(rpHead)
            {
               pTrv2=rpHead;
               while(pTrv2->next)
                   pTrv2=pTrv2->next;
               rTemp->next=pTrv2->next;
               pTrv2->next=rTemp;
            }
            else
            {
                rTemp->next=rpHead;
                rpHead=rTemp;
            }
      }
      fclose(tp);
    }
}

