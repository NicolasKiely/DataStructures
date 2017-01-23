CC=gcc -Wall -std=c99

all: c/LinkedLists/bin/linkedLists c/LinkedLists/bin/sortedLinkedLists \
	c/Vectors/bin/vectorLists c/Vectors/bin/sortedVectorLists \
	c/Trees/bin/tree


# Linked Lists
c/LinkedLists/bin/linkedLists: c/LinkedLists/linkedLists.c
	$(CC) c/LinkedLists/linkedLists.c -o c/LinkedLists/bin/linkedLists

c/LinkedLists/bin/sortedLinkedLists: c/LinkedLists/sortedLinkedLists.c
	$(CC) c/LinkedLists/sortedLinkedLists.c -o c/LinkedLists/bin/sortedLinkedLists


# Vectors
c/Vectors/bin/vectorLists: c/Vectors/vectorLists.c
	$(CC) c/Vectors/vectorLists.c -o c/Vectors/bin/vectorLists

c/Vectors/bin/sortedVectorLists: c/Vectors/sortedVectorLists.c
	$(CC) c/Vectors/sortedVectorLists.c -o c/Vectors/bin/sortedVectorLists


# Trees
c/Trees/bin/tree: c/Trees/tree.c
	$(CC) c/Trees/tree.c -o c/Trees/bin/tree
