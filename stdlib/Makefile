
CC ?= gcc
CFLAGS += -D_REENTRANT -fPIC 
LDFLAGS :=  -shared -llua -lrt

SRC = $(wildcard *.c)
OBJS = $(SRC:%.c=%.o)
TARGET = std.so

$(TARGET): $(OBJS)
	$(CC)  $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS) 
	cp $(TARGET) ../test/

$(OBJS): %.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@ 
