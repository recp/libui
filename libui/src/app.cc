/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../include/ui-app.h"

#ifdef __APPLE__
# include "cocoa/app.h"
# include "cocoa/wnd/window.h"
#elif _WIN32
# include "win/win-app.h"
#endif

#include <stdlib.h>

ui::App::App() {
  m_impl = new AppImpl(this);
}

ui::App::App(const App& other) {
  m_refCount = other.m_refCount;
  m_impl     = other.m_impl;

  retain();
}

ui::App::App(App&& other)
  : m_impl(nullptr) {

  m_refCount = other.m_refCount;
  m_impl     = other.m_impl;

  other.m_refCount = nullptr;
  other.m_impl     = nullptr;
}

ui::App&
ui::App::App::operator=(const App& other) {

  if (this != &other) {
    m_refCount = other.m_refCount;
    m_impl     = other.m_impl;

    retain();
  }

  return *this;
}

ui::App&
ui::App::App::operator=(App&& other) {

  if (this != &other) {
    Object::operator=(std::move(other));

    delete m_impl;

    m_refCount = other.m_refCount;
    m_impl     = other.m_impl;

    other.m_refCount = nullptr;
    other.m_impl     = nullptr;
  }

  return *this;
}

void
ui::App::run() const {
  m_impl->run();
}

ui::Menu *
ui::App::menuBarMenu() const {
  return m_impl->menuBarMenu();
}

void
ui::App::menuBarMenu(Menu * menu) const {
  m_impl->menuBarMenu(menu);
}

void
ui::App::onExit(AppOnExitCb cb) {
  atexit(cb);
}

ui::App::~App() {
  release();

  if (*m_refCount > 0)
    return;

  delete m_impl;
}
