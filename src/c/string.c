#include "string.h"

#include "defs.h"

khash_t(StringTable)* string_table;

KLObject* empty_string_object;
KLObject* true_string_object;
KLObject* false_string_object;
KLObject* three_dots_string_object;

EXTERN KLObject* get_empty_string_object (void);
EXTERN KLObject* get_true_string_object (void);
EXTERN KLObject* get_false_string_object (void);
EXTERN KLObject* get_three_dots_string_object (void);

EXTERN char* get_string (KLObject* string_object);
EXTERN void set_string (KLObject* string_object, char* string);
EXTERN KLObject* create_kl_string (char *string);
EXTERN khash_t(StringTable)* get_string_table (void);
EXTERN void initialize_string_table (void);
EXTERN KLObject* lookup_string_table (char* string);
EXTERN void extend_string_table (char* string, KLObject* object);
EXTERN KLObject* create_kl_string_with_intern (char* string);
EXTERN bool is_kl_string (KLObject* object);
EXTERN bool is_kl_string_equal (KLObject* left_object, KLObject* right_object);
EXTERN char* get_position_string (char* string, long index);
EXTERN KLObject* get_position_kl_string (KLObject* string_object,
                                         KLObject* number_object);

static inline void register_empty_string_object (void)
{
  empty_string_object = create_kl_string("");
  extend_string_table("", empty_string_object);
}

static inline void register_true_string_object (void)
{
  true_string_object = create_kl_string("true");
  extend_string_table("true", true_string_object);
}

static inline void register_false_string_object (void)
{
  false_string_object = create_kl_string("false");
  extend_string_table("false", false_string_object);
}

static inline void register_three_dots_string_object (void)
{
  three_dots_string_object = create_kl_string("...");
  extend_string_table("...", three_dots_string_object);
}

void register_string_objects (void)
{
  register_empty_string_object();
  register_true_string_object();
  register_false_string_object();
  register_three_dots_string_object();
}

char* string_to_double_quoted_string (char* string)
{
  size_t string_length = strlen(string);
  size_t double_quoted_string_length = string_length + 2;
  char* double_quoted_string = malloc(double_quoted_string_length + 1);

  double_quoted_string[0] = '"';

  for (size_t i = 0; i < string_length; ++i)
    double_quoted_string[i + 1] = string[i];

  double_quoted_string[double_quoted_string_length - 1] = '"';
  double_quoted_string[double_quoted_string_length] = '\0';

  return double_quoted_string;
}

char* get_double_quoted_string (KLObject* string_object)
{
  return string_to_double_quoted_string(get_string(string_object));
}

char* get_tail_string (char* string)
{
  if (strlen(string) == 0)
    throw_kl_exception("Should be a non-empty string");
  
  size_t string_length = strlen(string);
  char* tail_string = malloc(string_length);

  for (size_t i = 0; i < string_length - 1; ++i)
    tail_string[i] = string[i + 1];

  tail_string[string_length - 1] = '\0';

  return tail_string;
}

KLObject* get_tail_kl_string (KLObject* string_object)
{
  if (!is_kl_string(string_object))
    throw_kl_exception("Parameter should be a string");

  return create_kl_string_with_intern(get_tail_string(get_string(string_object)));
}

char* concatenate_string (char* left_string, char* right_string)
{
  char* string = malloc(strlen(left_string) + strlen(right_string) + 1);
  
  strcpy(string, left_string);
  strcat(string, right_string);
  
  return string;
}

KLObject* concatenate_kl_string (KLObject* left_string_object,
                                 KLObject* right_string_object)
{
  char* string =  concatenate_string(get_string(left_string_object),
                                     get_string(right_string_object));

  return create_kl_string_with_intern(string);
}

char* code_point_to_string (long code_point)
{
  if (code_point < 0)
    throw_kl_exception("Should be a non-negative integer");
  
  char* string = malloc(2);
  char c = (char)code_point;

  string[0] = c;
  string[1] = '\0';

  return string;
}

KLObject* kl_number_code_point_to_kl_string (KLObject* number_object)
{
  char* string = code_point_to_string(get_kl_number_number_l(number_object));

  return create_kl_string_with_intern(string);
}

long string_to_code_point (char* string)
{
  if (strlen(string) == 0)
    throw_kl_exception("Should be a non-empty string");

  return string[0];
}

KLObject* kl_string_to_kl_number_code_point (KLObject* string_object)
{
  long code_point = string_to_code_point(get_string(string_object));

  return create_kl_number_l(code_point);
}

char* append_string (char* string_destination,
                     size_t* string_destination_allocation_size_ref,
                     char* string_source)
{
  size_t new_string_destination_length =
    strlen(string_destination) + strlen(string_source);
    
  if (new_string_destination_length + 1 <=
      *string_destination_allocation_size_ref)
    return strcat(string_destination, string_source);
  else {
    size_t new_string_destination_allocation_size =
      new_string_destination_length * 2;
    char* new_string_destination = malloc(new_string_destination_allocation_size);

    *string_destination_allocation_size_ref =
      new_string_destination_allocation_size;
    strcpy(new_string_destination, string_destination);

    return strcat(new_string_destination, string_source);
  }
}

char* append_character_to_string (char* string_destination,
                                  size_t* string_destination_allocation_size_ref,
                                  char char_source)
{
  char* string_source = malloc(2);

  string_source[0] = char_source;
  string_source[1] = '\0';

  return append_string(string_destination,
                       string_destination_allocation_size_ref,
                       string_source);
}

char* long_to_string (long x)
{
  int object_string_length = snprintf(NULL, 0, "%ld", x);
  char* object_string = malloc((size_t)object_string_length + 1);

  sprintf(object_string, "%ld", x);

  return object_string;
}

char* double_to_string (double x)
{
  int object_string_length = snprintf(NULL, 0, "%.*g", DBL_DIG, x);
  char* object_string = malloc((size_t)object_string_length + 1);

  sprintf(object_string, "%.*g", DBL_DIG, x);  

  bool is_integer = true;

  for (int i = 0; i < object_string_length; ++i)
    if (is_dot_character(object_string[i]) || object_string[i] == 'e') {
      is_integer = false;
      break;
    }

  if (is_integer)
    object_string = concatenate_string(object_string, ".0");

  return  object_string;
}

char* kl_number_to_string (KLObject* number_object)
{
  char* number_object_string = NULL;

  if (is_kl_number_l(number_object))
    number_object_string = long_to_string(get_kl_number_number_l(number_object));
  else if (is_kl_number_d(number_object))
    number_object_string = double_to_string(get_kl_number_number_d(number_object));
  else
    throw_kl_exception("Not a number");

  return number_object_string;
}
