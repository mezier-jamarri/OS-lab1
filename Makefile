# list/Makefile
#
# Makefile for list implementation and test file.
#
# <Author>

list: main.c list.c
	gcc -Wall -o list main.c list.c

clean:
	rm -f list