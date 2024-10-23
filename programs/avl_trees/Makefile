CC = gcc

CFLAGS = -Wall -I./inc/

SRCDIR = ./src

SRC += $(SRCDIR)/tree.c

TARGET = avl_trees

all: $(TARGET).c
	 $(CC) $(CFLAGS) $(TARGET).c $(SRC) -o $(TARGET)
	 
run: $(TARGET)
	 ./$(TARGET)

clean: $(TARGET)
		rm $(TARGET)
