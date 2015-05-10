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

#include <algorithm>

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
                        this);

  if (!m_hWnd) {
    debug::logt("win:view", "couldnt create window, last err: %d", 
                GetLastError());
  }
}

LRESULT CALLBACK 
ui::View::ViewImpl::WndProc(HWND hWnd, 
                            UINT uMsg, 
                            WPARAM wParam, 
                            LPARAM lParam) {
  int wmId, wmEvent;
  PAINTSTRUCT ps;
  HDC hdc;

  ViewImpl * viewImpl = NULL;
  if (uMsg == WM_CREATE) {
    CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT *>(lParam);
    viewImpl = reinterpret_cast<ViewImpl *>(pCreate->lpCreateParams);
    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)viewImpl);
  } else {
    LONG_PTR ptr = GetWindowLongPtr(hWnd, GWLP_USERDATA);
    viewImpl = reinterpret_cast<ViewImpl *>(ptr);
  }

  switch (uMsg) {
  case WM_CREATE:
    break;
  case WM_COMMAND:
    wmId = LOWORD(wParam);
    wmEvent = HIWORD(wParam);
    switch (wmId) {
    default:
      return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    break;
  case WM_PAINT: {
    hdc = BeginPaint(hWnd, &ps);
   
    Color bgColor = viewImpl->backgroundColor();
    HBRUSH brush = CreateSolidBrush(bgColor);

    FillRect(hdc, &ps.rcPaint, brush);
    DeleteObject(brush);

    EndPaint(hWnd, &ps);
    break;
  }
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
  }

  return 0;
}

ui::Color 
ui::View::ViewImpl::backgroundColor() const {
  return m_bgcolor;
}

void 
ui::View::ViewImpl::setBackgroundColor(Color color) {
  m_bgcolor = color;

  InvalidateRect(m_hWnd, NULL, TRUE);
  UpdateWindow(m_hWnd);
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
  subview->m_impl->m_superview = const_cast<View *>(this->m_self);

  SetParent(subview->m_impl->m_hWnd, m_hWnd);
  ShowWindow(subview->m_impl->m_hWnd, SW_SHOWNORMAL);
  UpdateWindow(subview->m_impl->m_hWnd);

  m_subviews->push_back(subview);
}

void 
ui::View::ViewImpl::removeFromSuperview() const {
  ShowWindow(m_hWnd, SW_HIDE);
  View * _self = const_cast<View * >(m_self);

  std::vector<View *>::iterator it =
    std::find(m_superview->m_impl->m_subviews->begin(),
              m_superview->m_impl->m_subviews->end(), 
              _self);

  if (it != m_superview->m_impl->m_subviews->end()) {
    m_superview->m_impl->m_subviews->erase(it);
  }
};

const ui::Window * 
ui::View::ViewImpl::window() const {
  return m_wnd;
}

ui::View::ViewImpl::~ViewImpl() {
  m_subviews->clear();
  delete m_subviews;
  m_view = nullptr;
}
