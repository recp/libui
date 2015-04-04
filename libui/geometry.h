//
//  geometry.h
//  libui-test
//
//  Created by Recep ASLANTAS on 3/28/15.
//  Copyright (c) 2015 Recep ASLANTAS. All rights reserved.
//

#ifndef __libui__geometry__
#define __libui__geometry__

#ifdef __OBJC__
typedef struct CGPoint CGPoint;
typedef struct CGSize CGSize;
typedef struct CGRect CGRect;
#endif

namespace ui {

typedef enum {
  kCoordSystem2dLeftTop = 0,
  kCoordSystem2dLeftBottom,
  kCoordSystem2dRightTop,
  kCoordSystem2dRightBottom
} CoordSystem2d;
  
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
