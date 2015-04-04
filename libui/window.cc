//
//  window.cpp
//  libui-test
//
//  Created by Recep ASLANTAS on 3/23/15.
//  Copyright (c) 2015 Recep ASLANTAS. All rights reserved.
//

#include "window.h"
#include "geometry.h"
#include <functional>

#include "cocoa/wnd/window.h"

namespace wnd = ui;

wnd::Window::Window(Rect rect, int style) {
  m_impl = new wnd::Window::WindowImpl(this, rect, style);
}

void wnd::Window::show() const {
  m_impl->show();
}

void wnd::Window::setTitle(const char *title) const {
  m_impl->setTitle(title);
}

ui::View * wnd::Window::contentView() const {
  return m_impl->contentView();
}

void wnd::Window::setContentView(ui::View *view)  const {
  m_impl->setContentView(view);
}

wnd::Window::~Window() {
  delete m_impl;
}