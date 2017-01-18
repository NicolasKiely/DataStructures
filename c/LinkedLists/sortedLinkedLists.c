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
 * Returns copy of input line, stripped of newline
 * char *line: Raw input
 * int bufSize: Size of buffer to copy
 */
char *copyLine(char *line, int bufSize);

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
 * Iteratively find node before exact match with key
 * struct node *root: Root node
 * char *key: String to compare
 * Note: Returns NULL if no such node is found
 */
struct node *findExactBefore(struct node *root, char *key);

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
    char *line = NULL; // Line input
    ssize_t ret = getline(&line, &bufSize, stdin);
    if (ret <= 0)
      break;
    char *buf = copyLine(line, bufSize); // Node buffer

    if (line[0] == '+'){
      // Create new node
      struct node *n = malloc(sizeof(struct node));
      n->buf = buf;

      // Find node to insert after
      struct node *ins = findBefore(root, buf);

      if (ins){
        // Insert after this node
        n->next = ins->next;
        ins->next = n;

      } else {
        // Insert at start of list
        n->next = root;
        root = n;
      }

    } else if (line[0]=='-'){
      if (root){
        // Remove node
        if (strcmp(root->buf, buf)){
          // Search for node
          struct node *before = findExactBefore(root, buf);
          if (before){
            struct node *n = before->next;
            before->next = n->next;

            free(n->buf);
            free(n);
          }
        } else {
          // Delete first node
          struct node *next = root->next;
          free(root->buf);
          free(root);
          root = next;
        }
      }
      if (buf)
        free(buf);
        
    } else {
      fprintf(stderr, "Error: Line should start with + or -\n");
      if (buf)
        free(buf);
    }

    // Free old buffer
    if (line)
      free(line);
  }

  // Print list
  printNodes(root);

  // Free nodes
  free(root);
}


char *copyLine(char *line, int bufSize){
  if (bufSize < 0)
    return NULL;
  char *buf = malloc(bufSize);

  int i;
  for (i=1; i<bufSize && line[i]!='\0' && line[i]!='\n'; i++){
    buf[i-1] = line[i];
  }
  buf[i-1] = '\0';

  return buf;
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


struct node *findExactBefore(struct node *root, char *key){
  struct node *n = root;
  struct node *before = NULL;
  while (n){
    if (!strcmp(n->buf, key)){
      return before;
    }

    before = n;
    n = n->next;
  }
  return NULL;
}


void printNodes(struct node *n){
  if (!n)
    return;

  printf("::: %s\n", n->buf);
  printNodes(n->next);
}
