/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

 #include "../../include/ui-color.h"

#import <AppKit/NSColor.h>
#import <CoreGraphics/CGColorSpace.h>
#import <CoreGraphics/CGColor.h>

 ui::Color::operator NSColor * () {
   return [NSColor colorWithRed: this->red
                          green: this->green
                           blue: this->blue
                          alpha: this->alpha];
 }

 ui::Color::operator CGColorRef() {
   return CGColorCreateGenericRGB(this->red,
                                  this->green,
                                  this->blue,
                                  this->alpha);
 }
 
