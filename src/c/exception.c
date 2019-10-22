#include "exception.h"

#include "defs.h"


Stack* trapped_kl_exception_stack;

EXTERN char* get_exception_error_message (Exception* exception);
EXTERN void set_exception_error_message (Exception* exception,
                                         char* error_message);
EXTERN sigjmp_buf* get_exception_jump_buffer (Exception* exception);
EXTERN void set_exception_jump_buffer (Exception* exception,
                                       sigjmp_buf* jump_buffer);
EXTERN Exception* create_exception (void);

EXTERN Exception* get_exception (KLObject* exception_object);
EXTERN void set_exception (KLObject* exception_object, Exception* exception);
EXTERN KLObject* create_kl_exception (void);
EXTERN sigjmp_buf* get_kl_exception_jump_buffer (KLObject* exception_object);
EXTERN void set_kl_exception_jump_buffer (KLObject* exception_object,
                                          sigjmp_buf* jump_buffer);
EXTERN Stack* get_trapped_kl_exception_stack (void);
EXTERN void set_trapped_kl_exception_stack (Stack* stack);
EXTERN void initialize_trapped_kl_exception_stack (void);
EXTERN bool is_kl_exception (KLObject* object);
EXTERN bool is_kl_exception_equal (KLObject* left_object, KLObject* right_object);

void throw_kl_exception (char* error_message)
{
  KLObject* exception_object = peek_stack(get_trapped_kl_exception_stack());

  if (is_empty_kl_list(exception_object)) {
    fprintf(stderr, "%s\n", error_message);
    exit(EXIT_FAILURE);
  }

  Exception* exception = get_exception(exception_object);

  set_exception_error_message(exception, error_message);

  sigjmp_buf* jump_buffer = get_exception_jump_buffer(exception);

  siglongjmp(*jump_buffer, 1);
}

char* kl_exception_to_string (KLObject* exception_object)
{
  Exception* exception = get_exception(exception_object);
  char* error_message = get_exception_error_message(exception);
  int object_string_length = snprintf(NULL, 0,
                                      "#<Exception {0x%016p\" PRIxPTR \"} %s>",
                                      (uintptr_t)exception_object,
                                      error_message);
  char* object_string = malloc((size_t)object_string_length + 1);
  
  sprintf(object_string, "#<Exception {0x%016p\" PRIxPTR \"} %s>",
          (uintptr_t)exception_object,
          error_message);

  return object_string;
}
