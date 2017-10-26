CC = gcc
CFLAGS = -I. -std=c99 -Wall

all: gendata kmeans

gendata: gendata.c
	$(CC) -o $@ $^ $(CFLAGS) -lm

kmeans: kmeans.c
	$(CC) -o $@ $^ $(CFLAGS) -lm

clean:
	rm -f gendata kmeans

