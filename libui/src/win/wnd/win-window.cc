/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "win-window.h"
#include "../view/win-view.h"

#include "../../utils/logutils.h"
#include "../../utils/utils.h"
#include "../win-utils.h"

ui::Window::WindowImpl::WindowImpl(Window *_self, Rect rect, int style)
  : m_self(_self) {

  Rect contentViewRect({{0, 0}, {rect.size.width, rect.size.height}});
  m_contentView = new View(contentViewRect);
  m_contentView->setBackgroundColor(Color::whiteColor());
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

  DWORD windowMask = ui::translateWndStyleToWin32WS(style);
  m_hWnd = CreateWindow(m_szWindowClass, 
                        m_szTitle, 
                        windowMask,
                        (int)rect.origin.x, 
                        (int)rect.origin.y, 
                        (int)rect.size.width, 
                        (int)rect.size.height,
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

void 
ui::Window::WindowImpl::setTitle(const char *title) {
  // TODO: MultiByteToWideChar can be used for non-ansi strings
  ::SetWindowTextA(m_hWnd, title);
}

ui::Rect 
ui::Window::WindowImpl::getFrame() const {
  RECT rc;
  GetWindowRect(m_hWnd, &rc);

  return Rect::fromWin32RECT(rc);
}

void
ui::Window::WindowImpl::setFrame(Rect frame) {

  SetWindowPos(m_hWnd, 
               NULL, 
               (int)frame.origin.x,
               (int)frame.origin.y,
               (int)frame.size.width,
               (int)frame.size.height,
               SWP_SHOWWINDOW | SWP_FRAMECHANGED);
}

void 
ui::Window::WindowImpl::show() const {
  ShowWindow(m_hWnd, 1);
  UpdateWindow(m_hWnd);
}

ui::View * 
ui::Window::WindowImpl::contentView() {
  if (m_contentView && !m_contentView->m_impl->m_wnd) {
    this->setContentView(m_contentView);
  }

  return m_contentView;
}

void 
ui::Window::WindowImpl::setContentView(ui::View * view) {
  // remove prev contentview
  if (m_contentView) {
    SetParent(m_contentView->m_impl->m_hWnd, NULL);
    InvalidateRect(m_hWnd, NULL, TRUE);
    UpdateWindow(m_hWnd);
  }

  SetParent(view->m_impl->m_hWnd, m_hWnd);

  ShowWindow(view->m_impl->m_hWnd, 1);
  UpdateWindow(view->m_impl->m_hWnd);

  view->m_impl->m_wnd = const_cast<Window *>(m_self);
}

ui::Window::WindowImpl::~WindowImpl() {
  DestroyWindow(m_hWnd);
  delete m_contentView;
}
