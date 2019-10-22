#include "system.h"

#include "defs.h"

clock_t start_clock;

extern void initialize_start_clock (void);

static inline clock_t get_start_clock (void)
{
  return start_clock;
}

static inline long get_unix_time (void)
{
  return (long)time(NULL);
}

static inline KLObject* get_kl_number_unix_time (void)
{
  KLObject* number_object = create_kl_number_l(get_unix_time());

  return number_object;
}

static inline double get_run_time (void)
{
  return (double)(clock() - get_start_clock()) / CLOCKS_PER_SEC;
}

static inline KLObject* get_kl_number_run_time (void)
{
  KLObject* number_object = create_kl_number_d(get_run_time());

  return number_object;
}

KLObject* get_kl_number_time (KLObject* symbol_object)
{
  if (!is_kl_symbol(symbol_object))
    throw_kl_exception("Parameter should be a symbol");

  if (symbol_object == get_unix_symbol_object())
    return get_kl_number_unix_time();
  else if (symbol_object == get_run_symbol_object())
    return get_kl_number_run_time();

  throw_kl_exception("Parameter should be a symbol unix or run");

  return NULL;
}
