/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../config.h"
#include "../../include/ui-color.h"

ui::Color::operator COLORREF () {
  return RGB(this->red,
             this->green,
             this->blue);
}
