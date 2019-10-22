#include "symbol.h"

#include "defs.h"

unsigned long auto_increment_symbol_name_id = 0;
char* auto_increment_symbol_name_prefix = "G__";
khash_t(SymbolTable)* symbol_table;

EXTERN KLObject* get_symbol_name (Symbol* symbol);
EXTERN void set_symbol_name (Symbol* symbol, KLObject* string_object);
EXTERN KLObject* get_symbol_function (Symbol* symbol);
EXTERN void set_symbol_function (Symbol* symbol, KLObject* function_object);
EXTERN KLObject* get_symbol_variable_value (Symbol* symbol);
EXTERN void set_symbol_variable_value (Symbol* symbol,
                                       KLObject* variable_value_object);
EXTERN Symbol* create_symbol (KLObject* string_object);

EXTERN Symbol* get_symbol (KLObject* symbol_object);
EXTERN void set_symbol (KLObject* symbol_object, Symbol* symbol);
EXTERN KLObject* create_kl_symbol (KLObject* string_object);
EXTERN KLObject* create_kl_symbol_by_name (char* symbol_name);
EXTERN KLObject* get_kl_symbol_name (KLObject* symbol_object);
EXTERN void set_kl_symbol_name (KLObject* symbol_object, KLObject* string_object);
EXTERN KLObject* get_kl_symbol_function (KLObject* symbol_object);
EXTERN void set_kl_symbol_function (KLObject* symbol_object,
                                    KLObject* function_object);
EXTERN KLObject* get_kl_symbol_variable_value (KLObject* symbol_object);
EXTERN void set_kl_symbol_variable_value (KLObject* symbol_object,
                                          KLObject* variable_value_object);
EXTERN bool is_kl_symbol (KLObject* object);
EXTERN bool is_symbol_equal (Symbol* left_symbol, Symbol* right_symbol);
EXTERN bool is_kl_symbol_equal (KLObject* left_object, KLObject* right_object);

EXTERN unsigned long get_auto_increment_symbol_name_id (void);
EXTERN unsigned long pre_increment_auto_increment_symbol_name_id (void);
EXTERN char* get_auto_increment_symbol_name_prefix (void);
EXTERN char* create_auto_increment_symbol_name (void);
EXTERN KLObject* create_auto_increment_kl_symbol (void);

EXTERN khash_t(SymbolTable)* get_symbol_table (void);
EXTERN void initialize_symbol_table (void);
EXTERN KLObject* lookup_symbol_table (KLObject* string_object);
EXTERN void extend_symbol_table (KLObject* string_object, KLObject* object);
