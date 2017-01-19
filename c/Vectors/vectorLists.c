/**
 * Demonstrates basic linked lists
 * Reads commands from stdin, where each command is in the form:
 *  + <word>: Adds word to linked list
 *  - <word>: removes word from linked list
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MIN_SIZE 4

int main(int argc, char *argv[]){
  int listSize = MIN_SIZE; // Number of allocated spaces in list
  int listLen = 0; // Number of items stored in list
  char **vectorList = malloc(listSize * sizeof(char *));

  while (true){
    size_t bufSize = 0; // Buffer size
    char *line = NULL; // Line input
    ssize_t ret = getline(&line, &bufSize, stdin);

    // Parse line into copy buffer
    if (ret <= 0)
      break;
    char *buf = malloc(bufSize);

    int i;
    for (i=1; i<bufSize && line[i]!='\0' && line[i]!='\n'; i++)
      buf[i-1] = line[i];
    buf[i-1] = '\0';

    // Get command from original line buffer and free it
    char cmd = line[0];
    free(line);

    switch (cmd){
    case '?':
      // Query vector size
      printf("Vector size: %d\t# items: %d\n", listSize, listLen);
      free(buf);
      break;

    case '+':
      // Add node
      if (listLen+1 >= listSize){
        // Resize vector
        listSize *= 2;
        vectorList = realloc(vectorList, listSize*sizeof(char *));
      }
      vectorList[listLen] = buf;
      listLen += 1;
      break;

    case '-':
      // Free node
      for (i=0; i<listLen; i++){
        if (!strcmp(vectorList[i], buf)){
          // Match found, delete string
          free(vectorList[i]);
          listLen -= 1;
          break;
        }
      }
      // Move nodes back
      for (;i<=listLen; i++){
        if (i+1 < listSize){
          vectorList[i] = vectorList[i+1];
        } else {
          // Handle edge case where vector list is full
          vectorList[i] = NULL;
        }
      }
      free(buf);

      // Check if vector needs to shrink
      if (listSize>MIN_SIZE && 1+(listSize/4)>listLen){
        listSize /= 2;
        vectorList = realloc(vectorList, listSize*sizeof(char *));
      }
      break;

    default:
      fprintf(stderr, "Error: Line should start with + or -\n");
      free(buf);
    }
  }


  // Print and free vector list
  printf("Vector size: %d\t# items: %d\n", listSize, listLen);
  for (int i=0; i<listLen; i++){
    printf("  ::: %s\n", vectorList[i]);
    free(vectorList[i]);
  }
  free(vectorList);
}
