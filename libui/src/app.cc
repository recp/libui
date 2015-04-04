/*
 * Copyright (c), Recep Aslantas. All rights reserved.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "app.h"
#include "cocoa/app.h"
#include "cocoa/wnd/window.h"

namespace app = ui;

app::App::App() {
  m_impl = new AppImpl();
}

void app::App::run() {
  m_impl->run();
}

void app::App::run(Window *rootWindow) {
  m_impl->run(rootWindow);
}