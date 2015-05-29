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

ui::Color
ui::View::ViewImpl::backgroundColor() const {
  return m_bgcolor;
}

void
ui::View::ViewImpl::setBackgroundColor(Color color) const {
  [m_view setBackgroundColor: color];
}

ui::Rect
ui::View::ViewImpl::getFrame() const {
  return m_frame;
}

void
ui::View::ViewImpl::setFrame(Rect frame) const {
  [m_view setFrame: frame];
}

bool
ui::View::ViewImpl::isInputEnabled() const {
  return m_inputEnabled;
}

void
ui::View::ViewImpl::setInputEnabled(bool enabled) {
  m_inputEnabled = enabled;
}

const ui::View *
ui::View::ViewImpl::superview() const {
  return m_superview;
}

const ui::Window *
ui::View::ViewImpl::window() const {
  return m_wnd;
}

std::vector<ui::View *> *
ui::View::ViewImpl::subviews() const {
  return m_subviews;
}

void
ui::View::ViewImpl::addSubview(View *subview) {
  subview->removeFromSuperview();

  ViewImpl * subviewImpl = subview->m_impl;

  subviewImpl->m_superview = const_cast<View *>(this->m_self);
  subviewImpl->m_wnd = m_wnd;

  subview->setFrame(subview->getFrame());

  [m_view addSubview: subviewImpl->m_view];

  // Update all subviews' window ptr
  std::vector<View *>::iterator subview_it =
  subviewImpl->m_subviews->begin();
  for (; subview_it != subviewImpl->m_subviews->end(); subview_it++) {
    (*subview_it)->m_impl->m_wnd = m_wnd;
  }

  m_subviews->push_back(subview);
}

void
ui::View::ViewImpl::removeFromSuperview() {
  if (!m_superview)
    return;

  [m_view removeFromSuperview];

  View * _self = const_cast<View * >(m_self);

  ViewImpl * superviewImpl = m_superview->m_impl;

  std::vector<View *>::iterator fountView_it =
  std::find(superviewImpl->m_subviews->begin(),
            superviewImpl->m_subviews->end(),
            _self);

  if (fountView_it != superviewImpl->m_subviews->end()) {
    superviewImpl->m_subviews->erase(fountView_it);
  }

  // Update all subviews' window ptr
  std::vector<View *>::iterator subview_it = m_subviews->begin();
  for (; subview_it != m_subviews->end(); subview_it++) {
    (*subview_it)->m_impl->m_wnd = nullptr;
  }

  m_superview = nullptr;
}

NSComparisonResult
ui::View::ViewImpl::viewSiblingViewsCmp(__strong id v1,
                                        __strong id v2,
                                        void * context) {

  CocoaView * _v1 = static_cast<CocoaView *>(v1);
  CocoaView * _v2 = static_cast<CocoaView *>(v2);

  if (_v1.zIndex > _v2.zIndex)
    return NSOrderedDescending;
  else if (_v1.zIndex < _v2.zIndex)
    return NSOrderedAscending;

  return NSOrderedSame;
}

void
ui::View::ViewImpl::bringSubviewToFront(View * view) {
  ViewImpl * viewImpl = view->m_impl;

  std::vector<View *>::iterator fountView_it =
  std::find(m_subviews->begin(),
            m_subviews->end(),
            view);

  if (fountView_it == m_subviews->end())
    return;

  // change z-order in vactor for next
  m_subviews->erase(fountView_it);
  m_subviews->push_back(view);

  for (int i = 0; i < m_subviews->size(); i++) {
    View * aView = m_subviews->at(i);
    aView->m_impl->setZIndex(i);
  }

  [m_view sortSubviewsUsingFunction: ViewImpl::viewSiblingViewsCmp
                            context: (void *)viewImpl];
}

void
ui::View::ViewImpl::sendSubviewToBack(View * view) {
  ViewImpl * viewImpl = view->m_impl;
//  viewImpl->setZIndex(0);

  std::vector<View *>::iterator fountView_it =
  std::find(m_subviews->begin(),
            m_subviews->end(),
            view);

  if (fountView_it == m_subviews->end())
    return;

  // change z-order in vactor for next
  m_subviews->erase(fountView_it);
  m_subviews->insert(m_subviews->begin(), view);

  for (int i = 0; i < m_subviews->size(); i++) {
    View * aView = m_subviews->at(i);
    aView->m_impl->setZIndex(i);
  }

  [m_view sortSubviewsUsingFunction: ViewImpl::viewSiblingViewsCmp
                            context: (void *)viewImpl];
}

int
ui::View::ViewImpl::zIndex() const {
  return m_zIndex;
}

void
ui::View::ViewImpl::setZIndex(int zIndex) {
  m_zIndex = zIndex;
  [m_view setZIndex: zIndex];
}

ui::View::ViewImpl::~ViewImpl() {
  m_subviews->clear();
  delete m_subviews;
  m_view = nil;
}
