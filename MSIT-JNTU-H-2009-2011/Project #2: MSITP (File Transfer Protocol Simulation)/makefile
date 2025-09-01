
SCC = serverMain.c
SOBJ = serverMain.o
CCC = clientMain.c
COBJ = clientMain.o

all: serverMain.o clientMain.o server client

server: serlib.a
	gcc -g -o server serlib.a

client: clilib.a
	gcc -g -o client clilib.a

serlib.a: $(SOBJ)
	ar rv serlib.a $(SOBJ)
  
clilib.a: $(SOBJ)
	ar rv clilib.a $(COBJ)

SOBJ: $(SCC)
	gcc -c $(SCC)

COBJ: $(CCC)
	gcc -c $(CCC)

clean:
	clear
	ls -l
	ar -tv serlib.a
	ar -tv clilib.a	
	rm *.o *.a *.txt client server
	ls -l
	touch *

clean1:
	rm -r Database 
