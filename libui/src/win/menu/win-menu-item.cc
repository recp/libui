/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "win-menu-item.h"
#include "win-menu.h"

ui::MenuItem::MenuItemImpl::MenuItemImpl(MenuItem * _self) {
  // TODO:

  m_self = _self;
}

ui::MenuItem::MenuItemImpl::MenuItemImpl(MenuItem * _self, CStringPtr title) {
  m_title = title;

  // TODO:

  m_self = _self;
}

ui::MenuItem::MenuItemImpl::MenuItemImpl(MenuItem * _self,
                                         MenuItemAction action) {
  m_menuItemAction = action;

  // TODO:

  m_self = _self;
}

ui::MenuItem::MenuItemImpl::MenuItemImpl(MenuItem * _self,
                                         CStringPtr title,
                                         MenuItemAction action) {
  m_title = title;
  m_menuItemAction = action;

  // TODO:

  m_self = _self;
}

ui::CStringPtr
ui::MenuItem::MenuItemImpl::title() const {
  return m_title;
}

void
ui::MenuItem::MenuItemImpl::title(CStringPtr title) {
  m_title = title;

  // TODO:
}

ui::Image
ui::MenuItem::MenuItemImpl::image() const {
  return m_image;
}

void
ui::MenuItem::MenuItemImpl::image(Image image) {
  m_image = image;
  // TODO:
}

bool
ui::MenuItem::MenuItemImpl::highlighted() const {
  return m_highlighted;
}

void
ui::MenuItem::MenuItemImpl::highlighted(bool highlighted) {
  m_highlighted = highlighted;
  // TODO:
}

bool
ui::MenuItem::MenuItemImpl::enabled() const {
  return m_enabled;
}

void
ui::MenuItem::MenuItemImpl::enabled(bool enabled) {
  m_enabled = enabled;
  // TODO:
}

ui::Menu *
ui::MenuItem::MenuItemImpl::menu() const {
  return m_menu;
}

ui::Menu *
ui::MenuItem::MenuItemImpl::subMenu() const {
  return m_subMenu;
}

void
ui::MenuItem::MenuItemImpl::subMenu(Menu * menu) {
  m_subMenu = menu;
  // TODO:
}

ui::CStringPtr
ui::MenuItem::MenuItemImpl::keyEquivalent() const {
  return m_keyEquivalent;
}

void
ui::MenuItem::MenuItemImpl::keyEquivalent(CStringPtr keyEquivalent) {
  m_keyEquivalent = keyEquivalent;

  if (!keyEquivalent)
    m_keyEquivalent = "";

  // TODO:
}

void
ui::MenuItem::MenuItemImpl::setAction(MenuItemAction action) {
  m_menuItemAction = action;

  // TODO:
}

ui::MenuItem::MenuItemImpl::~MenuItemImpl() {
  // TODO:
}
