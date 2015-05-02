/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "win-utils.h"

DWORD 
ui::translateWndStyleToWin32WS(int style) {
  DWORD winWS = 0L;
  if (style == ui::kWindowStyleDefault) {
    // it is same with WS_OVERLAPPEDWINDOW
    winWS = (WS_OVERLAPPED
           | WS_CAPTION
           | WS_SYSMENU
           | WS_THICKFRAME
           | WS_MINIMIZEBOX
           | WS_MAXIMIZEBOX);

    return winWS;
  }

  BOOL borderless = false;

  if (style & ui::kWindowStyleBorderless) {
    borderless = true;
  } else {
    winWS |= (WS_OVERLAPPED
             | WS_CAPTION
             | WS_SYSMENU);
  }

  if ((style & ui::kWindowStyleTitled) || !borderless)
    winWS |= WS_CAPTION;

  if (style & ui::kWindowStyleFullscreen)
    winWS |= WS_MAXIMIZE;

  //if (style & ui::kWindowStyleCloseButton)
  // winWS |= ? See window class style

  if (style & ui::kWindowStyleMaximizeButton)
    winWS |= WS_MAXIMIZEBOX;

  if (style & ui::kWindowStyleMinimizeButton)
    winWS |= WS_MINIMIZEBOX;

  return winWS;
}
