/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../include/ui-color.h"

ui::Color::Color(double r, double g, double b, double a)
  : red(r), green(g), blue(b), alpha(a) {

  float colorMaxVal = 1.0f;

  if (red > colorMaxVal)
    red = colorMaxVal;
  else if (red < 0)
    red = 0;

  if (green > colorMaxVal)
    green = colorMaxVal;
  else if (green < 0)
    green = 0;

  if (blue > colorMaxVal)
    blue = colorMaxVal;
  else if (blue < 0)
    blue = 0;
};

ui::Color::Color(const Color& other)
  : red(other.red),
    green(other.green),
    blue(other.blue),
    alpha(other.alpha) {
}

ui::Color::Color(const char * hexColor)
  : red(0.0f),
    green(0.0f),
    blue(0.0f),
    alpha(0.0f) {
}

ui::Color&
ui::Color::operator=(const Color& other) {
  if (this != &other) {
    red   = other.red;
    green = other.green;
    blue  = other.blue;
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

