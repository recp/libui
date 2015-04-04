//
//  window.h
//  libui
//
//  Created by Recep ASLANTAS on 3/23/15.
//  Copyright (c) 2015 Recep ASLANTAS. All rights reserved.
//

#ifndef __libui__window__
#define __libui__window__

#include "geometry.h"
#include "view.h"

namespace ui {
  
//class IWindow {
//public:
//  virtual const Rect&& getRect() const = 0;
//  virtual View * contentView() const = 0;
//};

enum WindowStyle {
  kWindowStyleDefault                 = 0,
  kWindowStyleTitled                    = 1 << 0,
  kWindowStyleBorderless           = 1 << 1,
  kWindowStyleFullscreen            = 1 << 2,

  kWindowStyleCloseButton        = 1 << 3,
  kWindowStyleMinimizeButton  = 1 << 4,
  kWindowStyleMaximizeButton = 1 << 5,
  
  kWindowStyleAllButtons            = kWindowStyleCloseButton|kWindowStyleMinimizeButton|kWindowStyleMaximizeButton
} ;

class Window /* : public IWindow */ {
public:
  Window(Rect rect, int style = 0);
  Window(Window * parent,  Rect rect, int style = 0);

  void getTitle() const;
  void setTitle(const char * title) const;

  void attachToWindow(Window * wnd) const;

  const Point&& getPosition() const;
  void setPosition(Point rect) const;

  const Rect&& getRect() const;
  void setRect(Rect rect) const;
  
  bool isFullScreen() const;
  void toogleFullScreen() const;
  
  View * contentView() const;
  void setContentView(View * view) const;
  
  void center();
  void centerVertical();
  void centerHorizontal();
  
  // Iki duruma da WindowAnimation eklenebilir
  void show() const;
  void hide() const;
  
  ~Window();
private:
  Window() = delete;
  
  class WindowImpl;
  WindowImpl* m_impl;
};

} // namespace ui

#endif /* defined(__libui__window__) */
