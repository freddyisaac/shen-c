#include "dictionary.h"

#include "defs.h"

EXTERN khash_t(StringPairTable)* get_dictionary_table (Dictionary* dictionary);
EXTERN void set_dictionary_table (Dictionary* dictionary,
                                  khash_t(StringPairTable)* table);
EXTERN Dictionary* create_dictionary (void);
EXTERN Dictionary* get_dictionary (KLObject* dictionary_object);
EXTERN void set_dictionary (KLObject* dictionary_object, Dictionary* dictionary);
EXTERN KLObject* create_kl_dictionary (void);
EXTERN khash_t(StringPairTable)* get_kl_dictionary_table
(KLObject* dictionary_object);
EXTERN void set_kl_dictionary_table (KLObject* dictionary_object,
                                     khash_t(StringPairTable)* table);
EXTERN bool is_kl_dictionary (KLObject* object);
EXTERN long get_dictionary_count (Dictionary* dictionary);
EXTERN KLObject* get_kl_dictionary_count (KLObject* dictionary_object);
EXTERN KLObject* get_dictionary_keys (Dictionary* dictionary);
EXTERN KLObject* get_kl_dictionary_keys (KLObject* dictionary_object);
EXTERN KLObject* get_dictionary_values (Dictionary* dictionary);
EXTERN KLObject* get_kl_dictionary_values (KLObject* dictionary_object);
