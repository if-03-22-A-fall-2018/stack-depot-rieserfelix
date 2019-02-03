#include "depot.h"
#include "memcheck.h"
typedef struct Product product;

struct DepotImplementation
{
  Stack stacks;
};

Depot create_depot()
{
  Depot new_depot = (Depot)smalloc(sizeof(Depot));

  new_depot->stacks = 0;
  return new_depot;
}

void push_depot(Depot d, product* p)
{
  if(d->stacks == 0)
  {
    d->stacks =create_stack();
    add_stack(d->stacks, p);
    return;
  }

  Stack last_stack = (Stack)peek_stack(d->stacks);

  if(get_count(last_stack) == 3)
  {
    add_stack(d->stacks, p);
  }

  else
  {
    push_stack(last_stack,p);
  }
}

void delete_depot (Depot depot)
{
  while(get_count(depot) > 0)
  {
    Stack s = (Stack)pop_stack(depot->stacks);
    delete_stack(s);
  }

  delete_stack(depot->stacks);
  sfree(depot);
}


int get_count (Depot depot)
{
  if(depot->stacks == 0)
  {
    return 0;
  }
  return get_count(depot->stacks);
}

Product * pop_depot (Depot depot)
{
  Stack last_stack = (Stack)peek_stack(depot->stacks);
  Product* to_return = (Product*)pop_stack(last_stack);

  if(get_count(last_stack) == 0)
  {
    Stack to_delete_stack = (Stack)pop_stack(depot->stacks);
    delete_stack(to_delete_stack);

    if(get_count(depot) == 0)
    {
      sfree(depot->stacks);
        depot->stacks = 0;
    }
  }
  return to_return;
}

void add_stack(Stack depot_stack, Product* p)
{
  Stack product_stack = create_stack();
  push_stack(product_stack, p);
  push_stack(depot_stack, product_stack);
}
