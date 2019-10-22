#include "boolean.h"

#include "defs.h"

KLObject* true_boolean_object;
KLObject* false_boolean_object;

EXTERN bool get_boolean (KLObject* boolean_object);
EXTERN void set_boolean (KLObject* boolean_object, bool boolean);
EXTERN KLObject* create_kl_boolean (bool boolean);
EXTERN void initialize_true_boolean_object (void);
EXTERN void initialize_false_boolean_object (void);
EXTERN void initialize_boolean_objects (void);
EXTERN KLObject* get_true_boolean_object (void);
EXTERN KLObject* get_false_boolean_object (void);
EXTERN bool is_kl_boolean (KLObject* boolean_object);
EXTERN char* kl_boolean_to_string (KLObject* boolean_object);
EXTERN bool is_kl_boolean_equal (KLObject* left_object, KLObject* right_object);
