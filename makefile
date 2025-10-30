all: main

main: Main.o
	g++ Main.o -o main

Main.o: Main.cpp 
	g++ -c Main.cpp

clean:
	rm -f *.o main