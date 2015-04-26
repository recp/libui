/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "win-view.h"


ui::View::ViewImpl::ViewImpl(View * _self, Rect rect) : m_self(_self) {
  m_subviews = new std::vector<View *>();
  m_frame = rect;
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
ui::View::ViewImpl::setFrame(Rect frame) const {

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
