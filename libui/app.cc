//
//  app.cpp
//  libui-test
//
//  Created by Recep ASLANTAS on 3/24/15.
//  Copyright (c) 2015 Recep ASLANTAS. All rights reserved.
//

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