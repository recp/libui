/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../include/ui-window.h"
#include "../include/ui-geometry.h"

#ifdef __APPLE__
# include "cocoa/wnd/window.h"
#elif _WIN32
# include "win/wnd/win-window.h"
#endif

#include <functional>

ui::Window::Window(Rect rect, int style) {
  m_impl = new ui::Window::WindowImpl(this, rect, style);
}

ui::Window::Window(const Window& other)
  : m_impl(other.m_impl),
    ui::Object(other) {

  retain();
}

ui::Window::Window(Window&& other)
  : m_impl(std::move(other.m_impl)),
    ui::Object(std::move(other)) {

  other.m_impl = nullptr;
}

ui::Window&
ui::Window::operator=(const Window& other) {

  if (this != &other) {
    Object::operator=(other);

    delete m_impl;
    m_impl = other.m_impl;
    retain();
  }

  return *this;
}

ui::Window&
ui::Window::operator=(Window&& other) {

  if (this != &other) {
    Object::operator=(std::move(other));

    delete m_impl;
    m_impl = std::move(other.m_impl);
    other.m_impl = nullptr;
  }

  return *this;
}

void
ui::Window::show() const {
  m_impl->show();
}

void
ui::Window::hide() const {
  m_impl->hide();
}

void
ui::Window::center() {
  m_impl->center();
}

bool
ui::Window::isFullScreen() const {
  return m_impl->isFullScreen();
}

void
ui::Window::enterFullScreen() const {
  m_impl->enterFullScreen();
}

void
ui::Window::exitFullScreen() const {
  m_impl->exitFullScreen();
}

ui::CStringPtr
ui::Window::getTitle() const {
  return m_impl->getTitle();
}

void
ui::Window::setTitle(CStringPtr title) const {
  m_impl->setTitle(title);
}

ui::Rect
ui::Window::getFrame() const {
  return m_impl->getFrame();
}

void
ui::Window::setFrame(Rect rect) const {
  m_impl->setFrame(rect);
}

ui::View *
ui::Window::contentView() const {
  return m_impl->contentView();
}

void
ui::Window::setContentView(ui::View *view) const {
  m_impl->setContentView(view);
}

ui::WindowCloseBehavior 
ui::Window::getCloseBehavior() const {
  return m_impl->getCloseBehavior();
}
  
void 
ui::Window::setCloseBehavior(WindowCloseBehavior closeBehavior) const {
  m_impl->setCloseBehavior(closeBehavior);
}

ui::Window::~Window() {
  release();

  if (*m_refCount > 0)
    return;

  delete m_impl;
}
