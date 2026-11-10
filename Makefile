
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

.PHONY: all clean

all: sender receiver

sender: udp_sender.c
	$(CC) $(CFLAGS) udp_sender.c -o sender

receiver: udp_receiver.c
	$(CC) $(CFLAGS) udp_receiver.c -o receiver

clean:
	rm -f sender receiver
