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

ui::View::View(const View& other)
  : m_impl(other.m_impl),
    ui::Object(other) {

  retain();
}

ui::View::View(View&& other)
  : m_impl(std::move(other.m_impl)),
    ui::Object(std::move(other)) {

  other.m_impl = nullptr;
}

ui::View&
ui::View::operator=(const View& other) {

  if (this != &other) {
    Object::operator=(other);

    delete m_impl;
    m_impl = other.m_impl;
    retain();
  }

  return *this;
}

ui::View&
ui::View::operator=(View&& other) {

  if (this != &other) {
    Object::operator=(std::move(other));

    delete m_impl;
    m_impl = std::move(other.m_impl);
    other.m_impl = nullptr;
  }

  return *this;
}

bool
ui::View::operator==(const View& other) const {
  // compare address of impl for now
  return m_impl == other.m_impl;
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

bool 
ui::View::isInputEnabled() const {
  return m_impl->isInputEnabled();
}

void 
ui::View::setInputEnabled(bool enabled) const {
  m_impl->setInputEnabled(enabled);
}

const ui::View * 
ui::View::superview() const {
  return m_impl->superview();
}

const ui::Window *
ui::View::window() const {
  return m_impl->window();
}

std::vector<ui::View> *
ui::View::subviews() const {
  return m_impl->subviews();
}

void
ui::View::addSubview(const View& subview) const {
  m_impl->addSubview(subview);
}

void
ui::View::addSubview(View&& subview) const {
  m_impl->addSubview(std::move(subview));
}

void
ui::View::removeFromSuperview() const {
  m_impl->removeFromSuperview();
}

void 
ui::View::bringSubviewToFront(View * view) const {
  m_impl->bringSubviewToFront(view);
}

void 
ui::View::sendSubviewToBack(View * view) const {
  m_impl->sendSubviewToBack(view);
}

void 
ui::View::setHidden(bool isHidden) const {
  m_impl->setHidden(isHidden);
}
  
bool 
ui::View::isHidden() const {
  return m_impl->isHidden();
}

void 
ui::View::forceRedraw() const {
  m_impl->forceRedraw();
}

ui::View::~View() {
  release();

  if (*m_refCount > 0)
    return;

  delete m_impl;
}
