CC = gcc
SRC = src/*.c

default: $(SRC)
	$(CC) $^ -o gensrc

debug: $(SRC)
	$(CC) $^ -g -o gendebug
