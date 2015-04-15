/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "menu.h"

ui::Menu::MenuImpl::MenuImpl(Menu * _self) {
  m_self = _self;
}

ui::Menu::MenuImpl::MenuImpl(Menu * _self, CStringPtr title) {
  m_title = title;
  m_self = _self;
}

ui::CStringPtr ui::Menu::MenuImpl::title() const {
  return m_title;
}

void ui::Menu::MenuImpl::title(CStringPtr title) {
  m_title = title;
}

std::vector<ui::MenuItem *> * ui::Menu::MenuImpl::menuItems() const {
  return m_menuItems;
}

void ui::Menu::MenuImpl::addSubview(MenuItem * menuItem) const {
  
}