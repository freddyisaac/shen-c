#include "hash.h"

#include "defs.h"

EXTERN size_t djb2_hash (unsigned char *str);
EXTERN long bounded_hash (char* string, long divisor);
EXTERN KLObject* kl_object_bounded_hash (KLObject* object,
                                         KLObject* number_object);
