#include "stack.h"
#include "memcheck.h"

struct NodeImplementation
{
  Node next;
  void* data;
};


struct StackImplementation
{
  Node head;
  int count;
};

Stack create_stack()
{
  Stack new_stack = (Stack)smalloc(sizeof(Stack));
  new_stack->head = 0;
  new_stack->count = 0;
  return new_stack;
}

void delete_stack(Stack stack)
{
  if(stack == 0)
  {
    return;
  }

  Node crnt_node = stack->head;

  while(crnt_node != 0)
  {
    Node node_to_delete = crnt_node;
    crnt_node = crnt_node->next;
    sfree(node_to_delete);
  }
  sfree(stack);
}

void push_stack(Stack stack, void *data)
{
  Node new_node = (Node)smalloc(sizeof(Node));
  stack->count++;
  new_node->data = data;
  new_node->next = stack->head;
  stack->head = new_node;
}

int get_count(Stack stack)
{

  return stack->count;
}

void* pop_stack(Stack stack)
{
  stack->count--;
  Node node_to_delete = stack->head;
  void* p = node_to_delete->data;
  stack->head = stack->head->next;
  sfree(node_to_delete);
  return p;
}

void* peek_stack(Stack stack){
  return stack->head->data;
}
