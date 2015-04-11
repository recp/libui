/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../include/ui-color.h"

ui::Color::Color(float r, float g, float b, float a)
  : red(r), green(g), blue(b), alpha(a) {
    
};

ui::Color::Color(const Color& color)
  : red(color.red), 
    green(color.green), 
    blue(color.blue), 
    alpha(color.alpha) {

}

ui::Color::Color(const char * hexColor)
  : red(0.0f), green(0.0f), blue(0.0f), alpha(0.0f) {
    
}

const ui::Color&
ui::Color::operator = (const Color& color) {
  return color;
//  return Color(color.red, color.green, color.blue, color.alpha);
}

ui::Color ui::Color::clearColor()   { return ui::Color(0.0, 0.0, 0.0, 0.0); }
ui::Color ui::Color::blackColor()   { return ui::Color(0.0, 0.0, 0.0, 1.0); }
ui::Color ui::Color::whiteColor()   { return ui::Color(1.0, 1.0, 1.0, 1.0); }

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
