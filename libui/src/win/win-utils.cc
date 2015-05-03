/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "win-utils.h"
#include "../utils/logutils.h"
#include "../utils/utils.h"

namespace ui {

HWND def_fk_wnd = NULL;

} // namespace ui

HWND 
ui::defaultFakeWindow() {
  if (def_fk_wnd)
    return def_fk_wnd;

  HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);

  WNDCLASSEX wcex;

  wcex.cbSize        = sizeof(WNDCLASSEX);
  wcex.style         = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc   = ::DefWindowProc;
  wcex.hInstance     = hInstance;
  wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
  wcex.lpszClassName = L"libui_def_fk_wnd";
  wcex.cbClsExtra    = 0;
  wcex.cbWndExtra    = 0;
  wcex.hIcon         = 0;
  wcex.lpszMenuName  = 0;
  wcex.hIconSm       = 0;
  
  RegisterClassEx(&wcex);
  
  def_fk_wnd = CreateWindow(L"libui_def_fk_wnd", 
                            L"", 
                            WS_OVERLAPPED,
                            0, 
                            0, 
                            0, 
                            0,
                            NULL, 
                            NULL,
                            hInstance, 
                            NULL);

  if (!def_fk_wnd) {
    debug::logt("win:window", "couldnt create window, last err: %d", 
                GetLastError());
  }

  return def_fk_wnd;
}

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
