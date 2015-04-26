/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui_cocoa_app__
#define __libui_cocoa_app__

#include <objc/runtime.h>

#ifdef __OBJC__
#import <AppKit/NSApplication.h>
#else
typedef objc_object NSApplication;
#endif

#include "../../include/ui-app.h"
#include "../../include/ui-window.h"
#include "../../include/ui-menu.h"

namespace ui {
  
class App::AppImpl {
public:
  AppImpl(App * _self);
  void run();
  void run(Window * rootWindow);

  Menu * menuBarMenu();
  void menuBarMenu(Menu * menu);

  ~AppImpl();
private:
  NSApplication * m_cocoaApp;
  Menu * m_menuBarMenu;
  const App * m_self;
};

} // namespace ui

#endif /* defined (__libui__cocoa_app__) */