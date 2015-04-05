/*
* Copyright (c), Recep Aslantas. All rights reserved.
*
* MIT License (MIT), http://opensource.org/licenses/MIT
* Full license can be found in the LICENSE file
*/

#ifndef __libui_win_window__
#define __libui_win_window__

#include "../../../include/geometry.h"
#include "../../../include/window.h"
#include "../../../include/view.h"

namespace ui {

class Window::WindowImpl {
public:
  WindowImpl(Window *_self, Rect rect, int style = 0);

  void setTitle(const char * title) const;
  void show() const;

  View * contentView() const;
  void setContentView(View * view);

  ~WindowImpl();
private:
  int m_style;
  void * m_wnd;
  View * m_contentView;
  const Window * m_self;
};

} // namespace ui

#endif /* defined(__libui_win_window__) */