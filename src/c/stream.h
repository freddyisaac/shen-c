#ifndef SHEN_C_STREAM_H
#define SHEN_C_STREAM_H

#include "defs.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
//#include <inttypes.h>

#include "exception.h"
#include "kl.h"
#include "number.h"
#include "string.h"
#include "symbol_pool.h"

extern char* shen_c_home_path;

extern KLObject* std_input_stream_object;
extern KLObject* std_output_stream_object;
extern KLObject* std_error_stream_object;

extern size_t read_buffer_allocation_size;
extern char* read_buffer;
extern size_t read_buffer_position ;

INLINE void initialize_shen_c_home_path (char* home_path)
{
  shen_c_home_path = home_path;
}

INLINE char* get_shen_c_home_path (void)
{
  return shen_c_home_path;
}

char* kl_stream_to_string (KLObject* stream_object);

INLINE FILE* get_stream_file (Stream* stream)
{
  return stream->file;
}

INLINE void set_stream_file (Stream* stream, FILE* file)
{
  stream->file = file;
}

INLINE KLStreamType get_stream_stream_type (Stream* stream)
{
  return stream->stream_type;
}

INLINE void set_stream_stream_type (Stream* stream, KLStreamType stream_type)
{
  stream->stream_type = stream_type;
}

INLINE Stream* create_stream (FILE* file, KLStreamType stream_type)
{
  Stream* stream = malloc(sizeof(Stream));

  set_stream_file(stream, file);
  set_stream_stream_type(stream, stream_type);

  return stream;
}

INLINE char* stream_type_to_stream_type_string (KLStreamType stream_type)
{
  if (stream_type == KL_STREAM_TYPE_IN)
    return "in";

  if (stream_type == KL_STREAM_TYPE_OUT)
    return "out";

  throw_kl_exception("Unknown stream type");

  return NULL;
}

INLINE Stream* get_stream (KLObject* stream_object)
{
  return stream_object->value.stream;
}

INLINE void set_stream (KLObject* stream_object, Stream* stream)
{
  stream_object->value.stream = stream;
}

INLINE KLObject* create_kl_stream (char* file_path,
                                   KLObject* stream_type_symbol_object)
{
  char* open_mode_string;
  KLStreamType stream_type;

  if (stream_type_symbol_object == get_in_symbol_object()) {
    open_mode_string = "r";
    stream_type = KL_STREAM_TYPE_IN;
  } else if (stream_type_symbol_object == get_out_symbol_object()) {
    open_mode_string = "w";
    stream_type = KL_STREAM_TYPE_OUT;
  } else
    throw_kl_exception("Unknown stream type");

  FILE* file = fopen(file_path, open_mode_string);

  if (is_null(file))
    throw_kl_exception("Failed to open stream");

  KLObject* stream_object = create_kl_object(KL_TYPE_STREAM);
  Stream* stream = create_stream(file, stream_type);

  set_stream(stream_object, stream);

  return stream_object;
}

INLINE KLObject* create_kl_stream_from_home_path
(char* file_path, KLObject* stream_type_symbol_object)
{
  char* absolute_file_path = concatenate_string(get_shen_c_home_path(), file_path);

  return create_kl_stream(absolute_file_path, stream_type_symbol_object);
}

INLINE FILE* get_kl_stream_file (KLObject* stream_object)
{
  return get_stream_file(get_stream(stream_object));
}

INLINE void set_kl_stream_file (KLObject* stream_object, FILE* file)
{
  set_stream_file(get_stream(stream_object), file);
}

INLINE KLStreamType get_kl_stream_stream_type (KLObject* stream_object)
{
  return get_stream_stream_type(get_stream(stream_object));
}

INLINE void set_kl_stream_stream_type (KLObject* stream_object,
                                       KLStreamType stream_type)
{
  set_stream_stream_type(get_stream(stream_object), stream_type);
}

INLINE KLObject* close_kl_stream (KLObject* stream_object)
{
  int stream_status = fclose(get_kl_stream_file(stream_object));

  if (stream_status != 0)
    throw_kl_exception("Failed to close stream");

  return EL;
}

INLINE KLObject* create_std_kl_stream (FILE* file,
                                       KLObject* stream_type_symbol_object)
{
  KLStreamType stream_type;

  if (stream_type_symbol_object == get_in_symbol_object())
    stream_type = KL_STREAM_TYPE_IN;
  else if (stream_type_symbol_object == get_out_symbol_object())
    stream_type = KL_STREAM_TYPE_OUT;
  else
    throw_kl_exception("Unknown stream type");

  KLObject* stream_object = create_kl_object(KL_TYPE_STREAM);
  Stream* stream = create_stream(file, stream_type);

  set_stream(stream_object, stream);

  return stream_object;
}

INLINE void initialize_std_input_stream_object (void)
{
  std_input_stream_object = create_std_kl_stream(stdin, get_in_symbol_object());
}

INLINE void initialize_std_output_stream_object (void)
{
  std_output_stream_object = create_std_kl_stream(stdout, get_out_symbol_object());
}

INLINE void initialize_std_error_stream_object (void)
{
  std_error_stream_object = create_std_kl_stream(stderr, get_out_symbol_object());
}

INLINE void initialize_std_stream_objects (void)
{
  initialize_std_input_stream_object();
  initialize_std_output_stream_object();
  initialize_std_error_stream_object();
}

INLINE KLObject* get_std_input_stream_object (void)
{
  return std_input_stream_object;
}

INLINE KLObject* get_std_output_stream_object (void)
{
  return std_output_stream_object;
}

INLINE KLObject* get_std_error_stream_object (void)
{
  return std_error_stream_object;
}


INLINE bool is_kl_stream (KLObject* object)
{
  return get_kl_object_type(object) == KL_TYPE_STREAM;
}

INLINE bool is_kl_stream_equal (KLObject* left_object, KLObject* right_object)
{
  return left_object == right_object;
}

INLINE char read_byte (FILE* file)
{
  char c = (char)getc(file);

  if (c == (char) EOF) {
    if (ferror(file) != 0)
      throw_kl_exception("Failed to read a byte from stream");

    return  -1;
  }

  return c;
}

INLINE KLObject* read_kl_stream_byte (KLObject* stream_object)
{
  if (!is_kl_stream(stream_object))
    throw_kl_exception("Parameter should be a stream object");

  return create_kl_number_l(read_byte(get_kl_stream_file(stream_object)));
}

INLINE char* get_read_buffer (void)
{
  return read_buffer;
}

INLINE void set_read_buffer (char* buffer)
{
  read_buffer = buffer;
}

INLINE size_t get_read_buffer_allocation_size (void)
{
  return read_buffer_allocation_size;
}

INLINE void set_read_buffer_allocation_size (size_t size)
{
  read_buffer_allocation_size = size;
}

INLINE void initialize_read_buffer (void)
{
  read_buffer = malloc(get_read_buffer_allocation_size());
  read_buffer[get_read_buffer_allocation_size() - 1] = '\0';
}

INLINE int read_byte_with_buffer (FILE* file)
{
  return ((read_buffer_position > 0) ?
          read_buffer[--read_buffer_position] : getc(file));
}

INLINE void unread_byte_with_buffer (char c)
{
  if (read_buffer_position >= get_read_buffer_allocation_size() - 1) {
    size_t new_read_buffer_allocation_size =
      get_read_buffer_allocation_size() * 2;
    char* new_read_buffer = malloc(new_read_buffer_allocation_size);

    strcpy(new_read_buffer, get_read_buffer());
    set_read_buffer(new_read_buffer);
    set_read_buffer_allocation_size(new_read_buffer_allocation_size);
  }

  read_buffer[read_buffer_position++] = c;
}

INLINE void unread_bytes_with_buffer (char* lookahead_buffer)
{
  size_t lookahead_buffer_size = strlen(lookahead_buffer);

  for (long i = (long)lookahead_buffer_size - 1; i >= 0; --i)
    unread_byte_with_buffer(lookahead_buffer[i]);
}

INLINE char write_byte (FILE* file, char c)
{
  if (putc(c, file) != c)
    throw_kl_exception("Failed to write a byte to stream");

  return c;
}

INLINE KLObject* write_kl_stream_byte (KLObject* stream_object,
                                       KLObject* number_object)
{
  if (!is_kl_stream(stream_object))
    throw_kl_exception("Parameter is not a stream object");

  if (!is_kl_number(number_object))
    throw_kl_exception("Parameter is not a number object");

  char c = (char)get_kl_number_number_l(number_object);

  return create_kl_number_l(write_byte(get_kl_stream_file(stream_object), c));
}

INLINE char* read_file (FILE* file)
{
  if (fseek(file, 0, SEEK_END) != 0)
    throw_kl_exception("Failed to seek to the end position of the file");

  long string_size = ftell(file);

  if (string_size == -1L)
    throw_kl_exception("Failed to get string size of the file");

  if (fseek(file, 0, SEEK_SET) != 0)
    throw_kl_exception("Failed to seek to the start position of the file");

  char* string = malloc((size_t)string_size + 1);

  fread(string, (size_t)string_size, 1, file);
  string[string_size] = '\0';

  return string;
}

INLINE char* read_file_by_file_path (char* file_path)
{
  FILE* file = fopen(file_path, "r");

  if (is_null(file))
    throw_kl_exception("Failed to open file");

  char* string = read_file(file);

  if (fclose(file) != 0)
    throw_kl_exception("Failed to close file");

  return string;
}

INLINE char* read_file_by_file_path_from_home_path (char* file_path)
{
  char* absolute_file_path = concatenate_string(get_shen_c_home_path(),
                                                file_path);

  return read_file_by_file_path(absolute_file_path);
}

#endif
