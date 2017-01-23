/**
 * Demonstrates simple trees
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


/** Dynamic tree node */
typedef struct node {
  int height; // Node height
  char *buf;  // Text
  struct node *left;  // Left child
  struct node *right; // Right child
} Node;

typedef struct {
  Node *root;
} Tree;


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


// Tree functions
void TreeAdd(Tree *t, char *buf); // Add buf to tree
void TreeDel(Tree *t, char *buf); // Delete buf from tree
void TreePrint(Tree *t); // Print tree contents

// Node functions
Node *newNode(char *buf); // Create new node
void freeNode(Node *n); // Recursive free node
void nodeAdd(Node *n, char *buf); // Recursive add node


int main(int argc, char *argv[]){
  Tree tree;
  tree.root = NULL;

  while (true){
    size_t bufSize;
    char *buf;
    char cmd;

    // Parse line into copy buffer
    if (!fetchInput(&bufSize, &buf, &cmd))
      break;

    switch (cmd){
    case '+':
      // Add string
      TreeAdd(&tree, buf);
      buf = NULL;
      break;

    case '-':
      // Remove string
      TreeDel(&tree, buf);
      break;

    case '?':
      // Print tree
      TreePrint(&tree);
      break;

    default:
      fprintf(stderr, "Error: Line should start with + or -\n");
    }

    if (buf)
      free(buf);
  }

  freeNode(tree.root);
}


void freeNode(Node *n){
  if (!n)
    return;

  freeNode(n->left);
  freeNode(n->right);
  if (n->buf)
    free(n->buf);
  free(n);
}


void TreeAdd(Tree *t, char *buf){
  if (t->root){
    // Tree not empty, recursively add
    nodeAdd(t->root, buf);

  } else {
    // Tree empty, create new root node
    t->root = newNode(buf);
    return;
  }
}


void TreeDel(Tree *t, char *buf){
}


void TreePrint(Tree *t){
}


Node *newNode(char *buf){
  Node *n = malloc(sizeof(Node));
  n->buf = buf;
  n->height = 0;
  n->left = NULL;
  n->right = NULL;

  return n;
}


void nodeAdd(Node *n, char *buf){
  if (!n->left){
    // Left node empty, add here
    n->left = newNode(buf);
    n->height = n->height ? n->height : 1;
    return;
  }
  
  if (!n->right){
    // Right node empty, add here
    n->right = newNode(buf);
    n->height = n->height ? n->height : 1;
    return;
  }

  Node *child;
  int lheight = n->left->height;
  int rheight = n->right->height;
  if (lheight < rheight){
    // Left side shorter, add left
    child = n->left;

  } else if (lheight == rheight){
    // Same size, add left. Tree size will grow
    child = n->left;
    n->height++;

  } else {
    // Right side shorter
    child = n->right;
  }

  nodeAdd(child, buf);
}
