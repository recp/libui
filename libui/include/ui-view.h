/*
 * Copyright (c), Recep Aslantas. All rights reserved.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui__view__
#define __libui__view__

#include "types.h"
#include "ui-color.h"
#include "ui-geometry.h"

#include <vector>

namespace ui {

class Window;
  
class _libui_export View {
public:
  View(Rect rect);
  
  Color backgroundColor() const;
  void setBackgroundColor(Color color) const;
  
  Rect getFrame() const;
  void setFrame(Rect frame) const;
  
  bool userInteractionEnabled() const;
  void setUserInteractionEnabled(bool) const;
  
  const Window * window() const;
  
  // CALayer gibi olabilir
  void layer();
  void transform();
  
  // View Hierarchy
  std::vector<View *> subviews() const;
  void addSubview(View * subview) const;
  
  // Alternative names: popView();, pop();
  void removeFromSuperview() const;
  
  void bringSubviewToFront(View * view) const;
  void sendSubviewToBack(View * view) const;
  
  void setNeedsLayout() const;
  void layoutIfNeeded() const;
  
  void layoutSubviews() const;
  
  //
  void setHidden(bool isHidden) const;
  bool isHidden() const;
  
  ~View();
private:
  class ViewImpl;
  ViewImpl * m_impl;
  friend class Window;
};
  
} // namespace ui

#endif /* defined(__libui__view__) */
