/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "logutils.h"
#include "../utils/utils.h"

#include <cstdio>
#include <varargs.h>

void ui::debug::log(CStringPtr format, ...) {
  va_list arglist;
  va_start(arglist, format);

  int formatted_len = vsnprintf(0, 0, format, arglist);
  size_t output_size = sizeof(char) * (strlen(format) + formatted_len + 1);
  char * log_output = (char *)calloc(output_size, 1);

  vsprintf(log_output, format, arglist);
  va_end(arglist);

#ifndef _WIN32
  fprintf(stderr, "%s", log_output);
#else
  OutputDebugStringA(log_output);
#endif

  free(log_output);
}

void ui::debug::logt(CStringPtr tag, CStringPtr format, ...) {
  va_list arglist;
  va_start(arglist, format);

  int formatted_len = vsnprintf(0, 0, format, arglist);
  size_t format_size = sizeof(char) * (strlen(tag) + strlen(format) + 3);
  size_t output_size = sizeof(char) * formatted_len + format_size;

  char * log_output = (char *)calloc(output_size, 1);
  char * pretty_format = (char *)calloc(format_size, 1);

  strcat(pretty_format, tag);
  strcat(pretty_format, ": ");
  strcat(pretty_format, format);

  vsprintf(log_output, pretty_format, arglist);
  va_end(arglist);
  
#ifndef _WIN32
  fprintf(stderr, "%s", log_output);
#else
  OutputDebugStringA(log_output);
#endif

  free(pretty_format);
  free(log_output);
}