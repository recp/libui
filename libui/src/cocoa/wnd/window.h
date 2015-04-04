/*
 * Copyright (c), Recep Aslantas. All rights reserved.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui_cocoa_window__
#define __libui_cocoa_window__

#include <objc/runtime.h>

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#import <AppKit/NSWindow.h>
#else
typedef objc_object CocoaWindow;
#endif

#include "../../../include/geometry.h"
#include "../../../include/window.h"
#include "../../../include/view.h"

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