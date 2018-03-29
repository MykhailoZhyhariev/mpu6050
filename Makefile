CC=gcc
CFLAGS=-Wall -O3
LDFLAGS=-lwiringPi -lpthread -std=c99
PREFIX=mpu6050
SOURCES=main.c $(PREFIX)_high.c $(PREFIX)_low.c
EXECUTABLE=main

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE) $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE)
