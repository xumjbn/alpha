
export CC = gcc
export CFLAGS := -Wall -Wextra -std=c99 -pipe -DDEBUG -g -D_GUN_SOURCE

STD_DIR := stdlib
SRC = $(wildcard *.c)
OBJS = $(SRC:%.c=%.o)
TARGET = alpha

.PHONY: all clean
all: std.so alpha

std.so:
	$(MAKE) -C $(STD_DIR)

alpha: $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

#$(OBJS): %.o:%.c
#	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -rf $(OBJS) alpha ./test/std.so
	rm -rf $(wildcard ./$(STD_DIR)/*.o) ./$(STD_DIR)/*.so
