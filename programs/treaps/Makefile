CC = gcc

CFLAGS = -Wall -I./inc/

SRCDIR = ./src

SRC += $(SRCDIR)/treaps.c

TARGET = treaps_main

all: $(TARGET).c
	 $(CC) $(CFLAGS) $(TARGET).c $(SRC) -o $(TARGET)
	 
run: $(TARGET)
	 ./$(TARGET)
