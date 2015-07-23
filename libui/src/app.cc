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

//void app::App::run(Window *rootWindow) {
//  m_impl->run(rootWindow);
//}

ui::App::~App() {
  delete m_impl;
}
