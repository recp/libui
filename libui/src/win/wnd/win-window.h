/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui_win_window__
#define __libui_win_window__

#include "../../config.h"
#include "../../../include/ui-geometry.h"
#include "../../../include/ui-window.h"
#include "../../../include/ui-view.h"

namespace ui {

class Window::WindowImpl {
public:
  WindowImpl(Window *_self, Rect rect, int style = 0);

  CStringPtr getTitle() const;
  void setTitle(CStringPtr title);

  Rect getFrame() const;
  void setFrame(Rect frame);

  View * contentView();
  void setContentView(View * view);

  void show();
  void hide();

  void center();
  bool isFullScreen() const;
  void enterFullScreen();
  void exitFullScreen();

  WindowCloseBehavior getCloseBehavior() const;
  void setCloseBehavior(WindowCloseBehavior closeBehavior);

  ~WindowImpl();
private:
  static LRESULT CALLBACK WndProc(HWND hWnd,
                                  UINT message,
                                  WPARAM wParam,
                                  LPARAM lParam);

  bool                m_isFullScreen;
  int                 m_style;
  View *              m_contentView;
  WindowCloseBehavior m_closeBehavior;
  TCHAR               m_szWindowClass[50];
  HWND                m_hWnd;
  HINSTANCE           m_hInstance;
  LPCWSTR             m_szTitle;
  WINDOWPLACEMENT     m_prevPlace;

  const Window *      m_self;
};

} // namespace ui

#endif /* defined(__libui_win_window__) */