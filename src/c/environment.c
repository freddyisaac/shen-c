#include "environment.h"

#include "defs.h"

Environment* global_function_environment = NULL;
Environment* global_variable_environment = NULL;

EXTERN khash_t(ObjectTable)* get_environment_symbol_object_table
(Environment* environment);
EXTERN void set_environment_symbol_object_table
(Environment* environment, khash_t(ObjectTable)* symbol_object_table);
EXTERN Environment* get_parent_environment (Environment* environment);
EXTERN void set_parent_environment (Environment* environment,
                                    Environment* parent_environment);
EXTERN Environment* create_environment (void);
EXTERN Environment* get_global_function_environment (void);
EXTERN Environment* get_global_variable_environment (void);
EXTERN void extend_environment (KLObject* symbol_object, KLObject* object,
                                Environment* environment);

KLObject* lookup_environment (KLObject* symbol_object, Environment* environment)
{ 
  khash_t(ObjectTable)* symbol_object_table;
  khiter_t hash_iterator;
  bool is_key_not_found;
  Environment* new_environment = environment;
  Environment* parent_environment;

  while (true) {
    symbol_object_table = get_environment_symbol_object_table(new_environment);
    hash_iterator = kh_get(ObjectTable, symbol_object_table,
                           (kl_khint_ptr_t)symbol_object);
    is_key_not_found = hash_iterator == kh_end(symbol_object_table);

    if (is_key_not_found || kh_exist(symbol_object_table, hash_iterator) == 0) {
      parent_environment = get_parent_environment(new_environment);

      if (is_null(parent_environment))
        return NULL;

      new_environment = parent_environment;

      continue;
    }

    return kh_value(symbol_object_table, hash_iterator);
  }
}
