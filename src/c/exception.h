#ifndef SHEN_C_EXCEPTION_H
#define SHEN_C_EXCEPTION_H

#include "defs.h"

#include <stdio.h>
//#include <inttypes.h>
#include <setjmp.h>

#include "kl.h"
#include "stack.h"

extern Stack* trapped_kl_exception_stack;

void throw_kl_exception (char* error_message);
char* kl_exception_to_string (KLObject* exception_object);

INLINE char* get_exception_error_message (Exception* exception)
{
  return exception->error_message;
}

INLINE void set_exception_error_message (Exception* exception,
                                         char* error_message)
{
  exception->error_message = error_message;
}

INLINE sigjmp_buf* get_exception_jump_buffer (Exception* exception)
{
  return exception->jump_buffer;
}

INLINE void set_exception_jump_buffer (Exception* exception, sigjmp_buf* jump_buffer)
{
  exception->jump_buffer = jump_buffer;
}

INLINE Exception* create_exception (void)
{
  Exception* exception = malloc(sizeof(Exception));

  return exception;
}

INLINE Exception* get_exception (KLObject* exception_object)
{
  return exception_object->value.exception;
}

INLINE void set_exception (KLObject* exception_object, Exception* exception)
{
  exception_object->value.exception = exception;
}

INLINE KLObject* create_kl_exception (void)
{
  KLObject* exception_object = create_kl_object(KL_TYPE_EXCEPTION);
  Exception* exception = create_exception();

  set_exception(exception_object, exception);

  return exception_object;
}

INLINE sigjmp_buf* get_kl_exception_jump_buffer (KLObject* exception_object)
{
  return get_exception_jump_buffer(get_exception(exception_object));
}

INLINE void set_kl_exception_jump_buffer (KLObject* exception_object,
                                          sigjmp_buf* jump_buffer)
{
  set_exception_jump_buffer(get_exception(exception_object),
                            jump_buffer);
}

INLINE Stack* get_trapped_kl_exception_stack (void)
{
  return trapped_kl_exception_stack;
}

INLINE void set_trapped_kl_exception_stack (Stack* stack)
{
  trapped_kl_exception_stack = stack;
}

INLINE void initialize_trapped_kl_exception_stack (void)
{
  set_trapped_kl_exception_stack(create_stack());
}

INLINE bool is_kl_exception (KLObject* object)
{
  return get_kl_object_type(object) == KL_TYPE_EXCEPTION;
}

INLINE bool is_kl_exception_equal (KLObject* left_object, KLObject* right_object)
{
  return left_object == right_object;
}

#endif
