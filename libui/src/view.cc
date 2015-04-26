/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../include/ui-view.h"

#ifdef __APPLE__
# include "cocoa/view/view.h"
#elif _WIN32
# include "win/view/win-view.h"
#endif

#include <functional>

ui::View::View(Rect rect) {
  m_impl = new ViewImpl(this, rect);
}

ui::Color
ui::View::backgroundColor() const {
  return m_impl->backgroundColor();
}

void
ui::View::setBackgroundColor(Color color) const {
  m_impl->setBackgroundColor(color);
}

ui::Rect
ui::View::getFrame() const {
  return m_impl->getFrame();
}

void
ui::View::setFrame(Rect frame) const {
  m_impl->setFrame(frame);
}

void
ui::View::addSubview(View *subview) const {
  m_impl->addSubview(subview);
}

void
ui::View::removeFromSuperview() const {
  m_impl->removeFromSuperview();
}

const ui::Window *
ui::View::window() const {
  return m_impl->window();
}

ui::View::~View() {
  delete m_impl;
}