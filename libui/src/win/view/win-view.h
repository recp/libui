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

  ViewImpl(const ViewImpl& other) = delete;
  ViewImpl& operator=(const ViewImpl& other) = delete;
  
  Color backgroundColor() const;
  void setBackgroundColor(Color color);

  Rect getFrame() const;
  void setFrame(Rect frame);

  bool isInputEnabled() const;
  void setInputEnabled(bool enabled);

  const View * superview() const;
  const Window * window() const;

  std::vector<ui::View> * subviews() const;

  void addSubview(const View& subview);
  void addSubview(View&& subview);

  void removeFromSuperview();

  void bringSubviewToFront(View * view);
  void sendSubviewToBack(View * view);

  void setHidden(bool isHidden);
  bool isHidden() const;

  void forceRedraw() const;
  ~ViewImpl();
private:
  Rect m_frame;
  Color m_bgcolor;
  std::vector<View> * m_subviews;

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
