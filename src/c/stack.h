#ifndef SHEN_C_STACK_H
#define SHEN_C_STACK_H

#include "defs.h"

#include "kl.h"

void push_stack (Stack* stack, KLObject* object);
KLObject* pop_stack (Stack* stack);
KLObject* peek_stack (Stack* stack);

INLINE KLObject* get_stack_top (Stack* stack)
{
  return stack->top;
}

INLINE void set_stack_top (Stack* stack, KLObject* top_object)
{
  stack->top = top_object;
}

INLINE long get_stack_size (Stack* stack)
{
  return stack->size;
}

INLINE void set_stack_size (Stack* stack, long size)
{
  stack->size = size;
}

INLINE Stack* create_stack (void)
{
  Stack* stack = malloc(sizeof(Stack));

  set_stack_top(stack, EL);
  set_stack_size(stack, 0);

  return stack;
}

#endif
