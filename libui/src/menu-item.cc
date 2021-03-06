/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../include/ui-menu.h"

#ifdef __APPLE__
#  include "cocoa/menu/menu-item.h"
#elif _WIN32
#  include "win/menu/win-menu-item.h"
#endif

#include <functional>

ui::MenuItem::MenuItem() {
  m_impl = new MenuItemImpl(this);
}

ui::MenuItem::MenuItem(CStringPtr title) {
  m_impl = new MenuItemImpl(this, title);
}

ui::MenuItem::MenuItem(MenuItemAction action) {
  m_impl = new MenuItemImpl(this, action);
}

ui::MenuItem::MenuItem(CStringPtr title, MenuItemAction action) {
  m_impl = new MenuItemImpl(this, title, action);
}

ui::MenuItem::MenuItem(const MenuItem& other)
  : m_impl(other.m_impl),
    ui::Object(other) {

  retain();
}

ui::MenuItem::MenuItem(MenuItem&& other)
  : m_impl(std::move(other.m_impl)),
    ui::Object(std::move(other)) {

  other.m_impl = nullptr;
}

ui::MenuItem&
ui::MenuItem::operator=(const MenuItem& other) {

  if (this != &other) {
    Object::operator=(other);

    delete m_impl;
    m_impl = other.m_impl;
    retain();
  }

  return *this;
}

ui::MenuItem&
ui::MenuItem::operator=(MenuItem&& other) {

  if (this != &other) {
    Object::operator=(std::move(other));

    delete m_impl;
    m_impl = std::move(other.m_impl);
    other.m_impl = nullptr;
  }

  return *this;
}

ui::Menu *
ui::MenuItem::menu() const {
  return m_impl->menu();
}

ui::Menu *
ui::MenuItem::subMenu() const {
  return m_impl->subMenu();
}

void
ui::MenuItem::setSubMenu(Menu * menu) const {
  m_impl->subMenu(menu);
}

ui::CStringPtr
ui::MenuItem::title() const {
  return m_impl->title();
}

void
ui::MenuItem::title(CStringPtr title) const {
  m_impl->title(title);
}

const ui::Image&
ui::MenuItem::image() const {
  return m_impl->image();
}

void
ui::MenuItem::setImage(const Image& image) const {
  m_impl->setImage(image);
}

void
ui::MenuItem::setImage(Image&& image) const {
  m_impl->setImage(std::move(image));
}

bool
ui::MenuItem::highlighted() const {
  return m_impl->highlighted();
}

void
ui::MenuItem::highlighted(bool highlighted) {
  m_impl->highlighted(highlighted);
}

bool
ui::MenuItem::enabled() const {
  return m_impl->enabled();
}

void
ui::MenuItem::enabled(bool enabled) {
  m_impl->enabled(enabled);
}

ui::CStringPtr
ui::MenuItem::keyEquivalent() const {
  return m_impl->keyEquivalent();
}

void
ui::MenuItem::keyEquivalent(CStringPtr keyEquivalent) {
  m_impl->keyEquivalent(keyEquivalent);
}

void
ui::MenuItem::setAction(MenuItemAction action) const {
  m_impl->setAction(action);
}

ui::MenuItem::~MenuItem() {
  release();

  if (*m_refCount > 0)
    return;

  delete m_impl;
}
