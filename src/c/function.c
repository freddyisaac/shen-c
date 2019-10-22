#include "function.h"

#include "defs.h"

EXTERN long get_primitive_function_parameter_size
(PrimitiveFunction* primitive_function);
EXTERN void set_primitive_function_parameter_size
(PrimitiveFunction* primitive_function, long parameter_size);
EXTERN NativeFunction* get_primitive_function_native_function
(PrimitiveFunction* primitive_function);
EXTERN void set_primitive_function_native_function
(PrimitiveFunction* primitive_function, NativeFunction* native_function);
EXTERN PrimitiveFunction* create_primitive_function (void);

EXTERN Vector* get_user_function_parameters (UserFunction* user_function);
EXTERN void set_user_function_parameters (UserFunction* user_function,
                                          Vector* parameters);
EXTERN KLObject* get_user_function_body (UserFunction* user_function);
EXTERN void set_user_function_body (UserFunction* user_function,
                                    KLObject* body_object);
EXTERN UserFunction* create_user_function (void);

EXTERN KLObject* get_closure_parameter (Closure* closure);
EXTERN void set_closure_parameter (Closure* closure, KLObject* parameter);
EXTERN KLObject* get_closure_body (Closure* closure);
EXTERN void set_closure_body (Closure* closure, KLObject* body_object);
EXTERN Environment* get_closure_parent_function_environment (Closure* closure);
EXTERN void set_closure_parent_function_environment
(Closure* closure, Environment* parent_function_environment);
EXTERN Environment* get_closure_parent_variable_environment (Closure* closure);
EXTERN void set_closure_parent_variable_environment
(Closure* closure, Environment* parent_variable_environment);
EXTERN Closure* create_closure (void);

EXTERN KLFunctionType get_function_function_type (Function* function);
EXTERN void set_function_function_type (Function* function,
                                        KLFunctionType function_type);
EXTERN PrimitiveFunction* get_function_primitive_function (Function* function);
EXTERN void set_function_primitive_function
(Function* function, PrimitiveFunction* primitive_function);

EXTERN UserFunction* get_function_user_function (Function* function);
EXTERN void set_function_user_function (Function* function,
                                        UserFunction* user_function);
EXTERN Closure* get_function_closure (Function* function);
EXTERN void set_function_closure (Function* function, Closure* closure);
EXTERN bool is_primitive_function (Function* function);
EXTERN bool is_user_function (Function* function);
EXTERN bool is_closure (Function* function);
EXTERN Function* create_function (KLFunctionType function_type);

EXTERN Function* get_function (KLObject* function_object);
EXTERN void set_function (KLObject* function_object, Function* function);
EXTERN bool is_kl_function (KLObject* object);
EXTERN bool is_primitive_kl_function (KLObject* object);
EXTERN bool is_user_kl_function (KLObject* object);
EXTERN bool is_closure_kl_function (KLObject* object);
EXTERN KLFunctionType get_kl_function_type (KLObject* function_object);
EXTERN void set_kl_function_type (KLObject* function_object,
                                  KLFunctionType function_type);

EXTERN KLObject* create_primitive_kl_function (long parameter_size,
                                               NativeFunction* native_function);
EXTERN PrimitiveFunction* get_kl_function_primitive_function
(KLObject* function_object);
EXTERN void set_kl_function_primitive_function
(KLObject* function_object, PrimitiveFunction* primitive_function);

EXTERN KLObject* create_user_kl_function (void);
EXTERN UserFunction* get_kl_function_user_function (KLObject* function_object);
EXTERN void set_kl_function_user_function (KLObject* function_object,
                                           UserFunction* user_function);

EXTERN KLObject* create_closure_kl_function (void);
EXTERN Closure* get_kl_function_closure (KLObject* function_object);
EXTERN void set_kl_function_closure (KLObject* function_object, Closure* closure);

EXTERN void check_function_argument_size (long argument_size, long parameter_size);
EXTERN bool is_kl_function_equal (KLObject* left_object, KLObject* right_object);
EXTERN void check_function_user_parameters (Vector* parameters);
