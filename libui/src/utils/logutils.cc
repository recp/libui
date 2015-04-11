/*
* Copyright (c), Recep Aslantas. All rights reserved.
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
  vfprintf(stderr, format, arglist);
  va_end(arglist);
}

void ui::debug::logt(CStringPtr tag, CStringPtr format, ...) {
  size_t format_size = sizeof(char) * (strlen(format) + 2);
  char * pretty_format = (char *)malloc(format_size);

  strcat(pretty_format, tag);
  strcat(pretty_format, ": ");
  strcat(pretty_format, format);

  va_list arglist;
  va_start(arglist, pretty_format);
  vfprintf(stderr, pretty_format, arglist);
  va_end(arglist);
  
  free(pretty_format);
}