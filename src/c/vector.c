#include "vector.h"

#include "defs.h"

Vector* empty_vector = NULL;

EXTERN KLObject** get_vector_objects (Vector* vector);
EXTERN void set_vector_objects (Vector* vector, KLObject** objects);
EXTERN long get_vector_size (Vector* vector);
EXTERN void set_vector_size (Vector* vector, long size);
EXTERN Vector* create_vector (long size);
EXTERN void initialize_empty_vector (void);
EXTERN Vector* get_empty_vector (void);
EXTERN bool is_empty_vector (Vector* vector);
EXTERN KLObject* get_vector_element (Vector* vector, long index);
EXTERN void set_vector_element (Vector* vector, long index, KLObject* object);

EXTERN Vector* get_vector(KLObject* vector_object);
EXTERN void set_vector (KLObject* vector_object, Vector* vector);
EXTERN KLObject* create_kl_vector (long size);
EXTERN bool is_kl_vector (KLObject* object);
EXTERN KLObject** get_kl_vector_objects (KLObject* vector_object);
EXTERN void set_kl_vector_objects (KLObject* vector_object, KLObject** objects);
EXTERN long get_kl_vector_size (KLObject* vector_object);
EXTERN void set_kl_vector_size (KLObject* vector_object, long size);
EXTERN KLObject* get_kl_vector_element (KLObject* vector_object,
                                        KLObject* number_object);
EXTERN KLObject* set_kl_vector_element (KLObject* vector_object,
                                        KLObject* number_object,
                                        KLObject* object);
