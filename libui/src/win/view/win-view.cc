/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "win-view.h"

#include "../../utils/logutils.h"
#include "../../utils/utils.h"
#include "../win-utils.h"

ui::View::ViewImpl::ViewImpl(View * _self, Rect rect) 
  : m_self(_self) {

  m_subviews = new std::vector<View *>;
  m_frame = rect;

  m_hInstance = GetModuleHandle(NULL);

  static const char * defaultClassName = "libui_def_view_wnd";
  memcpy(m_szWindowClass, defaultClassName, strlen(defaultClassName));

  DWORD wndClassStyle = CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE;

  WNDCLASSEX wcex;

  wcex.cbSize        = sizeof(WNDCLASSEX);
  wcex.style         = wndClassStyle;
  wcex.lpfnWndProc   = ViewImpl::WndProc;
  wcex.hInstance     = m_hInstance;
  wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_GRAYTEXT);
  wcex.lpszClassName = m_szWindowClass;
  wcex.cbClsExtra    = 0;
  wcex.cbWndExtra    = 0;
  wcex.hIcon         = 0;
  wcex.lpszMenuName  = 0;
  wcex.hIconSm       = 0;
  
  RegisterClassEx(&wcex);

#ifdef _DEBUG
  CMutStringPtr rectString = utils::stringFromRect(rect);
  debug::logt("win", "view rect: %s", rectString);
  free(rectString);
#endif

  HWND hParentWnd = ui::defaultFakeWindow();
  DWORD windowMask = WS_CHILD;
  m_hWnd = CreateWindow(m_szWindowClass, 
                        NULL, 
                        windowMask,
                        rect.origin.x, 
                        rect.origin.y, 
                        rect.size.width, 
                        rect.size.height,
                        hParentWnd, 
                        NULL,
                        m_hInstance, 
                        NULL);

  if (!m_hWnd) {
    debug::logt("win:view", "couldnt create window, last err: %d", 
                GetLastError());
  }
}

LRESULT CALLBACK 
ui::View::ViewImpl::WndProc(HWND hWnd, 
                            UINT message, 
                            WPARAM wParam, 
                            LPARAM lParam) {
  int wmId, wmEvent;
  PAINTSTRUCT ps;
  HDC hdc;

  switch (message) {
  case WM_CREATE:
    break;
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

ui::Color 
ui::View::ViewImpl::backgroundColor() const {
  return m_bgcolor;
}

void 
ui::View::ViewImpl::setBackgroundColor(Color color) const {

}

ui::Rect 
ui::View::ViewImpl::getFrame() const {
  return m_frame;
}

void 
ui::View::ViewImpl::setFrame(Rect frame) {
  m_frame = frame;

  SetWindowPos(m_hWnd, 
               NULL, 
               frame.origin.x,
               frame.origin.y,
               frame.size.width,
               frame.size.height,
               SWP_SHOWWINDOW | SWP_FRAMECHANGED);
}

void 
ui::View::ViewImpl::addSubview(View *subview) const {
 
}

void 
ui::View::ViewImpl::removeFromSuperview() const {

}

const ui::Window * 
ui::View::ViewImpl::window() const {
  return m_wnd;
}

ui::View::ViewImpl::~ViewImpl() {
  m_subviews->clear();
  delete m_subviews;
  m_view = nullptr;
}
