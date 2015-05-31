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
    self.delegate = self;
  }

  return self;
}

- (BOOL) canBecomeKeyWindow {
  return YES;
}

- (BOOL) canBecomeMainWindow {
  return YES;
}

- (void) windowWillClose:(NSNotification *)notification {
  if (self.closeBahavior == ui::kWindowCloseBehavior_AppShouldExit) {
    [[NSApplication sharedApplication] terminate: nil];
  }
}

@end

NSUInteger translateWndStyleToCocoaWS(int style) {
  NSUInteger cocoaWS = 0;
  if (style == ui::kWindowStyleDefault) {
    cocoaWS = (NSTitledWindowMask
             | NSMiniaturizableWindowMask
             | NSResizableWindowMask
             | NSClosableWindowMask);

    return cocoaWS;
  }

  BOOL borderless = false;

  if (style & ui::kWindowStyleBorderless) {
    cocoaWS |= NSBorderlessWindowMask;
    borderless = true;
  }

  if ((style & ui::kWindowStyleTitled) || !borderless)
    cocoaWS |= NSTitledWindowMask;

  if (style & ui::kWindowStyleFullscreen)
    cocoaWS |= NSFullScreenWindowMask;

  if (style & ui::kWindowStyleCloseButton)
    cocoaWS |= NSClosableWindowMask;

  if (style & ui::kWindowStyleMaximizeButton)
    cocoaWS |= NSResizableWindowMask;

  if (style & ui::kWindowStyleMinimizeButton)
    cocoaWS |= NSMiniaturizableWindowMask;

  return cocoaWS;
}

ui::Window::WindowImpl::WindowImpl(Window *_self, Rect rect, int style)
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

ui::CStringPtr
ui::Window::WindowImpl::getTitle() const {
  NSString * _nsTitle = [m_wnd title];
  CStringPtr title = [_nsTitle cStringUsingEncoding: NSUTF8StringEncoding];
  return title;
}

void
ui::Window::WindowImpl::setTitle(CStringPtr title) const {
  [m_wnd setTitle: [NSString stringWithCString: title
                                      encoding: NSUTF8StringEncoding]];
}

void
ui::Window::WindowImpl::show() const {
  [m_wnd makeKeyAndOrderFront: nil];
}


ui::Rect
ui::Window::WindowImpl::getFrame() const {
  NSRect _nswndFrame = m_wnd.frame;
  Rect wndFrame({{_nswndFrame.origin.x, _nswndFrame.origin.y},
                 {_nswndFrame.size.width, _nswndFrame.size.height}});
  return wndFrame;
}

void
ui::Window::WindowImpl::setFrame(Rect frame) {
  [m_wnd setFrame: frame display: YES];
}

ui::View *
ui::Window::WindowImpl::contentView() const {
  return m_contentView;
}

void
ui::Window::WindowImpl::setContentView(ui::View *view) {
  NSView *_nsView = view->m_impl->m_view;
  [m_wnd setContentView: _nsView];

  view->m_impl->m_wnd = const_cast<Window *>(m_self);
  m_contentView = view;
}

ui::WindowCloseBehavior
ui::Window::WindowImpl::getCloseBehavior() const {
  return m_closeBehavior;
}

void
ui::Window::WindowImpl::setCloseBehavior(WindowCloseBehavior closeBehavior) {
  m_closeBehavior = closeBehavior;
  [m_wnd setCloseBahavior: closeBehavior];
}

ui::Window::WindowImpl::~WindowImpl() {
  m_wnd = nil;
}
