default:build

build:encoder

encoder:encoder.o
	gcc -Wall -o encoder encoder.o

encoder.o:encoder.c
	gcc -Wall -c encoder.c 

run:encoder
	./encoder

clean: 
	rm encoder.o encoder