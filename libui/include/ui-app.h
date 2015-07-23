/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui__app__
#define __libui__app__

#include "ui-base.h"
#include "ui-window.h"
#include "ui-menu.h"

namespace ui {

class _libui_export App {
public:
  typedef void (*AppOnExitCb)(void);

  App();
  
  void run() const;
  void run(Window * rootWindow) const;

  Menu * menuBarMenu() const;
  void menuBarMenu(Menu * menu) const;

  // Events
  void onExit(AppOnExitCb cb);

  ~App();
private:
  class AppImpl;
  AppImpl * m_impl;
};

} // namespace ui

#endif /* defined(__libui__app__) */
