/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#import "app.h"
#include "menu/menu.h"

ui::App::AppImpl::AppImpl(App * _self) {
  m_cocoaApp = [NSApplication sharedApplication];
  [m_cocoaApp setActivationPolicy:NSApplicationActivationPolicyRegular];

  // force to create a default menubar menu
  this->menuBarMenu(this->menuBarMenu());

  m_self = _self;
}

void
ui::App::AppImpl::run() {
  [m_cocoaApp run];
}

void
ui::App::AppImpl::run(Window *rootWindow) {
  [m_cocoaApp activateIgnoringOtherApps: NO];
  [m_cocoaApp run];
}

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
  [NSApp setMainMenu: menu->m_impl->m_cocoaMenu];
}

ui::App::AppImpl::~AppImpl() {
  [NSApp setMainMenu: nil];
}
