# Project: N-Queen
# Makefile para gerar o executavel para o teste das classes
# Queen, main, Lista, Nodo
#Criado por Lucas Victor es71512
# Criado em 26/04/2015

all: Queen.o main.o
	g++ -o main Queen.o main.o

Queen.o: Queen.h Queen.cpp
	g++ -c Queen.cpp

main.o: Queen.o main.cpp
	g++ -c main.cpp

clean:
	rm main *.o *.exe
