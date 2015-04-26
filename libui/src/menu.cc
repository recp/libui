/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../include/ui-menu.h"

#ifdef __APPLE__
#  include "cocoa/menu/menu.h"
#elif _WIN32

#endif

ui::Menu::Menu() {
  m_impl = new MenuImpl(this);
}

ui::Menu::Menu(CStringPtr title) {
  m_impl = new MenuImpl(this, title);
  m_impl->title(title);
}

ui::CStringPtr ui::Menu::title() const {
  return m_impl->title();
}

void ui::Menu::title(CStringPtr title) const {
  m_impl->title(title);
}

std::vector<ui::MenuItem *> * ui::Menu::menuItems() const {
  return m_impl->menuItems();
}

void ui::Menu::addMenuItem(MenuItem * menuItem) {
  m_impl->addMenuItem(menuItem);
}

ui::Menu::~Menu() {
  delete m_impl;
}