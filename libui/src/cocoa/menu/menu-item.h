/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui__cocoa__menu_item__
#define __libui__cocoa__menu_item__

#include <objc/runtime.h>

#ifdef __OBJC__
#import <AppKit/NSMenuItem.h>
#else
typedef objc_object NSMenuItem;
typedef objc_object CocoaMenuItem;
#endif

#include "../../../include/ui-menu.h"

#ifdef __OBJC__
@interface CocoaMenuItem : NSMenuItem {
@public
  ui::MenuItem * m_menuItem;
  ui::MenuItem::MenuItemAction * m_pMenuAction;
}
@end // cocoa interface CocoaMenuItem
#endif

namespace ui {

class MenuItem::MenuItemImpl {
public:
  MenuItemImpl(MenuItem * _self);
  MenuItemImpl(MenuItem * _self, CStringPtr title);
  MenuItemImpl(MenuItem * _self, MenuItemAction action);
  MenuItemImpl(MenuItem * _self, CStringPtr title, MenuItemAction action);

  MenuItemImpl(const MenuItemImpl& other) = delete;
  MenuItemImpl& operator=(const MenuItemImpl& other) = delete;

  Menu * menu() const;

  Menu * subMenu() const;
  void subMenu(Menu * menu);

  CStringPtr title() const;
  void title(CStringPtr title);

  const Image& image() const;

  void setImage(const Image& image);
  void setImage(Image&& image);

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
  CocoaMenuItem * m_cocoaMenuItem;
  MenuItem * m_self;
  friend class Menu;
};

} // namespace ui

#endif /* defined(__libui__cocoa_menu_item__) */
