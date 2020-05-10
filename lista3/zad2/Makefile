# Makefile

all: main clean

main: main.o Device.o Ethernet.o Field.o Frame.o
	g++ -o main main.o Device.o Ethernet.o Field.o Frame.o

main.o: main.cpp
	g++ -c main.cpp

Device.o: src/Device.cpp src/Device.h
	g++ -c src/Device.cpp -o Device.o

Ethernet.o: src/Ethernet.cpp src/Ethernet.h
	g++ -c src/Ethernet.cpp -o Ethernet.o

Field.o: src/Field.cpp src/Field.h
	g++ -c src/Field.cpp -o Field.o

Frame.o: src/Frame.cpp src/Frame.h
	g++ -c src/Frame.cpp -o Frame.o

clean:
	rm -f *.o
