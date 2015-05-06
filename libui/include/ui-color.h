/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui__color__
#define __libui__color__

#include "ui-base.h"

#ifdef __OBJC__
@class NSColor;
typedef struct CGColor * CGColorRef;
#endif

namespace ui {

struct _libui_export Color {
  float red;
  float green;
  float blue;
  float alpha;

  Color(const Color& color);
  Color(float r = .0f, float g = .0f, float b = .0f, float a = 1.0f);

  Color(const char * hexColor);

  Color& operator = (const Color& color);
  
#ifdef __OBJC__
  operator NSColor *  ();;
  operator CGColorRef ();
#endif
  
  static const Color blackColor();
  static const Color whiteColor();
  static const Color clearColor();
};

}

#endif /* defined(__libui__color__) */
