CC=gcc -Wall -std=c99

all: c/LinkedLists/bin/linkedLists c/LinkedLists/bin/sortedLinkedLists

c/LinkedLists/bin/linkedLists: c/LinkedLists/linkedLists.c
	$(CC) c/LinkedLists/linkedLists.c -o c/LinkedLists/bin/linkedLists

c/LinkedLists/bin/sortedLinkedLists: c/LinkedLists/sortedLinkedLists.c
	$(CC) c/LinkedLists/sortedLinkedLists.c -o c/LinkedLists/bin/sortedLinkedLists
