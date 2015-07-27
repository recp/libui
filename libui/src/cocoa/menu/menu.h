/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui__cocoa__menu__
#define __libui__cocoa__menu__

#include <objc/runtime.h>

#ifdef __OBJC__
#import <AppKit/NSMenu.h>
#else
typedef objc_object NSMenu;
#endif

#include "../../../include/ui-app.h"
#include "../../../include/ui-menu.h"

namespace ui {
  
class Menu::MenuImpl {
public:
  MenuImpl(Menu * _self);
  MenuImpl(Menu * _self, CStringPtr title);

  MenuImpl(const MenuImpl& other) = delete;
  MenuImpl& operator=(const MenuImpl& other) = delete;
  
  CStringPtr title() const;
  void title(CStringPtr title);
  
  std::vector<MenuItem *> * menuItems() const;
  void addMenuItem(MenuItem * menuItem);

  ~MenuImpl();
private:
  CStringPtr m_title;
  NSMenu * m_cocoaMenu;
  std::vector<MenuItem *> * m_menuItems;
  const Menu * m_self;
  friend class Menu;
  friend class MenuItem;
  friend class App;
};
  
} // namespace ui

#endif /* defined(__libui__cocoa__menu__) */
