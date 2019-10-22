#include "character.h"

#include "defs.h"

char* symbol_characters =
  "=-*/+_?$!@~.><&%\'#`;:{}"
  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
  "012356789";

EXTERN char* get_symbol_characters(void);
EXTERN bool is_left_parenthesis_character (char c);
EXTERN bool is_right_parenthesis_character (char c);
EXTERN bool is_double_quotation_character (char c);
EXTERN bool is_plus_character (char c);
EXTERN bool is_minus_character (char c);
EXTERN bool is_dot_character (char c);
EXTERN bool is_whitespace_character (char c);
EXTERN bool is_lowercase_alphabet_character (char c);
EXTERN bool is_uppercase_alphabet_character (char c);
EXTERN bool is_alphabet_character (char c);
EXTERN bool is_numeric_character (char c);
EXTERN bool is_alphanumeric_character (char c);
EXTERN bool is_non_alphanumeric_symbol_character (char c);
EXTERN bool is_symbol_character (char c);
