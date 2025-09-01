
CC = clientTFTP.c creatPacket.c errFile.c processCliSrv.c strConct.c
OBJS = clientTFTP.o creatPacket.o errFile.o processCliSrv.o strConct.o

exeTFTP: arch.a
	gcc -g -o exeTFTP arch.a

arch.a: $(OBJS) 
	ar rv arch.a $(OBJS)

$(OBJS): $(CC)
	gcc -c $(CC)

clean:
	clear
	ls
	ar -tv arch.a
	rm *.o *.a exeTFTP
	ls
	touch *
