CC = gcc

CFLAGS = -Wall -I./inc/

SRCDIR = ./src

SRC += $(SRCDIR)/tree.c

TARGET = tree_main

all: $(TARGET).c
	 $(CC) $(CFLAGS) $(TARGET).c $(SRC) -o $(TARGET)
	 
run: $(TARGET)
	 ./$(TARGET)
