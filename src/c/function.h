#ifndef SHEN_C_FUNCTION_H
#define SHEN_C_FUNCTION_H

#include "defs.h"

#include <stdint.h>
#include <stdbool.h>

#include "environment.h"
#include "exception.h"
#include "kl.h"
#include "symbol.h"
#include "vector.h"

INLINE long get_primitive_function_parameter_size
(PrimitiveFunction* primitive_function)
{
  return primitive_function->parameter_size;
}

INLINE void set_primitive_function_parameter_size
(PrimitiveFunction* primitive_function, long parameter_size)
{
  primitive_function->parameter_size = parameter_size;
}

INLINE NativeFunction* get_primitive_function_native_function
(PrimitiveFunction* primitive_function)
{
  return primitive_function->native_function;
}

INLINE void set_primitive_function_native_function
(PrimitiveFunction* primitive_function, NativeFunction* native_function)
{
  primitive_function->native_function = native_function;
}

INLINE PrimitiveFunction* create_primitive_function (void)
{
  PrimitiveFunction* primitive_function = malloc(sizeof(PrimitiveFunction));

  set_primitive_function_parameter_size(primitive_function, 0);
  set_primitive_function_native_function(primitive_function, NULL);

  return primitive_function;
}

INLINE Vector* get_user_function_parameters (UserFunction* user_function)
{
  return user_function->parameters;
}

INLINE void set_user_function_parameters (UserFunction* user_function,
                                          Vector* parameters)
{
  user_function->parameters = parameters;
}

INLINE KLObject* get_user_function_body (UserFunction* user_function)
{
  return user_function->body;
}

INLINE void set_user_function_body (UserFunction* user_function,
                                    KLObject* body_object)
{
  user_function->body = body_object;
}

INLINE UserFunction* create_user_function (void)
{
  UserFunction* user_function = malloc(sizeof(UserFunction));

  set_user_function_parameters(user_function, NULL);
  set_user_function_body(user_function, NULL);

  return user_function;
}

INLINE KLObject* get_closure_parameter (Closure* closure)
{
  return closure->parameter;
}

INLINE void set_closure_parameter (Closure* closure, KLObject* parameter)
{
  closure->parameter = parameter;
}

INLINE KLObject* get_closure_body (Closure* closure)
{
  return closure->body;
}

INLINE void set_closure_body (Closure* closure, KLObject* body_object)
{
  closure->body = body_object;
}

INLINE Environment* get_closure_parent_function_environment (Closure* closure)
{
  return closure->parent_function_environment;
}

INLINE void set_closure_parent_function_environment
(Closure* closure, Environment* parent_function_environment)
{
  closure->parent_function_environment = parent_function_environment;
}

INLINE Environment* get_closure_parent_variable_environment (Closure* closure)
{
  return closure->parent_variable_environment;
}

INLINE void set_closure_parent_variable_environment
(Closure* closure, Environment* parent_variable_environment)
{
  closure->parent_variable_environment = parent_variable_environment;
}

INLINE Closure* create_closure (void)
{
  Closure* closure = malloc(sizeof(Closure));

  set_closure_parameter(closure, NULL);
  set_closure_body(closure, NULL);
  set_closure_parent_function_environment(closure, NULL);
  set_closure_parent_variable_environment(closure, NULL);

  return closure;
}

INLINE KLFunctionType get_function_function_type (Function* function)
{
  return function->function_type;
}

INLINE void set_function_function_type (Function* function,
                                        KLFunctionType function_type)
{
  function->function_type = function_type;
}

INLINE PrimitiveFunction* get_function_primitive_function (Function* function)
{
  return function->value.primitive_function;
}

INLINE void set_function_primitive_function (Function* function,
                                             PrimitiveFunction* primitive_function)
{
  function->value.primitive_function = primitive_function;
}

INLINE UserFunction* get_function_user_function (Function* function)
{
  return function->value.user_function;
}

INLINE void set_function_user_function (Function* function,
                                        UserFunction* user_function)
{
  function->value.user_function = user_function;
}

INLINE Closure* get_function_closure (Function* function)
{
  return function->value.closure;
}

INLINE void set_function_closure (Function* function, Closure* closure)
{
  function->value.closure = closure;
}

INLINE bool is_primitive_function (Function* function)
{
  return (get_function_function_type(function) ==
          KL_FUNCTION_TYPE_PRIMITIVE_FUNCTION);
}

INLINE bool is_user_function (Function* function)
{
  return get_function_function_type(function) == KL_FUNCTION_TYPE_USER_FUNCTION;
}

INLINE bool is_closure (Function* function)
{
  return get_function_function_type(function) == KL_FUNCTION_TYPE_CLOSURE;
}

INLINE Function* create_function (KLFunctionType function_type)
{
  Function* function = malloc(sizeof(Function));

  set_function_function_type(function, function_type);

  if (is_primitive_function(function))
    set_function_primitive_function(function, create_primitive_function());
  else if (is_user_function(function))
    set_function_user_function(function, create_user_function());
  else if (is_closure(function))
    set_function_closure(function, create_closure());
  else
    throw_kl_exception("Unknown type of function");

  return function;
}

INLINE Function* get_function (KLObject* function_object)
{
  return function_object->value.function;
}

INLINE void set_function (KLObject* function_object, Function* function)
{
  function_object->value.function = function;
}

INLINE bool is_kl_function (KLObject* object)
{
  return get_kl_object_type(object) == KL_TYPE_FUNCTION;
}

INLINE bool is_primitive_kl_function (KLObject* object)
{
  return is_kl_function(object) && is_primitive_function(get_function(object));
}

INLINE bool is_user_kl_function (KLObject* object)
{
  return is_kl_function(object) && is_user_function(get_function(object));
}

INLINE bool is_closure_kl_function (KLObject* object)
{
  return is_kl_function(object) && is_closure(get_function(object));
}

INLINE KLFunctionType get_kl_function_type (KLObject* function_object)
{
  return get_function_function_type(get_function(function_object));
}

INLINE void set_kl_function_type (KLObject* function_object,
                                  KLFunctionType function_type)
{
  set_function_function_type(get_function(function_object), function_type);
}

INLINE KLObject* create_primitive_kl_function (long parameter_size,
                                               NativeFunction* native_function)
{
  KLObject* function_object = create_kl_object(KL_TYPE_FUNCTION);
  Function* function = create_function(KL_FUNCTION_TYPE_PRIMITIVE_FUNCTION);
  PrimitiveFunction* primitive_function =
    get_function_primitive_function(function);

  set_primitive_function_parameter_size(primitive_function, parameter_size);
  set_primitive_function_native_function(primitive_function, native_function);
  set_function(function_object, function);

  return function_object;
}

INLINE PrimitiveFunction* get_kl_function_primitive_function
(KLObject* function_object)
{
  return get_function_primitive_function(get_function(function_object));
}

INLINE void set_kl_function_primitive_function
(KLObject* function_object, PrimitiveFunction* primitive_function)
{
  set_function_primitive_function(get_function(function_object),
                                  primitive_function);
}

INLINE KLObject* create_user_kl_function (void)
{
  KLObject* function_object = create_kl_object(KL_TYPE_FUNCTION);
  Function* function = create_function(KL_FUNCTION_TYPE_USER_FUNCTION);

  set_function(function_object, function);

  return function_object;
}

INLINE UserFunction* get_kl_function_user_function (KLObject* function_object)
{
  return get_function_user_function(get_function(function_object));
}

INLINE void set_kl_function_user_function (KLObject* function_object,
                                           UserFunction* user_function)
{
  set_function_user_function(get_function(function_object),
                             user_function);
}

INLINE KLObject* create_closure_kl_function (void)
{
  KLObject* function_object = create_kl_object(KL_TYPE_FUNCTION);
  Function* function = create_function(KL_FUNCTION_TYPE_CLOSURE);

  set_function(function_object, function);

  return function_object;
}

INLINE Closure* get_kl_function_closure (KLObject* function_object)
{
  return get_function_closure(get_function(function_object));
}

INLINE void set_kl_function_closure (KLObject* function_object, Closure* closure)
{
  set_function_closure(get_function(function_object), closure);
}

INLINE void check_function_argument_size (long argument_size, long parameter_size)
{
  if (argument_size != parameter_size)
    throw_kl_exception("Wrong number of arguments passed to function");
}

INLINE bool is_kl_function_equal (KLObject* left_object, KLObject* right_object)
{
  return left_object == right_object;
}

INLINE void check_function_user_parameters (Vector* parameters)
{
  if (is_not_null(parameters)) {
    KLObject** objects = get_vector_objects(parameters);
    long parameters_size = get_vector_size(parameters);

    for (long i = 0; i < parameters_size; ++i) {
      if (!is_kl_symbol(objects[i]))
        throw_kl_exception("Function parameters should be symbols");
    }
  }
}

#endif
