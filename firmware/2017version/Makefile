#makefile
ghmain:	ghmain.o ghutils.o ghcontrol.o hshbme280.o
	gcc -g -o ghmain ghmain.o ghutils.o ghcontrol.o hshbme280.o -lwiringPi
ghmain.o:	ghmain.c ghutils.h ghcontrol.h
	gcc -g -c ghmain.c
ghutils.o:	ghutils.c ghutils.h ghcontrol.h
	gcc -g -c ghutils.c
ghcontrol.o:	ghcontrol.c ghcontrol.h hshbme280.h
	gcc -g -c ghcontrol.c
hshbme280.o:	hshbme280.c hshbme280.h
	gcc -g -c hshbme280.c
