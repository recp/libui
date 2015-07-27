/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "menu.h"
#include "menu-item.h"

#include "../../../include/ui-menu.h"

ui::Menu::MenuImpl::MenuImpl(Menu * _self) {
  m_menuItems = new std::vector<MenuItem>();

  m_cocoaMenu = [[NSMenu alloc] init];
  m_self = _self;
}

ui::Menu::MenuImpl::MenuImpl(Menu * _self, CStringPtr title) {
  m_menuItems = new std::vector<MenuItem>();

  m_title = title;
  m_self = _self;

  NSString * _nsTitle = [NSString stringWithCString: title
                                           encoding: NSUTF8StringEncoding];

  m_cocoaMenu = [[NSMenu alloc] initWithTitle: _nsTitle];

  m_self = _self;
}

ui::CStringPtr
ui::Menu::MenuImpl::title() const {
  return m_title;
}

void
ui::Menu::MenuImpl::title(CStringPtr title) {
  m_title = title;

  NSString * _nsTitle = [NSString stringWithCString: title
                                           encoding: NSUTF8StringEncoding];

  [m_cocoaMenu setTitle: _nsTitle];
}

std::vector<ui::MenuItem> *
ui::Menu::MenuImpl::menuItems() const {
  return m_menuItems;
}

void
ui::Menu::MenuImpl::addMenuItem(const MenuItem& menuItem) {
  m_menuItems->push_back(menuItem);
  [m_cocoaMenu addItem: menuItem.m_impl->m_cocoaMenuItem];
}

void
ui::Menu::MenuImpl::addMenuItem(MenuItem&& menuItem) {
  m_menuItems->push_back(std::move(menuItem));
  [m_cocoaMenu addItem: menuItem.m_impl->m_cocoaMenuItem];
}

ui::Menu::MenuImpl::~MenuImpl() {
  m_menuItems->clear();
  delete m_menuItems;
  m_menuItems = nullptr;

  [m_cocoaMenu removeAllItems];
  m_cocoaMenu = nil;

  m_title = nullptr;
}
