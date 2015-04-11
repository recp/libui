/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#import "window.h"
#import <AppKit/AppKit.h>

#include "../view/view.h"

@implementation CocoaWindow

- (instancetype) initWithRect: (NSRect) rect style: (NSUInteger) aStyle {
  self = [super initWithContentRect: rect
                          styleMask: aStyle
                            backing: NSBackingStoreBuffered
                              defer: YES];

  if (self) {
    // ...
  }

  return self;
}

- (BOOL) canBecomeKeyWindow {
  return YES;
}

- (BOOL) canBecomeMainWindow {
  return YES;
}

@end

namespace wnd = ui;

NSUInteger translateWndStyleToCocoaWS(int style) {
  NSUInteger cocoaWS = 0;
  if (style == wnd::kWindowStyleDefault) {
    cocoaWS = (NSTitledWindowMask
             | NSMiniaturizableWindowMask
             | NSResizableWindowMask
             | NSClosableWindowMask);

    return cocoaWS;
  }

  BOOL borderless = false;

  if (style & wnd::kWindowStyleBorderless) {
    cocoaWS |= NSBorderlessWindowMask;
    borderless = true;
  }

  if ((style & wnd::kWindowStyleTitled) || !borderless)
    cocoaWS |= NSTitledWindowMask;

  if (style & wnd::kWindowStyleFullscreen)
    cocoaWS |= NSFullScreenWindowMask;

  if (style & wnd::kWindowStyleCloseButton)
    cocoaWS |= NSClosableWindowMask;

  if (style & wnd::kWindowStyleMaximizeButton)
    cocoaWS |= NSResizableWindowMask;

  if (style & wnd::kWindowStyleMinimizeButton)
    cocoaWS |= NSMiniaturizableWindowMask;

  return cocoaWS;
}

wnd::Window::WindowImpl::WindowImpl(Window *_self, Rect rect, int style)
    : m_self(_self) {

  NSInteger windowMask = translateWndStyleToCocoaWS(style);

  NSRect screenRect = [[NSScreen mainScreen] visibleFrame];

  NSRect contentRect = NSMakeRect(0, 0, rect.size.width, rect.size.height);
  NSRect consideredWndRect = [NSWindow frameRectForContentRect: contentRect
                                                     styleMask: windowMask];

  double originY = screenRect.size.height
                   - screenRect.origin.y
                   - consideredWndRect.size.height
                   - rect.origin.y;

  NSRect _nsRect = NSMakeRect(screenRect.origin.x + rect.origin.x,
                              originY,
                              rect.size.width,
                              rect.size.height);
  m_wnd = [[CocoaWindow alloc] initWithRect: _nsRect style: windowMask];

  m_self = _self;
}

void wnd::Window::WindowImpl::setTitle(const char *title) const {
  [m_wnd setTitle: [NSString stringWithCString: title
                                      encoding: NSUTF8StringEncoding]];
}

void wnd::Window::WindowImpl::show() const {
  [m_wnd makeKeyAndOrderFront: nil];
}

ui::View * wnd::Window::WindowImpl::contentView() const {
  return m_contentView;
}

void wnd::Window::WindowImpl::setContentView(ui::View *view) {
  NSView *_nsView = view->m_impl->m_view;
  [m_wnd setContentView: _nsView];

  view->m_impl->m_wnd = const_cast<Window *>(m_self);
  m_contentView = view;
}

wnd::Window::WindowImpl::~WindowImpl() {
  m_wnd = nil;
}
