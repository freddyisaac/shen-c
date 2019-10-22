#ifndef SHEN_C_HASH_H
#define SHEN_C_HASH_H

#include "defs.h"

#include "kl.h"
#include "number.h"
#include "object.h"

INLINE size_t djb2_hash (unsigned char *string)
{
  size_t hash = 5381;
  int c;

  while ((c = *string++))
    hash = ((hash << 5) + hash) + c;

  return hash;
}

INLINE long bounded_hash (char* string, long divisor)
{
  long hash = djb2_hash((unsigned char*)string) % divisor;

  return (hash == 0) ? 1 : hash;
}

INLINE KLObject* kl_object_bounded_hash (KLObject* object,
                                         KLObject* number_object)
{
  return create_kl_number_l(bounded_hash(kl_object_to_string(object),
                                         get_kl_number_number_l(number_object)));
}

#endif
