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

#define BUFFER_SIZE 100

/* Linked list node */
struct node {
  char *buf;
  struct node *next;
};


int main(int argc, char *argv[]){
  char *buf = NULL; // Buffer
  size_t bufSize = BUFFER_SIZE;
  struct node *root = NULL;

  while (true){
    // Read line
    ssize_t ret = getline(&buf, &bufSize, stdin);
    if (ret <= 0)
      break;

    if (buf[0] == '+'){
      // Create new node
      struct node *newNode = malloc(sizeof(struct node));
      newNode->buf = buf;
      newNode->next = root;
      root = newNode;

    } else if (buf[0] == '-'){
      // Search for node and delete it
      struct node *prev = NULL;
      struct node *n = root;
      while (n){
        if (strcmp(buf+1, n->buf+1) == 0)
          break;
        prev = n;
        n = n->next;
      }

      if (n){
        // Free the node
        if (n == root){
          root = root->next;
        } else {
          prev->next = n->next;
        }
        free(n->buf);
        free(n);
      }
      free(buf);

    } else {
      fprintf(stderr, "Error: Line should start with + or -\n");
      free(buf);
    }
    buf = NULL;
  }


  while (root){
    struct node *next = root->next;

    // Print node
    printf("::: %s", root->buf+1);

    // Free node
    free(root->buf);
    free(root);

    root = next;
  }

  free(buf);
}
