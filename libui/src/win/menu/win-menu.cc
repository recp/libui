/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "win-menu.h"
#include "win-menu-item.h"

#include "../../../include/ui-menu.h"

ui::Menu::MenuImpl::MenuImpl(Menu * _self) {
  m_menuItems = new std::vector<MenuItem *>();

  // TODO:
  m_self = _self;
}

ui::Menu::MenuImpl::MenuImpl(Menu * _self, CStringPtr title) {
  m_menuItems = new std::vector<MenuItem *>();

  m_title = title;
  m_self = _self;

  // TODO:

  m_self = _self;
}

ui::CStringPtr
ui::Menu::MenuImpl::title() const {
  return m_title;
}

void
ui::Menu::MenuImpl::title(CStringPtr title) {
  m_title = title;

  // TODO:
}

std::vector<ui::MenuItem *> *
ui::Menu::MenuImpl::menuItems() const {
  return m_menuItems;
}

void
ui::Menu::MenuImpl::addMenuItem(MenuItem * menuItem) {
  m_menuItems->push_back(menuItem);
  // TODO:
}

ui::Menu::MenuImpl::~MenuImpl() {
  m_menuItems->clear();
  m_menuItems = nullptr;

  // TODO:
}
