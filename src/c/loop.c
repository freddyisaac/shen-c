#include "loop.h"

#include "defs.h"

LoopFrameStack* loop_frame_stack;
LoopFramePair* empty_loop_frame_pair;

EXTERN Vector* get_loop_frame_arguments (LoopFrame* frame);
EXTERN void set_loop_frame_arguments (LoopFrame* frame, Vector* arguments);
EXTERN Vector* get_loop_frame_parameters (LoopFrame* frame);
EXTERN void set_loop_frame_parameters (LoopFrame* frame, Vector* parameters);
EXTERN sigjmp_buf* get_loop_frame_jump_buffer (LoopFrame* frame);
EXTERN void set_loop_frame_jump_buffer (LoopFrame* frame, sigjmp_buf* jump_buffer);
EXTERN LoopFrame* create_loop_frame (void);

EXTERN LoopFrame* get_loop_frame_pair_car (LoopFramePair* frame_pair);
EXTERN void set_loop_frame_pair_car (LoopFramePair* frame_pair, LoopFrame* frame);
EXTERN LoopFramePair* get_loop_frame_pair_cdr (LoopFramePair* frame_pair);
EXTERN void set_loop_frame_pair_cdr (LoopFramePair* frame_pair,
                                     LoopFramePair* cdr_frame_pair);
EXTERN LoopFramePair* create_loop_frame_pair (LoopFrame* car_frame,
                                              LoopFramePair* cdr_frame_pair);
EXTERN void initialize_empty_loop_frame_pair (void);
EXTERN LoopFramePair* get_empty_loop_frame_pair (void);
EXTERN bool is_empty_loop_frame_pair (LoopFramePair* frame_pair);

EXTERN LoopFrameStack* get_loop_frame_stack (void);
EXTERN void set_loop_frame_stack (LoopFrameStack* frame_stack);
EXTERN LoopFramePair* get_loop_frame_stack_top (LoopFrameStack* frame_stack);
EXTERN void set_loop_frame_stack_top (LoopFrameStack* frame_stack,
                                      LoopFramePair* frame_pair);
EXTERN long get_loop_frame_stack_size (LoopFrameStack* frame_stack);
EXTERN void set_loop_frame_stack_size (LoopFrameStack* frame_stack,
                                       long frame_stack_size);
EXTERN void initialize_loop_frame_stack (void);

void push_loop_frame_stack_with_frame_pair (LoopFramePair* frame_pair)
{
  LoopFramePair* top_frame_pair =
    get_loop_frame_stack_top(get_loop_frame_stack());
  long new_frame_stack_size =
    get_loop_frame_stack_size(get_loop_frame_stack()) + 1;

  set_loop_frame_pair_cdr(frame_pair, top_frame_pair);
  set_loop_frame_stack_top(get_loop_frame_stack(), frame_pair);
  set_loop_frame_stack_size(get_loop_frame_stack(), new_frame_stack_size);
}

LoopFrame* pop_loop_frame_stack (void)
{
  LoopFramePair* top_frame_pair =
    get_loop_frame_stack_top(get_loop_frame_stack());

  if (is_empty_loop_frame_pair(top_frame_pair))
    return NULL;

  LoopFrame* car_frame = get_loop_frame_pair_car(top_frame_pair);
  LoopFramePair* cdr_frame_pair = get_loop_frame_pair_cdr(top_frame_pair);
  long new_frame_stack_size =
    get_loop_frame_stack_size(get_loop_frame_stack()) - 1;

  set_loop_frame_stack_top(get_loop_frame_stack(), cdr_frame_pair);
  set_loop_frame_stack_size(get_loop_frame_stack(), new_frame_stack_size);

  return car_frame;
}

LoopFrame* peek_loop_frame_stack (void)
{
  LoopFramePair* top_frame_pair =
    get_loop_frame_stack_top(get_loop_frame_stack());

  if (is_empty_loop_frame_pair(top_frame_pair))
    return NULL;

  return get_loop_frame_pair_car(top_frame_pair);
}
