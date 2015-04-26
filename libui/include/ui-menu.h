/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui__menu__
#define __libui__menu__

#include "ui-base.h"
#include "ui-color.h"
#include "ui-geometry.h"
#include "ui-image.h"

#include <vector>
#include <functional>

namespace ui {

class _libui_export MenuItem;

class _libui_export Menu {
public:
  Menu();
  Menu(CStringPtr title);

  CStringPtr title() const;
  void title(CStringPtr title) const;

  std::vector<MenuItem *> * menuItems() const;
  void addMenuItem(MenuItem * menuItem);

  ~Menu();
private:
  class MenuImpl;
  MenuImpl * m_impl;
  friend class MenuItem;
  friend class App;
};

class _libui_export MenuItem {
public:
  typedef std::function<void (MenuItem *)> MenuItemAction;
  
  MenuItem();
  MenuItem(CStringPtr title);

  MenuItem(MenuItemAction action);
  MenuItem(CStringPtr title, MenuItemAction action);

  Menu * menu() const;
  Menu * subMenu() const;
  void setSubMenu(Menu * menu) const;

  CStringPtr title() const;
  void title(CStringPtr title) const;

  Image image() const;
  void image(Image image) const;

  bool highlighted() const;
  void highlighted(bool highlighted);

  bool enabled() const;
  void enabled(bool enabled);

  CStringPtr keyEquivalent() const;
  void keyEquivalent(CStringPtr keyEquivalent);

  void setAction(MenuItemAction action) const;

  ~MenuItem();
private:
  class MenuItemImpl;
  MenuItemImpl * m_impl;
  friend class Menu;
};

} // namespace ui

#endif /* defined(__libui__menu__) */
