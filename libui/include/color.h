/*
 * Copyright (c), Recep Aslantas. All rights reserved.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui__color__
#define __libui__color__

#include "types.h"

#ifdef __OBJC__
@class NSColor;
typedef struct CGColor * CGColorRef;
#endif

namespace ui {

struct _libui_export Color {
  const float red;
  const float green;
  const float blue;
  const float alpha;

  Color(const Color& color);
  Color(float r = .0f, float g = .0f, float b = .0f, float a = 1.0f);

  Color(const char * hexColor);

  const Color& operator = (const Color& color);
  
#ifdef __OBJC__
  operator NSColor *  ();;
  operator CGColorRef ();
#endif
  
  static Color blackColor();
  static Color whiteColor();
  static Color clearColor();
};

}

#endif /* defined(__libui__color__) */
