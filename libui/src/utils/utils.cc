/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "utils.h"

#include <stdlib.h>
#include <stdio.h>

ui::CMutStringPtr ui::utils::stringFromRect(const Rect& rect) {
  int maxRectStrLen = 50;
  char * rectstr = (char *)calloc(sizeof(char) * maxRectStrLen, 1);
  sprintf(rectstr, "{{%.3f, %.3f}, {%.3f, %.3f}}",
          rect.origin.x,
          rect.origin.y,
          rect.size.width,
          rect.size.height);
  return rectstr;
}