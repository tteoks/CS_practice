#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
  int data;
  struct _Node *left;
  struct _Node *right;
} Node;

Node *newNode(int data) {
  Node *tmpNode = malloc(sizeof(Node));

  tmpNode->data = data;
  tmpNode->left = NULL;
  tmpNode->right = NULL;

  return tmpNode;
}

Node *insertNode(Node *node, int data) {
  if (node == NULL) 
    return newNode(data);

  if (data < node->data) 
    node->left = insertNode(node->left, data);
  else if (data > node->data) 
    node->right = insertNode(node->right, data);

  return node;
}

Node *searchNode(Node *node, int key) {
  if (node->left == NULL && node->right == NULL)
    return NULL;

if (key < node->data) {
    node = searchNode(node->left, key);
  } else if (key > node->data) {
    node = searchNode(node->right, key);
  } else {
    return node;
  }

  return node;
}

Node *minValNode(Node *node) {
  Node *cur = node;

  while (cur && cur->left != NULL)
    cur = cur->left;

  return cur;
}

Node *deleteNode(Node *node, int data) {
  // Delete Leaf node
  //   * Just delete
  //
  // Delete Node with one child
  //   * Delete, replace node to child
  //
  // Delete Node with both childs
  //   * Delete, decide proper node, replace proper node
  //   * decide proper node
  //     1. Largest node from left child subtree
  //     2. Smallest node from right child subtre
  //
  if (node == NULL)
    return node;

  if (data < node->data) {
    node->left = deleteNode(node->left, data);
  } else if (data > node->data) {
    node->right = deleteNode(node->right, data);
  } else {
    Node *tmp;
    // For only one child or no child
    if (node->left == NULL) {
      tmp = node->right;
      free(node);
      return tmp;
    } else if (node->right == NULL) {
      tmp = node->left;
      free(node);
      return tmp;
    } else {
      // For two child
      tmp = minValNode(node);
      node->data = tmp->data;
      node->right = deleteNode(node->right, tmp->data);
    }
  }
    return node;
}

int tree_height(Node *node) {
  if (node == NULL)
    return 0;

  else {
    int leftHeight = tree_height(node->left);
    int rightHeight = tree_height(node->right);

    if (leftHeight > rightHeight) 
      return (leftHeight + 1);
    else
      return (rightHeight + 1);
  }
}

void printLevel(Node *root, int level) {
  if (root == NULL)
    return ;
  if (level == 1)
    printf("%d ", root->data);
  else
    printLevel(root->left, level - 1);
    printLevel(root->right, level - 1);

}

void printLevelOrder(Node *node) {
  int h = tree_height(node);
  int i;
  for (i=1; i<=h; i++) {
    printLevel(node, i);
    printf("\n");
  }
  printf("\n");

}

void inorderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }
  inorderTraversal(root->left);
  printf("%d ", root->data);
  inorderTraversal(root->right);
}

void postorderTraversal(Node *root) {
  if (root == NULL)
    return;

  postorderTraversal(root->right);
  printf("%d ", root->data);
  postorderTraversal(root->left);

}
  



int main(int argc, char **argv)
{
  printf("Hello world\n");

  Node *tmp;
  Node *testNode = newNode(50);

  insertNode(testNode, 30);
  insertNode(testNode, 20);
  insertNode(testNode, 40);
  insertNode(testNode, 70);
  insertNode(testNode, 60);
  insertNode(testNode, 80);

  printLevelOrder(testNode);

  printf("postorderTraversal\n");
  postorderTraversal(testNode);
  printf("\n\n");

  printf("inorderTraversal\n");
  inorderTraversal(testNode);
  printf("\n\n");
  
  deleteNode(testNode, 60);
  printf("Delete Heap: %d\n", 60);
  printLevelOrder(testNode);
   
  deleteNode(testNode, 70);
  printf("Delete Heap: %d\n", 70);
  printLevelOrder(testNode);
 
  deleteNode(testNode, 50);
  printf("Delete Heap: %d\n", 50);
  printLevelOrder(testNode);

  free(testNode);

  return 0;
}
