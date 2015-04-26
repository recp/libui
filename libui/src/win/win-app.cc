/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../config.h"
#include "win-app.h"

ui::App::AppImpl::AppImpl(App * _self) {
  // force to create a default menubar menu
  this->menuBarMenu(this->menuBarMenu());

  m_self = _self;
}

void 
ui::App::AppImpl::run() {
  MSG msg;

  /*
     TODO:
     https://msdn.microsoft.com/en-us/library/windows/desktop/ms646373(v=vs.85).aspx
   */
  // HACCEL hAccelTable;
  // static LPCTSTR lpTableName = L"ui_app_accel_tbl";
  // hAccelTable = LoadAccelerators(hInstance, lpTableName);
  while (GetMessage(&msg, NULL, 0, 0)) {
   // if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   // }
  }
}

//void app::appimpl::run(window *rootwindow) {
//
//}

ui::Menu *
ui::App::AppImpl::menuBarMenu() {
  if (!m_menuBarMenu)
    m_menuBarMenu = new Menu;

  return m_menuBarMenu;
}

void
ui::App::AppImpl::menuBarMenu(Menu * menu) {
  if (m_menuBarMenu && m_menuBarMenu != menu)
    delete m_menuBarMenu;

  m_menuBarMenu = menu;
  // TODO:
}

ui::App::AppImpl::~AppImpl() {

}
