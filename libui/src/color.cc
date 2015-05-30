/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../include/ui-color.h"

ui::Color::Color(double r, double g, double b, double a)
  : red(r), green(g), blue(b), alpha(a) {
    
};

ui::Color::Color(const Color& color)
  : red(color.red), 
    green(color.green), 
    blue(color.blue), 
    alpha(color.alpha) {
   
  float colorMaxVal = 1.0f;

  if (this->red > colorMaxVal) 
    this->red = colorMaxVal;
  else if (this->red < 0) 
    this->red = 0;

  if (this->green > colorMaxVal) 
    this->green = colorMaxVal;
  else if (this->green < 0) 
    this->green = 0;

  if (this->blue > colorMaxVal) 
    this->blue = colorMaxVal;
  else if (this->blue < 0) 
    this->blue = 0;
}

ui::Color::Color(const char * hexColor)
  : red(0.0f), green(0.0f), blue(0.0f), alpha(0.0f) {
    
}

ui::Color&
ui::Color::operator = (const Color& color) {
  if (this != &color) {
    this->red = color.red;
    this->green = color.green;
    this->blue = color.blue;
  }

  return *this;
}

const ui::Color 
ui::Color::clearColor() { 
  return ui::Color(0.0, 0.0, 0.0, 0.0); 
}

const ui::Color 
ui::Color::blackColor() { 
  return ui::Color(0.0, 0.0, 0.0, 1.0); 
}

const ui::Color 
ui::Color::whiteColor() { 
  return ui::Color(1.0, 1.0, 1.0, 1.0); 
}

//CG_EXTERN CGColorRef CGColorCreate(CGColorSpaceRef space,
//                                   const CGFloat components[]) CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);
//
///* Create a color in the "Generic" gray color space. */
//
//CG_EXTERN CGColorRef CGColorCreateGenericGray(CGFloat gray, CGFloat alpha)
//CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);
//
///* Create a color in the "Generic" RGB color space. */
//
//CG_EXTERN CGColorRef CGColorCreateGenericRGB(CGFloat red, CGFloat green,
//                                             CGFloat blue, CGFloat alpha) CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);
