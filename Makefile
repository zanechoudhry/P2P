#Zane Choudhry
#Joshua Vong
#EECE 446 Fall 2020
EXE = peer registry
CFLAGS = -Wall
CXXFLAGS = -Wall
LDLIBS =
CC = gcc
CXX = g++

.PHONY: all
all: $(EXE)

# Implicit rules defined by Make, but you can redefine if needed

peer: peer.c
	$(CC) $(CFLAGS) peer.c $(LDLIBS) -o peer

registry: registry.c
	$(CC) $(CFLAGS) registry.c $(LDLIBS) -o registry



.PHONY: clean
clean:
	rm -f $(EXE)

