runRoyals.out: royals.o RunRoyals.o
	g++ -Wall -ansi -g -o runRoyals.out royals.o RunRoyals.o 

royals.o: royals.cpp royals.h RunRoyals.h QuadraticProbing.h 
	g++ -Wall -ansi -g -c royals.cpp

RunRoyals.o: RunRoyals.cpp RunRoyals.h royals.h CPUTimer.h 
	g++ -Wall -ansi -g -c RunRoyals.cpp

clean:
	rm -f runRoyals.out royals.o RunRoyals.o 
