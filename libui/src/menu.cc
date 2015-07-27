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
#  include "win/menu/win-menu.h"
#endif

#include <functional>

ui::Menu::Menu() {
  m_impl = new MenuImpl(this);
}

ui::Menu::Menu(CStringPtr title) {
  m_impl = new MenuImpl(this, title);
  m_impl->title(title);
}

ui::Menu::Menu(const Menu& other) {
  m_refCount = other.m_refCount;
  m_impl     = other.m_impl;

  retain();
}

ui::Menu&
ui::Menu::Menu::operator=(const Menu& other) {

  if (this != &other) {
    Object::operator=(other);

    delete m_impl;
    
    m_refCount = other.m_refCount;
    m_impl     = other.m_impl;

    retain();
  }

  return *this;
}

ui::CStringPtr
ui::Menu::title() const {
  return m_impl->title();
}

void ui::Menu::title(CStringPtr title) const {
  m_impl->title(title);
}

std::vector<ui::MenuItem> *
ui::Menu::menuItems() const {
  return m_impl->menuItems();
}

void
ui::Menu::addMenuItem(const MenuItem& menuItem) {
  m_impl->addMenuItem(menuItem);
}

void
ui::Menu::addMenuItem(MenuItem&& menuItem) {
  m_impl->addMenuItem(std::move(menuItem));
}

ui::Menu::~Menu() {
  release();

  if (*m_refCount > 0)
    return;

  delete m_impl;
}
