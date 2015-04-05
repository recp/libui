/*
 * Copyright (c), Recep Aslantas. All rights reserved.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "win-window.h"

ui::Window::WindowImpl::WindowImpl(Window *_self, Rect rect, int style) : m_self(_self) {

  m_self = _self;
}

void ui::Window::WindowImpl::setTitle(const char *title) const {

}

void ui::Window::WindowImpl::show() const {
 
}

//ui::View * wnd::Window::WindowImpl::contentView() const {
//  return m_contentView;
//}
//
//void wnd::Window::WindowImpl::setContentView(ui::View *view) {
//
//}

ui::Window::WindowImpl::~WindowImpl() {
  m_wnd = nullptr;
}
