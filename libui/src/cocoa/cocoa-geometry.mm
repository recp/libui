/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../../include/ui-geometry.h"

#include <CoreGraphics/CGGeometry.h>

ui::Rect::operator CGRect() {
  return CGRectMake(this->origin.x,
                    this->origin.y,
                    this->size.width,
                    this->size.height);
}

ui::Size::operator CGSize() {
  return CGSizeMake(this->width, this->height);
}

ui::Point::operator CGPoint() {
  return CGPointMake(this->x, this->y);
}
