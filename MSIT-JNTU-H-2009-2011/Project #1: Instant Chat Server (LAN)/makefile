
SCC = Server.c dispError.c userLinkedList.c serverProcess.c createLog.c
SOBJ = Server.o dispError.o userLinkedList.o serverProcess.o createLog.o
CCC = Client.c dispError.c addfriend.c exit.c friendlist.c login.c logout.c registration.c
COBJ = Client.o dispError.o addfriend.o exit.o friendlist.o login.o logout.o registration.o

all: Server.o Client.o dispError.o userLinkedList.o serverProcess.o createLog.o addfriend.o exit.o friendlist.o login.o logout.o registration.o server client

server: serlib.a
	gcc -g -o server serlib.a -lpthread

client: clilib.a
	gcc -g -o client clilib.a -lpthread

serlib.a: $(SOBJ)
	ar rv serlib.a $(SOBJ)
  
clilib.a: $(COBJ)
	ar rv clilib.a $(COBJ)

SOBJ: $(SCC)
	gcc -c $(SCC) -lpthread

COBJ: $(CCC)
	gcc -c $(CCC) -lpthread

clean:
	clear
	ls -l
	ar -tv serlib.a
	ar -tv clilib.a	
	rm *.o *.a temp.txt client server
	ls -l
	touch *

clean1:
	rm -r usrDataBase Downloads

clean2:
	rm -r PersonalFolder
