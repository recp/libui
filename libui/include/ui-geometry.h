/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui__geometry__
#define __libui__geometry__

#include "ui-base.h"

#ifdef __OBJC__
typedef struct CGPoint CGPoint;
typedef struct CGSize CGSize;
typedef struct CGRect CGRect;
#elif defined(_WIN32) || defined(WIN32)
typedef struct tagRECT RECT;
#endif

namespace ui {

enum CoordSystem2d {
  kCoordSystem2dLeftTop = 0,
  kCoordSystem2dLeftBottom,
  kCoordSystem2dRightTop,
  kCoordSystem2dRightBottom
};

struct _libui_export Point {
  double x;
  double y;

  Point(double _x=0.0, double _y=0.0)
    : x(_x), y(_y) { }

  bool operator==(const Point& p) const;
  bool operator==(const Point&& p) const;

#ifdef __OBJC__
  operator CGPoint  ();
#endif
};

struct _libui_export Size {
  double width;
  double height;

  Size(double _w=0.0, double _h=0.0)
    : width(_w), height(_h) { }

#ifdef __OBJC__
  operator CGSize  ();
#endif
};

struct _libui_export Vector {
  double dx;
  double dy;
};

struct _libui_export Rect {
  Point origin;
  Size size;

#ifdef __OBJC__
  operator CGRect  ();
#elif defined(_WIN32) || defined(WIN32)
  static Rect fromWin32RECT(RECT rc);
  operator RECT ();
#endif
};

}

#endif /* defined(__libui__geometry__) */
