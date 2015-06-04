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

  RECT wndExtraSizeRect;
  AdjustWindowRectEx(&wndExtraSizeRect, windowMask, FALSE, wcex.style);

  int extraWndHeight = wndExtraSizeRect.bottom - wndExtraSizeRect.top;
  int extraWndWidth = wndExtraSizeRect.right - wndExtraSizeRect.left;

  m_hWnd = CreateWindow(m_szWindowClass, 
                        m_szTitle, 
                        windowMask,
                        (int)rect.origin.x, 
                        (int)rect.origin.y, 
                        (int)rect.size.width + extraWndWidth, 
                        (int)rect.size.height + extraWndHeight,
                        NULL, 
                        NULL,
                        m_hInstance, 
                        this);

  if (!m_hWnd) {
    debug::logt("win:window", "couldnt create window, last err: %d", 
                GetLastError());
  }
    
  m_self = _self;
}

LRESULT CALLBACK 
ui::Window::WindowImpl::WndProc(HWND hWnd, 
                                UINT uMsg, 
                                WPARAM wParam, 
                                LPARAM lParam) {
  int wmId, wmEvent;
  PAINTSTRUCT ps;
  HDC hdc;

  WindowImpl * windowImpl = NULL;
  if (uMsg == WM_CREATE) {
    CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT *>(lParam);
    windowImpl = reinterpret_cast<WindowImpl *>(pCreate->lpCreateParams);
    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)windowImpl);
  } else {
    LONG_PTR ptr = GetWindowLongPtr(hWnd, GWLP_USERDATA);
    windowImpl = reinterpret_cast<WindowImpl *>(ptr);
  }

  switch (uMsg) {
  case WM_CREATE:

    break;
  case WM_COMMAND:
    wmId = LOWORD(wParam);
    wmEvent = HIWORD(wParam);
    //switch (wmId) {
    //default:
    //  return DefWindowProc(hWnd, message, wParam, lParam);
    //}
    break;
  case WM_SIZE: {
    Rect wndBounds = windowImpl->getFrame();
    wndBounds.origin = {0};
    windowImpl->contentView()->setFrame(wndBounds);
    break;
  }
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);

    EndPaint(hWnd, &ps);
    break;
  case WM_DESTROY:
    switch (windowImpl->getCloseBehavior()) {
    case kWindowCloseBehavior_AppShouldExit:
      PostQuitMessage(0);
      break;
    default:
      break;
    }
    break;
  default:
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
  }

  return 0;
}

ui::CStringPtr 
ui::Window::WindowImpl::getTitle() const {
  int titleMaxLen = 512;
  WCHAR _wTitle[512];
  GetWindowText(m_hWnd, _wTitle, titleMaxLen);

  if (!_wTitle)
    return nullptr;

  char title[512];
  wcstombs(title, _wTitle, titleMaxLen);

  return title;
}

void 
ui::Window::WindowImpl::setTitle(CStringPtr title) {
  int titleMaxLen = 512;
  WCHAR _wTitle[512];
  mbstowcs(_wTitle, title, titleMaxLen);
  SetWindowText(m_hWnd, _wTitle);
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
ui::Window::WindowImpl::show() {
  GetWindowPlacement(m_hWnd, &m_prevPlace); 
  ShowWindow(m_hWnd, 1);
  UpdateWindow(m_hWnd);
}

void 
ui::Window::WindowImpl::hide() {
  ShowWindow(m_hWnd, 0);
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
ui::Window::WindowImpl::center() {
  int screenWidth = GetSystemMetrics(SM_CXSCREEN);
  int screenHeight = GetSystemMetrics(SM_CYSCREEN);
  
  Rect frm = this->getFrame();
  int offsetX = (int)((screenWidth - frm.size.width) / 2.0);
  int offsetY = (int)((screenHeight - frm.size.height) / 2.0);
  MoveWindow(m_hWnd,
             offsetX,
             offsetY, 
             (int)frm.size.width,
             (int)frm.size.height, 
             FALSE);
}

bool
ui::Window::WindowImpl::isFullScreen() const {
  return m_isFullScreen;
}

void
ui::Window::WindowImpl::enterFullScreen() {
  GetWindowPlacement(m_hWnd, &m_prevPlace);
  DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);

  if (dwStyle & WS_OVERLAPPEDWINDOW) {
    HMONITOR hMonitor = MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTOPRIMARY);
    MONITORINFO mi;
    mi.cbSize = sizeof(mi);
    if (GetMonitorInfo(hMonitor, &mi)) {
      SetWindowLong(m_hWnd,
                    GWL_STYLE,
                    dwStyle & ~WS_OVERLAPPEDWINDOW);
      SetWindowPos(m_hWnd,
                   HWND_TOP,
                   mi.rcMonitor.left, 
                   mi.rcMonitor.top,
                   mi.rcMonitor.right - mi.rcMonitor.left,
                   mi.rcMonitor.bottom - mi.rcMonitor.top,
                   SWP_NOOWNERZORDER | SWP_FRAMECHANGED);

      m_isFullScreen = true;
    }
  }
}

void
ui::Window::WindowImpl::exitFullScreen() {
  DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);

  // TODO:
  // WS_OVERLAPPEDWINDOW shouldnt add directly to wnd style because the window
  // may not contain caption, border, menu...
  SetWindowLong(m_hWnd, 
                GWL_STYLE,
                dwStyle | WS_OVERLAPPEDWINDOW);
  SetWindowPlacement(m_hWnd, &m_prevPlace);
  SetWindowPos(m_hWnd, 
               NULL, 
               0, 0, 0, 0,
               SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
               SWP_NOOWNERZORDER | SWP_FRAMECHANGED);

  m_isFullScreen = false;
}

void 
ui::Window::WindowImpl::setContentView(ui::View * view) {
  // remove prev contentview
  if (m_contentView) {
    SetParent(m_contentView->m_impl->m_hWnd, NULL);
    InvalidateRect(m_hWnd, NULL, TRUE);
    UpdateWindow(m_hWnd);
  }

  Rect wndBounds = this->getFrame();
  wndBounds.origin = {0};
  view->setFrame(wndBounds);
  
  m_contentView = view;
  SetParent(view->m_impl->m_hWnd, m_hWnd);

  ShowWindow(view->m_impl->m_hWnd, 1);
  UpdateWindow(view->m_impl->m_hWnd);

  view->m_impl->m_wnd = const_cast<Window *>(m_self);
}

ui::WindowCloseBehavior 
ui::Window::WindowImpl::getCloseBehavior() const {
  return m_closeBehavior;
}
  
void 
ui::Window::WindowImpl::setCloseBehavior(WindowCloseBehavior closeBehavior) {
  m_closeBehavior = closeBehavior;
}

ui::Window::WindowImpl::~WindowImpl() {
  DestroyWindow(m_hWnd);
  delete m_contentView;
}
