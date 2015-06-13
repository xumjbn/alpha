
CC ?= gcc
CFLAGS += -D_REENTRANT -D_POSIX_SOURCE -fPIC 
LDFLAGS :=  -shared -llua

SRC = $(wildcard *.c)
OBJS = $(SRC:%.c=%.o)
TARGET = std.so

$(TARGET): $(OBJS)
	$(CC)  $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS) 
	cp $(TARGET) ../test/

$(OBJS): %.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@ 
