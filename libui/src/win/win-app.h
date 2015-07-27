/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui_win_app__
#define __libui_win_app__

#include "../../include/ui-app.h"
#include "../../include/ui-window.h"
#include "../../include/ui-menu.h"

namespace ui {

class App::AppImpl {
public:
  AppImpl(App * _self);

  AppImpl(const AppImpl& other) = delete;
  AppImpl& operator=(const AppImpl& other) = delete;

  void run();
 //  void run(Window * rootWindow);

  Menu * menuBarMenu();
  void menuBarMenu(Menu * menu);

  ~AppImpl();
private:
  Menu * m_menuBarMenu;
  const App * m_self;
};

} // namespace ui

#endif /* defined(__libui_win_app__) */