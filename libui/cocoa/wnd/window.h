//
//  window.h
//  libui-test
//
//  Created by Recep ASLANTAS on 3/24/15.
//  Copyright (c) 2015 Recep ASLANTAS. All rights reserved.
//

#ifndef __libui_cocoa_window__
#define __libui_cocoa_window__

#include <objc/runtime.h>

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#import <AppKit/NSWindow.h>
#else
typedef objc_object CocoaWindow;
#endif

#include "../../geometry.h"
#include "../../window.h"
#include "../../view.h"

#ifdef __OBJC__
@interface CocoaWindow : NSWindow
- (instancetype) initWithRect: (NSRect) rect style: (NSUInteger) aStyle;
@end
#endif

namespace ui {

class Window::WindowImpl {
public:
  WindowImpl(Window *_self, Rect rect, int style = 0);
  
  void setTitle(const char * title) const;
  void show() const;
  
  View * contentView() const;
  void setContentView(View * view) ;
  
  ~WindowImpl();
private:
  int m_style;
  CocoaWindow * m_wnd;
  View * m_contentView;
  const Window * m_self;
};

} // namespace ui

#endif /* defined(__libui__cocoa_window__) */