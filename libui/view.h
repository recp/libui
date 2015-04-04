//
//  view.h
//  libui
//
//  Created by Recep ASLANTAS on 3/23/15.
//  Copyright (c) 2015 Recep ASLANTAS. All rights reserved.
//

#ifndef __libui__view__
#define __libui__view__

#include "color.h"
#include "geometry.h"

#include <vector>

namespace ui {

class Window;
  
class View {
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
