/*
 * Copyright (c), Recep Aslantas.
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

#include "../../../include/ui-geometry.h"
#include "../../../include/ui-window.h"
#include "../../../include/ui-view.h"

#ifdef __OBJC__
@interface CocoaWindow : NSWindow <NSWindowDelegate>
@property (nonatomic, assign, getter=isFullScreen) bool fullScreen;
@property (nonatomic, assign) ui::WindowCloseBehavior closeBahavior;
- (instancetype) initWithRect: (NSRect) rect style: (NSUInteger) aStyle;
@end
#endif

namespace ui {

class Window::WindowImpl {
public:
  WindowImpl(Window *_self, Rect rect, int style = 0);

  CStringPtr getTitle() const;
  void setTitle(CStringPtr title) const;

  Rect getFrame() const;
  void setFrame(Rect frame);
  
  View * contentView();
  void setContentView(View * view) ;

  void show() const;
  void hide() const;

  void center();
  bool isFullScreen() const;
  void enterFullScreen() const;
  void exitFullScreen() const;

  WindowCloseBehavior getCloseBehavior() const;
  void setCloseBehavior(WindowCloseBehavior closeBehavior);

  ~WindowImpl();
private:
  int                 m_style;
  WindowCloseBehavior m_closeBehavior;
  CocoaWindow *       m_wnd;
  View *              m_contentView;
  const Window *      m_self;
};

} // namespace ui

#endif /* defined(__libui__cocoa_window__) */