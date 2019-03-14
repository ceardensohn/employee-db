CC = gcc
CFLAGS = -g -Wall -Wextra -std=c11

TARGET = employee_db

LIB = readfile.o

SRC = $(TARGET).c 

all: $(TARGET)

$(TARGET): $(SRC) $(LIB)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIB)

$(LIB): readfile.c readfile.h
	$(CC) $(CFLAGS) -c readfile.c

clean:
	$(RM) $(TARGET) $(LIB)
