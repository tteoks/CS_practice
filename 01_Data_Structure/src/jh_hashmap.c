#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE   20

typedef struct _Item {
  int data;
  int key;
} Item;

Item *HashTable[MAXSIZE];
Item *dummyItem;


int hashFunction(int key) {
  if (key >= 0)
    return key % MAXSIZE;
  else
    return (key * -1) % MAXSIZE;
}
Item *searchHash(int key) {
  Item *res;
  int addr = hashFunction(key);

  while (HashTable[addr] != NULL) {
    if (HashTable[addr]->key == key)
      return HashTable[addr];
    else {
      addr++;
      addr %= MAXSIZE;
    }
  }

  return NULL;
} 

void insertHash(int key, int data) {
  Item *tmp = (Item *)malloc(sizeof(Item));
  int addr = hashFunction(key);
  tmp->key = key;
  tmp->data = data;

  while (HashTable[addr] != NULL) {
    addr++;
    addr %= MAXSIZE;
  }

  HashTable[addr] = tmp;
}


Item *deleteHash(Item *item) {
  int key = item->key;
  int addr= hashFunction(key);

  while (HashTable[addr] != NULL) {
    if (HashTable[addr]->key == key) {
      Item *tmp = HashTable[addr];
      HashTable[addr] = dummyItem;
      return tmp;
    }
    else {
      addr++;
      addr %= MAXSIZE;
    }
  }

  return NULL;
}

void displayHash() {
  int i = 0;
  printf("#### Display Hash Table\n");
  for (i=0; i<MAXSIZE; i++) {
    if (HashTable[i] != NULL)
      printf("  (%d, %d)", HashTable[i]->key, HashTable[i]->data);
    else 
      printf("  ~~ ");
  }
  printf("\n");
}



int main(int argc, char **argv)
{
  Item *item;
  printf("Hello World\n");

  dummyItem = (Item*) malloc(sizeof(Item));
  dummyItem->data = -1;  
  dummyItem->key = -1; 

  insertHash(1, 20);
  insertHash(2, 70);
  insertHash(42, 80);
  insertHash(4, 25);
  insertHash(12, 44);
  insertHash(-5, 25);
  insertHash(-20, 25);
  insertHash(14, 32);
  insertHash(17, 11);
  insertHash(13, 78);
  insertHash(37, 97);

  displayHash();

  printf("Search Hash key 37\n");
  item = searchHash(37);

  if(item != NULL) {
    printf("Element found: %d\n", item->data);
  } else {
    printf("Element not found\n");
  }
  printf("\n");

  printf("Delete Hash key 37\n\n");
  deleteHash(item);
  displayHash();

  printf("Search Hash key 37\n");
  item = searchHash(37);

  if(item != NULL) {
    printf("Element found: %d\n", item->data);
  } else {
    printf("Element not found\n");
  }
  printf("\n");

  return 0;
}
