CC=gcc
ARG=-g -Wall -Wpadded -Wextra

all:liboperation.so
	 $(CC) $(ARG) main.c -o main -L. -loperation -lm

liboperation.so:
	$(CC) $(ARG) -fPIC -c operation.c
	$(CC) $(ARG) -o liboperation.so -shared operation.o

clean:
	rm -fv liboperation.so operation.o main
