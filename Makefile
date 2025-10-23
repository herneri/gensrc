CC = gcc
SRC = src/main.c src/preprocess.c src/param.c

default: $(SRC)
	$(CC) $^ -o gensrc
