#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE   20

typedef struct _Node {
  int data;
  int key;
  struct _Node *next;
} Node;

Node *HashTable[MAXSIZE];


int hashFunction(int key) {
  if (key >= 0)
    return key % MAXSIZE;
  else
    return (key % MAXSIZE)* -1;

}
Node *searchHash(int key) {
  Node *cur;
  int addr = hashFunction(key);

  cur = HashTable[addr];
  while (cur != NULL) {
    if (cur->key == key)
      return cur;
    else {
      cur = cur->next;
    }
  }

  return NULL;
} 

void insertHash(int key, int data) {
  int addr = hashFunction(key);
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->key = key;
  new_node->data = data;
  new_node->next = NULL;

  if (HashTable[addr] == NULL) {
    HashTable[addr] = new_node;
  } else {
    Node *cur = HashTable[addr];
    while (cur->next != NULL) {
      cur = cur->next;
    }
    cur->next = new_node;
  }
}


Node *deleteHash(Node *item, int key) {
  int addr= hashFunction(key);
  Node *cur = HashTable[addr];
  Node *before = NULL;
  
  if (cur != NULL && cur->next == NULL) {
    Node *tmp = HashTable[addr];
    HashTable[addr] = NULL;
    return tmp;
  }

  while (cur != NULL) {
    if (cur->key == key) {
      Node *tmp = cur;
      
      if (before != NULL)
        before->next = cur->next;
      else
        HashTable[addr] = NULL;

      return tmp;
    }
    else {
      before = cur;
      cur = cur->next;
    }
  }

  return NULL;
}

void displayHash() {
  int i = 0;
  Node *cur;
  printf("#### Display Hash Table\n");
  for (i=0; i<MAXSIZE; i++) {
    if (HashTable[i] != NULL) {
      cur = HashTable[i];
      printf("  (%d, %d)", cur->key, cur->data);
      while (cur->next != NULL) {
        cur = cur->next;
        printf("->(%d, %d)", cur->key, cur->data);
      }
    }
    else 
      printf("  ~~ ");
  }
  printf("\n");
}



int main(int argc, char **argv)
{
  Node *item;
  printf("Hello World\n");

  insertHash(1, 20);
  insertHash(2, 70);
  insertHash(42, 80);
  insertHash(4, 25);
  insertHash(12, 44);
  insertHash(-5, 25);
  insertHash(-20, 25);
  insertHash(14, 32);
  insertHash(17, 11);
  insertHash(24, 78);
  insertHash(37, 97);

  displayHash();

  printf("Search Hash data 37\n");
  item = searchHash(37);

  if(item != NULL) {
    printf("Element found: %d\n", item->data);
  } else {
    printf("Element not found\n");
  }
  printf("\n");

  printf("Delete Hash data 37\n\n");
  deleteHash(item, 37);
  displayHash();

  printf("Search Hash data 37\n");
  item = searchHash(37);
  if(item != NULL) {
    printf("Element found: %d\n", item->data);
  } else {
    printf("Element not found\n");
  }
  printf("\n");

  return 0;
}
