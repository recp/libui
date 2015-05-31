/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../config.h"
#include "../../include/ui-color.h"
#include <math.h>

ui::Color::operator COLORREF () {

  int colorMaxVal = 255;

  int R = (int)round(this->red * colorMaxVal);
  int G = (int)round(this->green * colorMaxVal);
  int B = (int)round(this->blue * colorMaxVal);

  return RGB(R, G, B);
}
