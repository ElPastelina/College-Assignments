#include<stdio.h>
#include<stdlib.h>

struct StackNode{
  int data;
  struct StackNode *next;
};

struct StackNode* newNode(int data){
  struct StackNode* stackNode = (struct StackNode *) malloc (sizeof(struct StackNode));
  stackNode->data = data;
  stackNode->next = NULL;
  return stackNode;
}

int isEmpty(struct StackNode* root){
  return !root;
}

void push(struct StackNode** root, int data){
  struct StackNode* stackNode = newNode(data);
  stackNode->next = *root;
  *root = stackNode;
  printf("%d pushed to the stack\n", data);
}

int pop(struct StackNode** root){
  if(*root == NULL){
    printf("The Stack is empty");
  }
  struct StackNode* temp = *root;
  *root = (*root)->next;
  int popped = temp->data;
  free(temp);

  return popped;
}

int peek(struct StackNode* root) 
{ 
  return root->data; 
}

int main(){
  struct StackNode* root;

  push(&root, 10);
  push(&root, 20);
  push(&root, 30);

  printf("%d popped from the stack\n", pop(&root));

  printf("Top element is %d\n", root->data);
}