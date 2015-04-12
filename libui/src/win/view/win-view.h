/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui__win__view__
#define __libui__win__view__

#include "../../../include/ui-geometry.h"
#include "../../../include/ui-view.h"
#include "../../../include/ui-color.h"

#include <vector>

namespace ui {

class View::ViewImpl {
public:
  ViewImpl(View * _self, Rect rect);

  Color backgroundColor() const;
  void setBackgroundColor(Color color) const;

  Rect getFrame() const;
  void setFrame(Rect frame) const;

  void addSubview(View * subview) const;
  void removeFromSuperview() const;

  const Window * window() const;

  ~ViewImpl();
private:
  Rect m_frame;
  Color m_bgcolor;
  void * m_view;
  std::vector<View *> * m_subviews;
  View * m_superview;
  Window * m_wnd;
  const View * m_self;
  friend class Window;
  friend class View;
};

} // namespace ui

#endif /* defined(__libui__win__view__) */
