/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#import "view.h"

@implementation CocoaView

- (instancetype) initWithFrame: (NSRect)frameRect {
  self = [super initWithFrame: frameRect];
  if (self) {
    [self setWantsLayer: YES];
  }
  return self;
}

- (void)setBackgroundColor: (ui::Color)backgroundColor {
  [self.layer setBackgroundColor: backgroundColor];
  [self setNeedsDisplay: YES];

//  CGContextRef context = (CGContextRef)[[NSGraphicsContext currentContext] graphicsPort];
//  CGContextSetRGBFillColor (context, 1.0, 0.0, 1.0, 1.0);
//  CGContextFillRect(context, NSRectToCGsRect(self.frame));
//
//  [self setNeedsDisplay: YES];
}

- (NSViewLayerContentsRedrawPolicy)layerContentsRedrawPolicy {
  return NSViewLayerContentsRedrawOnSetNeedsDisplay;
}

- (void)drawRect: (NSRect)dirtyRect {

//  CGContextRef context = (CGContextRef)[[NSGraphicsContext currentContext] graphicsPort];
//  CGContextSetRGBFillColor (context, 1.0, 0.0, 1.0, 1.0);
//  CGContextFillRect(context, NSRectToCGRect(self.frame));

  [super drawRect: dirtyRect];
}

- (BOOL)isFlipped {
  return YES;
}

@end

ui::View::ViewImpl::ViewImpl(View * _self, Rect rect) : m_self(_self) {
  m_subviews = new std::vector<View *>();
  m_frame = rect;

  NSRect _nsRect = NSMakeRect(rect.origin.x,
                              rect.origin.y,
                              rect.size.width,
                              rect.size.height);

  m_view = [[CocoaView alloc] initWithFrame: _nsRect];
}

ui::Color ui::View::ViewImpl::backgroundColor() const {
  return m_bgcolor;
}

void ui::View::ViewImpl::setBackgroundColor(Color color) const {
  [m_view setBackgroundColor: color];
}

ui::Rect ui::View::ViewImpl::getFrame() const {
  return m_frame;
}

void ui::View::ViewImpl::setFrame(Rect frame) const {
  [m_view setFrame: frame];
}

void ui::View::ViewImpl::addSubview(View *subview) const {
  subview->m_impl->m_superview = const_cast<View *>(this->m_self);

  /* Because of isFlipped  */
//  Rect selfFrame = this->getFrame();
//  Rect subviewFrame = subview->getFrame();

//  double originY = selfFrame.size.height - subviewFrame.size.height - subviewFrame.origin.y;
//  subviewFrame.origin.y = originY;

  subview->setFrame(subview->getFrame());

  [m_view addSubview: subview->m_impl->m_view];
  m_subviews->push_back(subview);
}

void ui::View::ViewImpl::removeFromSuperview() const {
  [m_view removeFromSuperview];
}

const ui::Window * ui::View::ViewImpl::window() const {
  return m_wnd;
}

ui::View::ViewImpl::~ViewImpl() {
  m_subviews->clear();
  delete m_subviews;
  m_view = nil;
}
