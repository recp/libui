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
#elif defined(_WIN32) || defined(WIN32)
typedef unsigned long COLORREF;
#endif

namespace ui {

struct _libui_export Color {
  double red;
  double green;
  double blue;
  double alpha;

  Color(const Color& color);
  Color(double r = .0f,
        double g = .0f,
        double b = .0f,
        double a = 1.f);

  Color(const char * hexColor);

  Color& operator = (const Color& color);
  
#ifdef __OBJC__
  operator NSColor *  ();;
  operator CGColorRef ();
#elif defined(_WIN32) || defined(WIN32)
  operator COLORREF ();
#endif
  
  static const Color blackColor();
  static const Color whiteColor();
  static const Color clearColor();
};

}

#endif /* defined(__libui__color__) */
