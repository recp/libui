/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui__win__view__
#define __libui__win__view__

#include "../../config.h"
#include "../../../include/ui-geometry.h"
#include "../../../include/ui-view.h"
#include "../../../include/ui-color.h"

#include <vector>

namespace ui {

class View::ViewImpl {
public:
  ViewImpl(View * _self, Rect rect);

  Color backgroundColor() const;
  void setBackgroundColor(Color color);

  Rect getFrame() const;
  void setFrame(Rect frame);

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

  static LRESULT CALLBACK WndProc(HWND hWnd,
                                  UINT uMsg,
                                  WPARAM wParam,
                                  LPARAM lParam);

  TCHAR          m_szWindowClass[50];
  HWND           m_hWnd;
  HINSTANCE      m_hInstance;

  const View * m_self;
  friend class Window;
  friend class View;
};

} // namespace ui

#endif /* defined(__libui__win__view__) */
