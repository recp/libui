/*
 * Copyright (c), Recep Aslantas. All rights reserved.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "win-window.h"

ui::Window::WindowImpl::WindowImpl(Window *_self, Rect rect, int style)
  : m_self(_self) {

  WNDCLASSEX wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);

  wcex.style = CS_HREDRAW | CS_VREDRAW;
  // wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = m_hInstance;
  // wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT3));
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  // wcex.lpszMenuName = MAKEINTRESOURCE(IDC_WIN32PROJECT3);
  // wcex.lpszClassName = szWindowClass;
  // wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

  m_className = RegisterClassEx(&wcex);
  
  m_self = _self;
}

void ui::Window::WindowImpl::setTitle(const char *title) const {

}

void ui::Window::WindowImpl::show() const {
 
}

ui::View * ui::Window::WindowImpl::contentView() const {
  return m_contentView;
}

void ui::Window::WindowImpl::setContentView(ui::View *view) {

}

ui::Window::WindowImpl::~WindowImpl() {
  m_wnd = nullptr;
}
