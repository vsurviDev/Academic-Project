
OBJS = Client.o Comm.o DataBase.o Server.o
	
ExeProject1.out: ProjectArchieve.a
	gcc -o ExeProject1.out ProjectArchieve.a

ProjectArchieve.a: $(OBJS)
	ar rv ProjectArchieve.a $(OBJS)

Client.o: Client.c 
	gcc -c Client.c 
Comm.o: Comm.c 
	gcc -c Comm.c 
Server.o: Server.c
	gcc -c Server.c
DataBase.o: DataBase.c 
	gcc -c DataBase.c 

clean:
	clear 
	ls
	ar -tv ProjectArchieve.a
	rm *.o *.a *.out
	ls
	touch *
