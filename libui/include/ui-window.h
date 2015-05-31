/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui__window__
#define __libui__window__

#include "ui-base.h"
#include "ui-geometry.h"
#include "ui-view.h"

namespace ui {

//class IWindow {
//public:
//  virtual const Rect&& getRect() const = 0;
//  virtual View * contentView() const = 0;
//};

enum WindowStyle {
  kWindowStyleDefault        = 0,
  kWindowStyleTitled         = 1 << 0,
  kWindowStyleBorderless     = 1 << 1,
  kWindowStyleFullscreen     = 1 << 2,

  kWindowStyleCloseButton    = 1 << 3,
  kWindowStyleMinimizeButton = 1 << 4,
  kWindowStyleMaximizeButton = 1 << 5,

  kWindowStyleAllButtons     = kWindowStyleCloseButton
                              |kWindowStyleMinimizeButton
                              |kWindowStyleMaximizeButton
};

enum WindowCloseBehavior {
  kWindowCloseBehavior_None,
  kWindowCloseBehavior_AppShouldExit
};

class _libui_export Window /* : public IWindow */ {
public:
  Window(Rect rect, int style = 0);
  Window(Window * parent,  Rect rect, int style = 0);

  void getTitle() const;
  void setTitle(const char * title) const;

  Rect getFrame() const;
  void setFrame(Rect frame) const;

  bool isFullScreen() const;
  void toogleFullScreen() const;

  View * contentView() const;
  void setContentView(View * view) const;

  void center();

  void show() const;
  void hide() const;

  WindowCloseBehavior getCloseBehavior() const;
  void setCloseBehavior(WindowCloseBehavior closeBehavior) const;

  void attachToWindow(Window * wnd) const;

  ~Window();
private:
  Window() = delete;

  class WindowImpl;
  WindowImpl* m_impl;
};

} // namespace ui

#endif /* defined(__libui__window__) */
