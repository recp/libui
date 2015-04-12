/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "win-window.h"
#include <functional>

#include <assert.h>
#include "../../utils/logutils.h"
#include "../../utils/utils.h"

#include <stdio.h>

DWORD translateWndStyleToWin32WS(int style);

ui::Window::WindowImpl::WindowImpl(Window *_self, Rect rect, int style)
  : m_self(_self) {

  m_hInstance = GetModuleHandle(NULL);

  static const char * defaultClassName = "libui_def_wnd";
  memcpy(m_szWindowClass, defaultClassName, strlen(defaultClassName));

  DWORD wndClassStyle = CS_HREDRAW | CS_VREDRAW;
  if (!(style & kWindowStyleCloseButton) && style != kWindowStyleDefault)
    wndClassStyle |= CS_NOCLOSE;

  WNDCLASSEX wcex;

  wcex.cbSize        = sizeof(WNDCLASSEX);
  wcex.style         = wndClassStyle;
  wcex.lpfnWndProc   = WindowImpl::WndProc;
  wcex.hInstance     = m_hInstance;
  wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
  wcex.lpszClassName = m_szWindowClass;
  wcex.cbClsExtra    = 0;
  wcex.cbWndExtra    = 0;
  wcex.hIcon         = 0;
  wcex.lpszMenuName  = 0;
  wcex.hIconSm       = 0;
  
  RegisterClassEx(&wcex);

#ifdef _DEBUG
  CMutStringPtr rectString = utils::stringFromRect(rect);
  debug::logt("win", "window rect: %s", rectString);
  free(rectString);
#endif

  DWORD windowMask = translateWndStyleToWin32WS(style);
  m_hWnd = CreateWindow(m_szWindowClass, 
                        m_szTitle, 
                        windowMask,
                        rect.origin.x, 
                        rect.origin.y, 
                        rect.size.width, 
                        rect.size.height,
                        NULL, 
                        NULL,
                        m_hInstance, 
                        NULL);

  if (!m_hWnd) {
    debug::logt("win:window", "couldnt create window, last err: %d", 
                GetLastError());
  }

  m_self = _self;
}

DWORD translateWndStyleToWin32WS(int style) {
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

LRESULT CALLBACK 
ui::Window::WindowImpl::WndProc(HWND hWnd, 
                                UINT message, 
                                WPARAM wParam, 
                                LPARAM lParam) {
  int wmId, wmEvent;
  PAINTSTRUCT ps;
  HDC hdc;

  switch (message) {
  case WM_COMMAND:
    wmId = LOWORD(wParam);
    wmEvent = HIWORD(wParam);
    switch (wmId) {
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
    }
    break;
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);

    EndPaint(hWnd, &ps);
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }

  return 0;
}

void ui::Window::WindowImpl::setTitle(const char *title) const {
  // TODO: MultiByteToWideChar can be used for non-ansi strings
  ::SetWindowTextA(m_hWnd, title);
}

void ui::Window::WindowImpl::show() const {
  ShowWindow(m_hWnd, 1);
  UpdateWindow(m_hWnd);
}

ui::View * ui::Window::WindowImpl::contentView() const {
  return m_contentView;
}

void ui::Window::WindowImpl::setContentView(ui::View *view) {

}

ui::Window::WindowImpl::~WindowImpl() {

}
