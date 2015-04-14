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

#include <vector>

namespace ui {

class _libui_export Image;
class _libui_export MenuItem;

class _libui_export Menu {
public:
  Menu();
  Menu(CStringPtr title);

  CStringPtr title() const;
  void title(CStringPtr title) const;

  std::vector<MenuItem *> menuItems() const;
  void addSubview(MenuItem * menuItem) const;
};

class _libui_export MenuItem {
public:
  MenuItem();
  MenuItem(CStringPtr title);

  Menu * menu() const;
  Menu * subMenu() const;

  CStringPtr title() const;
  void title(CStringPtr title) const;

  Image image() const;
  void image(Image image) const;

  bool highlighted() const;
  void highlighted(bool highlighted);

  bool enabled() const;
  void enabled(bool enabled);
};

} // namespace ui

#endif /* defined(__libui__menu__) */
