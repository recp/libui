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

#include <stdio.h>

ui::Window::WindowImpl::WindowImpl(Window *_self, Rect rect, int style)
  : m_self(_self) {

  m_hInstance = GetModuleHandle(NULL);

  static const char * defaultClassName = "libui_def_wnd";
  memcpy(m_szWindowClass, defaultClassName, strlen(defaultClassName));

  WNDCLASSEX wcex = {0};
 //  memset(&wcex, '\0', sizeof(wcex));

  wcex.cbSize = sizeof(WNDCLASSEX);

  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = ::DefWindowProcW;
  // wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = m_hInstance;
  // wcex.hIcon = 
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
  // wcex.lpszMenuName = 
  wcex.lpszClassName = m_szWindowClass;
  // wcex.hIconSm =
  
  RegisterClassEx(&wcex);
  
  m_hWnd = CreateWindow(m_szWindowClass, 
                        m_szTitle, 
                        WS_OVERLAPPEDWINDOW,
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
