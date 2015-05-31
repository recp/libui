/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../config.h"
#include "../../include/ui-geometry.h"

ui::Rect 
ui::Rect::fromWin32RECT(RECT rc) {
  
  Rect uiRect;
  uiRect.origin.x = rc.left;
  uiRect.origin.y = rc.top;
  uiRect.size.width = rc.right - rc.left;
  uiRect.size.height = rc.bottom - rc.top;

  return uiRect;
}

ui::Rect::operator RECT () {

  RECT rc;
  rc.left   = origin.x;
  rc.top    = origin.y;
  rc.right  = origin.x + size.width;
  rc.bottom = origin.y + size.height;

  return rc;
}