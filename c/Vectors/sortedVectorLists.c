/**
 * Demonstrates sorted dynamic arrays
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


/** Dynamic array data structure */
typedef struct {
  int size;    // Allocated size
  int len;     // Number of items stored
  char **list; // List
} Vector;

/** Reads input and stores in references to variables */
bool fetchInput(size_t *bufSize, char **buf, char *cmd){
  char *line = NULL;
  *bufSize = 0;

  // Read next line
  ssize_t ret = getline(&line, bufSize, stdin);
  if (ret <= 0)
    return false;

  // Copy raw input into new buffer; strip first character and newlines
  *buf = malloc(*bufSize);

  int i;
  for (i=1; i<*bufSize && line[i]!='\0' && line[i]!='\n'; i++)
    (*buf)[i-1] = line[i];
  (*buf)[i-1] = '\0';

  // Get command from original line buffer and free it
  *cmd = line[0];
  free(line);

  return true;
}

/** Vector functions */
void initializeVector(Vector *v);
void describeVector(Vector *v);
void updateVectorSize(Vector *v, bool grow);
void freeVector(Vector *v);

void vectorAdd(Vector *v, char *buf);
void vectorRemove(Vector *v, char *buf);


int main(int argc, char *argv[]){
  Vector vector;
  initializeVector(&vector);

  while (true){
    size_t bufSize;
    char *buf;
    char cmd;

    // Parse line into copy buffer
    if (!fetchInput(&bufSize, &buf, &cmd))
      break;

    switch (cmd){
    case '?':
      // Print vector
      describeVector(&vector);
      break;

    case '+':
      // Sorted insert
      vectorAdd(&vector, buf);
      buf = NULL; // Buffer belongs to vector now
      break;

    case '-':
      // Free node
      vectorRemove(&vector, buf);
      break;

    default:
      fprintf(stderr, "Error: Line should start with + or -\n");
    }

    if (buf)
      free(buf);
  }

  // Print and free vector list
  describeVector(&vector);
  freeVector(&vector);
}


void initializeVector(Vector *v){
  v->size = MIN_SIZE;
  v->len = 0;
  v->list = malloc(v->size * sizeof(char *));
}


void updateVectorSize(Vector *v, bool grow){
  if (grow){
    // Adding data, check if buffer needs to grow
    if (v->len+1 >= v->size){
      v->size *= 2;
      v->list = realloc(v->list, v->size*sizeof(char *));
    }

  } else {
    // Deleting data, check if buffer needs to shrink
    if (v->size>MIN_SIZE && 1+(v->size/4)>v->len){
      v->size /= 2;
      v->list = realloc(v->list, v->size*sizeof(char *));
    }
  }
}


void describeVector(Vector *v){
  printf("Vector size: %d\t# items: %d\n", v->size, v->len);
}


void freeVector(Vector *v){
  for (int i=0; i < v->len; i++){
    printf("  ::: %s\n", v->list[i]);
    free(v->list[i]);
  }
  free(v->list);
}


void vectorAdd(Vector *v, char *buf){
  updateVectorSize(v, true);
  // v->list[v->len] = buf;
  int i;

  // Find spot to insert vector
  for (i=0; i < v->len; i++){
    if (strcmp(v->list[i], buf) >= 0)
      break;
  }

  // Insert here
  char *forward = v->list[i];
  v->list[i] = buf;
  v->len += 1;

  // Move rest of list forward
  for (; i < v->len; i++){
    char *temp = v->list[i];
    v->list[i] = forward;
    forward = temp;
  }
}


void vectorRemove(Vector *v, char *buf){
  int i;
  for (i=0; i < v->len; i++){
    if (!strcmp(v->list[i], buf)){
      // Match found, delete string
      free(v->list[i]);
      v->len -= 1;
      break;
    }
  }
  // Move nodes back
  for (; i<= v->len; i++){
    if (i+1 < v->size){
      v->list[i] = v->list[i+1];
    } else {
      // Handle edge case where vector list is full
      v->list[i] = NULL;
    }
  }
  updateVectorSize(v, true);
}
