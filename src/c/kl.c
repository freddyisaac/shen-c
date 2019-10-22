#include "kl.h"

#include "defs.h"

KLObject* empty_list_object = NULL;

EXTERN KLType get_kl_object_type (KLObject* object);
EXTERN void set_kl_object_type (KLObject* object, KLType type);
EXTERN KLObject* create_kl_object (KLType type);
EXTERN bool is_null (void* object);
EXTERN bool is_not_null (void* object);

EXTERN KLObject* get_pair_car (Pair* pair);
EXTERN void set_pair_car (Pair* pair, KLObject* object);
EXTERN KLObject* get_pair_cdr (Pair* pair);
EXTERN void set_pair_cdr (Pair* pair, KLObject* object);
EXTERN Pair* create_pair (KLObject* car_object, KLObject* cdr_object);

EXTERN void initialize_empty_kl_list (void);
EXTERN KLObject* get_empty_kl_list (void);
EXTERN bool is_empty_kl_list (KLObject* object);
