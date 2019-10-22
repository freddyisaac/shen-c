#ifndef SHEN_C_LOOP_H
#define SHEN_C_LOOP_H

#include "defs.h"

#include <stdbool.h>
#include <setjmp.h>

#include "kl.h"
#include "vector.h"

extern LoopFrameStack* loop_frame_stack;
extern LoopFramePair* empty_loop_frame_pair;

void push_loop_frame_stack_with_frame_pair (LoopFramePair* frame_pair);
LoopFrame* pop_loop_frame_stack (void);
LoopFrame* peek_loop_frame_stack (void);

INLINE Vector* get_loop_frame_arguments (LoopFrame* frame)
{
  return frame->arguments;
}

INLINE void set_loop_frame_arguments (LoopFrame* frame, Vector* arguments)
{
  frame->arguments = arguments;
}

INLINE Vector* get_loop_frame_parameters (LoopFrame* frame)
{
  return frame->parameters;
}

INLINE void set_loop_frame_parameters (LoopFrame* frame, Vector* parameters)
{
  frame->parameters = parameters;
}

INLINE sigjmp_buf* get_loop_frame_jump_buffer (LoopFrame* frame)
{
  return frame->jump_buffer;
}

INLINE void set_loop_frame_jump_buffer (LoopFrame* frame, sigjmp_buf* jump_buffer)
{
  frame->jump_buffer = jump_buffer;
}

INLINE LoopFrame* create_loop_frame (void)
{
  LoopFrame* frame = malloc(sizeof(LoopFrame));

  set_loop_frame_arguments(frame, NULL);
  set_loop_frame_parameters(frame, NULL);
  set_loop_frame_jump_buffer(frame, NULL);

  return frame;
}

INLINE LoopFrame* get_loop_frame_pair_car (LoopFramePair* frame_pair)
{
  return frame_pair->car;
}

INLINE void set_loop_frame_pair_car (LoopFramePair* frame_pair, LoopFrame* frame)
{
  frame_pair->car = frame;
}

INLINE LoopFramePair* get_loop_frame_pair_cdr (LoopFramePair* frame_pair)
{
  return frame_pair->cdr;
}

INLINE void set_loop_frame_pair_cdr (LoopFramePair* frame_pair,
                                     LoopFramePair* cdr_frame_pair)
{
  frame_pair->cdr = cdr_frame_pair;
}

INLINE LoopFramePair* create_loop_frame_pair (LoopFrame* car_frame,
                                              LoopFramePair* cdr_frame_pair)
{
  LoopFramePair* frame_pair = malloc(sizeof(LoopFramePair));

  set_loop_frame_pair_car(frame_pair, car_frame);
  set_loop_frame_pair_cdr(frame_pair, cdr_frame_pair);

  return frame_pair;
}

INLINE void initialize_empty_loop_frame_pair (void)
{
  empty_loop_frame_pair = create_loop_frame_pair(NULL, NULL);
}

INLINE LoopFramePair* get_empty_loop_frame_pair (void)
{
  return empty_loop_frame_pair;
}

INLINE bool is_empty_loop_frame_pair (LoopFramePair* frame_pair)
{
  return frame_pair == get_empty_loop_frame_pair();
}

INLINE LoopFrameStack* get_loop_frame_stack (void)
{
  return loop_frame_stack;
}

INLINE void set_loop_frame_stack (LoopFrameStack* frame_stack)
{
  loop_frame_stack = frame_stack;
}

INLINE LoopFramePair* get_loop_frame_stack_top (LoopFrameStack* frame_stack)
{
  return frame_stack->top;
}

INLINE void set_loop_frame_stack_top (LoopFrameStack* frame_stack,
                                      LoopFramePair* frame_pair)
{
  frame_stack->top = frame_pair;
}

INLINE long get_loop_frame_stack_size (LoopFrameStack* frame_stack)
{
  return frame_stack->size;
}

INLINE void set_loop_frame_stack_size (LoopFrameStack* frame_stack,
                                       long frame_stack_size)
{
  frame_stack->size = frame_stack_size;
}

INLINE void initialize_loop_frame_stack (void)
{
  LoopFrameStack* frame_stack = malloc(sizeof(LoopFrameStack));

  set_loop_frame_stack_top(frame_stack, get_empty_loop_frame_pair());
  set_loop_frame_stack_size(frame_stack, 0);
  set_loop_frame_stack(frame_stack);
}

#endif
