//
//  view.cpp
//  libui-test
//
//  Created by Recep ASLANTAS on 3/23/15.
//  Copyright (c) 2015 Recep ASLANTAS. All rights reserved.
//

#include "view.h"
#include "cocoa/view/view.h"
#include <functional>

ui::View::View(Rect rect) {
  m_impl = new ViewImpl(this, rect);
}

ui::Color ui::View::backgroundColor() const {
  return m_impl->backgroundColor();
}

void ui::View::setBackgroundColor(Color color) const {
  m_impl->setBackgroundColor(color);
}

ui::Rect ui::View::getFrame() const {
  return m_impl->getFrame();
}

void ui::View::setFrame(Rect frame) const {
  m_impl->setFrame(frame);
}

void ui::View::View::addSubview(View *subview) const {
  m_impl->addSubview(subview);
}

void ui::View::View::removeFromSuperview() const {
  m_impl->removeFromSuperview();
}

const ui::Window * ui::View::window() const {
  return m_impl->window();
}

ui::View::~View() {
  delete m_impl;
}