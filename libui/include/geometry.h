/*
 * Copyright (c), Recep Aslantas. All rights reserved.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui__geometry__
#define __libui__geometry__

#ifdef __OBJC__
typedef struct CGPoint CGPoint;
typedef struct CGSize CGSize;
typedef struct CGRect CGRect;
#endif

namespace ui {

enum CoordSystem2d {
  kCoordSystem2dLeftTop = 0,
  kCoordSystem2dLeftBottom,
  kCoordSystem2dRightTop,
  kCoordSystem2dRightBottom
};
  
struct Point {
  double x;
  double y;

  Point(float _x=0.0, float _y=0.0)
    : x(_x), y(_y) { }

  bool operator==(const Point& p) const;
  bool operator==(const Point&& p) const;
  
#ifdef __OBJC__
  operator CGPoint  ();
#endif
};

struct Size {
  float width;
  float height;
  
#ifdef __OBJC__
  operator CGSize  ();
#endif
};

struct Vector {
  float dx;
  float dy;
};
  
struct Rect {
  Point origin;
  Size size;
  
#ifdef __OBJC__
  operator CGRect  ();
#endif
};

}

#endif /* defined(__libui__geometry__) */
