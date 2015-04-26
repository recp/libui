/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui__win__menu_item__
#define __libui__win__menu_item__

#include "../../../include/ui-menu.h"

namespace ui {

class MenuItem::MenuItemImpl {
public:
  MenuItemImpl(MenuItem * _self);
  MenuItemImpl(MenuItem * _self, CStringPtr title);
  MenuItemImpl(MenuItem * _self, MenuItemAction action);
  MenuItemImpl(MenuItem * _self, CStringPtr title, MenuItemAction action);

  Menu * menu() const;

  Menu * subMenu() const;
  void subMenu(Menu * menu);

  CStringPtr title() const;
  void title(CStringPtr title);

  Image image() const;
  void image(Image image);

  bool highlighted() const;
  void highlighted(bool highlighted);

  bool enabled() const;
  void enabled(bool enabled);

  CStringPtr keyEquivalent() const;
  void keyEquivalent(CStringPtr keyEquivalent);
  
  void setAction(MenuItemAction action);

  ~MenuItemImpl();
private:
  CStringPtr m_title;
  Image m_image;
  bool m_highlighted;
  bool m_enabled;
  Menu * m_menu;
  Menu * m_subMenu;
  CStringPtr m_keyEquivalent;
  MenuItemAction m_menuItemAction;
  MenuItem * m_self;
  friend class Menu;
};

} // namespace ui

#endif /* defined(__libui__win_menu_item__) */
