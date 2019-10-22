#include "list.h"

#include "defs.h"

EXTERN Pair* get_pair (KLObject* list_object);
EXTERN void set_pair (KLObject* list_object, Pair* pair);
EXTERN KLObject* create_kl_list (KLObject* car_object, KLObject* cdr_object);
EXTERN KLObject* get_head_kl_list (KLObject* list_object);
EXTERN void set_head_kl_list (KLObject* list_object, KLObject* car_object);
EXTERN KLObject* get_tail_kl_list (KLObject* list_object);
EXTERN void set_tail_kl_list (KLObject* list_object, KLObject* cdr_object);
EXTERN bool is_kl_list (KLObject* object);
EXTERN bool is_non_empty_kl_list (KLObject* object);
EXTERN long get_kl_list_size (KLObject* list_object);
