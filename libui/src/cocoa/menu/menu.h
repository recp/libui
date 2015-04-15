/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui__cocoa__menu__
#define __libui__cocoa__menu__

#include "../../../include/ui-menu.h"

namespace ui {
  
class Menu::MenuImpl {
public:
  MenuImpl(Menu * _self);
  MenuImpl(Menu * _self, CStringPtr title);
  
  CStringPtr title() const;
  void title(CStringPtr title);
  
  std::vector<MenuItem *> * menuItems() const;
  void addSubview(MenuItem * menuItem) const;
private:
  CStringPtr m_title;
  std::vector<MenuItem *> * m_menuItems;
  const Menu * m_self;
};
  
} // namespace ui

#endif /* defined(__libui__cocoa__menu__) */
