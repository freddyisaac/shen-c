#ifndef SHEN_C_SYMBOL_H
#define SHEN_C_SYMBOL_H

#include "defs.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "boolean.h"
#include "exception.h"
#include "kl.h"
#include "string.h"

extern unsigned long auto_increment_symbol_name_id;
extern char* auto_increment_symbol_name_prefix;
extern khash_t(SymbolTable)* symbol_table;

INLINE KLObject* get_symbol_name (Symbol* symbol)
{
  return symbol->name;
}

INLINE void set_symbol_name (Symbol* symbol, KLObject* string_object)
{
  symbol->name = string_object;
}

INLINE KLObject* get_symbol_function (Symbol* symbol)
{
  return symbol->function;
}

INLINE void set_symbol_function (Symbol* symbol, KLObject* function_object)
{
  symbol->function = function_object;
}

INLINE KLObject* get_symbol_variable_value (Symbol* symbol)
{
  return symbol->variable_value;
}

INLINE void set_symbol_variable_value (Symbol* symbol,
                                       KLObject* variable_value_object)
{
  symbol->variable_value = variable_value_object;
}

INLINE Symbol* create_symbol (KLObject* string_object)
{
  Symbol *symbol = malloc(sizeof(Symbol));

  set_symbol_name(symbol, string_object);
  set_symbol_function(symbol, NULL);
  set_symbol_variable_value(symbol, NULL);

  return symbol;
}

INLINE Symbol* get_symbol (KLObject* symbol_object)
{
  return symbol_object->value.symbol;
}

INLINE void set_symbol (KLObject* symbol_object, Symbol* symbol)
{
  symbol_object->value.symbol = symbol;
}

INLINE KLObject* create_kl_symbol (KLObject* string_object)
{
  KLObject* symbol_object = create_kl_object(KL_TYPE_SYMBOL);
  Symbol* symbol = create_symbol(string_object);

  set_symbol(symbol_object, symbol);

  return symbol_object;
}

INLINE KLObject* create_kl_symbol_by_name (char* symbol_name)
{
  return create_kl_symbol(create_kl_string_with_intern(symbol_name));
}

INLINE KLObject* get_kl_symbol_name (KLObject* symbol_object)
{
  return get_symbol_name(get_symbol(symbol_object));
}

INLINE void set_kl_symbol_name (KLObject* symbol_object, KLObject* string_object)
{
  set_symbol_name(get_symbol(symbol_object), string_object);
}

INLINE KLObject* get_kl_symbol_function (KLObject* symbol_object)
{
  return get_symbol_function(get_symbol(symbol_object));
}

INLINE void set_kl_symbol_function (KLObject* symbol_object,
                                    KLObject* function_object)
{
  set_symbol_function(get_symbol(symbol_object), function_object);
}

INLINE KLObject* get_kl_symbol_variable_value (KLObject* symbol_object)
{
  return get_symbol_variable_value(get_symbol(symbol_object));
}

INLINE void set_kl_symbol_variable_value (KLObject* symbol_object,
                                          KLObject* variable_value_object)
{
  set_symbol_variable_value(get_symbol(symbol_object),
                            variable_value_object);
}

INLINE bool is_kl_symbol (KLObject* object)
{
  return get_kl_object_type(object) == KL_TYPE_SYMBOL;
}

INLINE bool is_symbol_equal (Symbol* left_symbol, Symbol* right_symbol)
{
  return left_symbol == right_symbol;
}

INLINE bool is_kl_symbol_equal (KLObject* left_object, KLObject* right_object)
{
  return left_object == right_object;
}

INLINE unsigned long get_auto_increment_symbol_name_id (void)
{
  return auto_increment_symbol_name_id;
}

INLINE unsigned long pre_increment_auto_increment_symbol_name_id (void)
{
  return ++auto_increment_symbol_name_id;
}

INLINE char* get_auto_increment_symbol_name_prefix (void)
{
  return auto_increment_symbol_name_prefix;
}

INLINE char* create_auto_increment_symbol_name (void)
{
  pre_increment_auto_increment_symbol_name_id();

  int symbol_name_length = snprintf(NULL, 0, "%s%zu",
                                    get_auto_increment_symbol_name_prefix(),
                                    get_auto_increment_symbol_name_id());
  char* symbol_name = malloc((size_t)symbol_name_length + 1);

  sprintf(symbol_name, "%s%zu", get_auto_increment_symbol_name_prefix(),
          get_auto_increment_symbol_name_id());

  return symbol_name;
}

INLINE KLObject* create_auto_increment_kl_symbol (void)
{
  return create_kl_symbol_by_name(create_auto_increment_symbol_name());
}

INLINE khash_t(SymbolTable)* get_symbol_table (void)
{
  return symbol_table;
}

INLINE void initialize_symbol_table (void)
{
  symbol_table = kh_init(SymbolTable);
}

INLINE KLObject* lookup_symbol_table (KLObject* string_object)
{
  khash_t(SymbolTable)* table = get_symbol_table();
  khiter_t hash_iterator = kh_get(SymbolTable, table, (kl_khint_ptr_t)string_object);
  bool is_key_not_found = hash_iterator == kh_end(table);

  if (is_key_not_found || kh_exist(table, hash_iterator) == 0)
    return NULL;

  return kh_value(table, hash_iterator);
}

INLINE void extend_symbol_table (KLObject* string_object, KLObject* symbol_object)
{
  khash_t(SymbolTable)* table = get_symbol_table();
  int put_result;
  khiter_t hash_iterator = kh_put(SymbolTable, table, (kl_khint_ptr_t)string_object,
                                  &put_result);

  if (put_result == -1)
    throw_kl_exception("Failed to extend symbol name table");

  kh_value(table, hash_iterator) = symbol_object;
}

#endif
