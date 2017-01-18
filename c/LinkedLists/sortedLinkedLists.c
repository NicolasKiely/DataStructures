/**
 * Demonstrates sorted linked lists
 * Reads commands from stdin, where each command is in the form:
 *  + <word>: Adds word to linked list
 *  - <word>: removes word from linked list
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/* Linked list node */
struct node {
  char *buf;
  struct node *next;
};


/**
 * Creates and returns new node with copy of text buffer
 * char *buf: c string to copy to node
 * int bufSize: Size of buffer to copy
 * Note: the next pointer in node struct is not set
 */
struct node *createNode(char *buf, int bufSize);

/**
 * Recursively frees node and child nodes
 * struct node *n: Node structure
 */
void freeNode(struct node *n);

/**
 * Recursively find node that compares after key, and return node before that
 * struct node *root: Root node
 * char *key: String to compare
 * Note: Returns NULL if no such node is found
 */
struct node *findBefore(struct node *root, char *key);

/**
 * Recursively print node contents
 * struct node *n: Node to print
 */
void printNodes(struct node *n);


int main(int argc, char *argv[]){
  struct node *root = NULL; // Root node of list

  while (true){
    // Read line
    size_t bufSize = 0; // Buffer size
    char *buf = NULL; // Buffer
    ssize_t ret = getline(&buf, &bufSize, stdin);
    if (ret <= 0)
      break;

    if (buf[0] == '+'){
      // Create new node
      struct node *n = createNode(buf+1, bufSize-1);

      // Find node to insert after
      struct node *ins = findBefore(root, n->buf);

      if (ins){
        // Insert after this node
        n->next = ins->next;
        ins->next = n;

      } else {
        // Insert at start of list
        n->next = root;
        root = n;
      }

    } else {
      fprintf(stderr, "Error: Line should start with + or -\n");
    }

    // Free old buffer
    free(buf);
  }

  // Print list
  printNodes(root);

  // Free nodes
  free(root);
}


struct node *createNode(char *buf, int bufSize){
  if (bufSize < 0)
    return NULL;
  struct node *n = malloc(sizeof(struct node));
  n->buf = malloc(bufSize); // Create new buffer

  // Copy up till newline or null byte
  int i;
  for (i=0; i<bufSize-1 && buf[i]!='\0' && buf[i]!='\n'; i++){
    n->buf[i] = buf[i];
  }
  n->buf[i] = '\0';

  return n;
}


void freeNode(struct node *n){
  if (!n)
    return;

  freeNode(n->next);

  if (n->buf)
    free(n->buf);

  free(n);
}

struct node *findBefore(struct node *root, char *key){
  if (!root)
    return NULL;

  if (strcmp(root->buf, key) > 0){
    // Key comes before this node, done searching
    return NULL;

  } else {
    // Key comes after this node, keep searching
    struct node *n = findBefore(root->next, key);

    if (n == NULL){
      // Key does not come after next node, return this node
      return root;

    } else {
      // Recursive return
      return n;
    }
  }
}


void printNodes(struct node *n){
  if (!n)
    return;

  printf("::: %s\n", n->buf);
  printNodes(n->next);
}
