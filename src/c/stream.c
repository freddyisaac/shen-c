#include "stream.h"

#include "defs.h"

char* shen_c_home_path;

KLObject* std_input_stream_object;
KLObject* std_output_stream_object;
KLObject* std_error_stream_object;

size_t read_buffer_allocation_size = 100;
char* read_buffer;
size_t read_buffer_position = 0;

EXTERN void initialize_shen_c_home_path (char* home_path);
EXTERN char* get_shen_c_home_path (void);

EXTERN FILE* get_stream_file (Stream* stream);
EXTERN void set_stream_file (Stream* stream, FILE* file);
EXTERN KLStreamType get_stream_stream_type (Stream* stream);
EXTERN void set_stream_stream_type (Stream* stream, KLStreamType stream_type);
EXTERN Stream* create_stream (FILE* file, KLStreamType stream_type);

EXTERN char* stream_type_to_stream_type_string (KLStreamType stream_type);

EXTERN Stream* get_stream (KLObject* stream_object);
EXTERN void set_stream (KLObject* stream_object, Stream* stream);
EXTERN KLObject* create_kl_stream (char* file_path,
                                   KLObject* stream_type_symbol_object);
EXTERN KLObject* create_kl_stream_from_home_path
(char* file_path, KLObject* stream_type_symbol_object);
EXTERN FILE* get_kl_stream_file (KLObject* stream_object);
EXTERN void set_kl_stream_file (KLObject* stream_object, FILE* file);
EXTERN KLStreamType get_kl_stream_stream_type (KLObject* stream_object);
EXTERN void set_kl_stream_stream_type (KLObject* stream_object,
                                       KLStreamType stream_type);
EXTERN KLObject* close_kl_stream (KLObject* stream_object);

EXTERN KLObject* create_std_kl_stream (FILE* file,
                                       KLObject* stream_type_symbol_object);
EXTERN void initialize_std_input_stream_object (void);
EXTERN void initialize_std_output_stream_object (void);
EXTERN void initialize_std_error_stream_object (void);
EXTERN void initialize_std_stream_objects (void);
EXTERN KLObject* get_std_input_stream_object (void);
EXTERN KLObject* get_std_output_stream_object (void);
EXTERN KLObject* get_std_error_stream_object (void);
EXTERN void initialize_std_stream_objects (void);

EXTERN bool is_kl_stream (KLObject* object);
EXTERN bool is_kl_stream_equal (KLObject* left_object, KLObject* right_object);

EXTERN char read_byte (FILE* file);
EXTERN KLObject* read_kl_stream_byte (KLObject* stream_object);
EXTERN char* get_read_buffer (void);
EXTERN void set_read_buffer (char* buffer);
EXTERN size_t get_read_buffer_allocation_size (void);
EXTERN void set_read_buffer_allocation_size (size_t size);
EXTERN void initialize_read_buffer (void);
EXTERN int read_byte_with_buffer (FILE* file);
EXTERN void unread_byte_with_buffer (char c);
EXTERN void unread_bytes_with_buffer (char* lookahead_buffer);
EXTERN char write_byte (FILE* file, char c);
EXTERN KLObject* write_kl_stream_byte (KLObject* stream_object,
                                       KLObject* number_object);

EXTERN char* read_file (FILE* file);
EXTERN char* read_file_by_file_path (char* file_path);
EXTERN char* read_file_by_file_path_from_home_path (char* file_path);

char* kl_stream_to_string (KLObject* stream_object)
{
  if (stream_object == get_std_input_stream_object())
    return "#<Stream {stinput} in>";
  else if (stream_object == get_std_output_stream_object())
    return "#<Stream {stoutput} out>";
  else if (stream_object == get_std_error_stream_object())
    return "#<Stream {sterror} out>";

  Stream* stream = get_stream(stream_object);
  char* stream_type_string =
    stream_type_to_stream_type_string(get_stream_stream_type(stream));
  char* object_string;
  int object_string_length = snprintf(NULL, 0,
                                      "#<Stream {0x%016p\" PRIxPTR \"} %s>",
                                      (uintptr_t)stream_object,
                                      stream_type_string);

  object_string = malloc((size_t)object_string_length + 1);
  sprintf(object_string, "#<Stream {0x%016p\" PRIxPTR \"} %s>",
          (uintptr_t)stream_object, stream_type_string);

  return object_string;
}
