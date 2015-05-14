/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui__cocoa__view__
#define __libui__cocoa__view__

#include "../../../include/ui-geometry.h"
#include "../../../include/ui-view.h"
#include "../../../include/ui-color.h"

#ifdef __OBJC__
#import <Cocoa/Cocoa.h>
#else
#include <objc/runtime.h>
#endif

#include <vector>

#ifndef __OBJC__
typedef objc_object CocoaView;
#endif

#ifdef __OBJC__
@interface CocoaView : NSView
@end
#endif

namespace ui {
  
class View::ViewImpl {
public:
  ViewImpl(View * _self, Rect rect);
  
  Color backgroundColor() const;
  void setBackgroundColor(Color color) const;
  
  Rect getFrame() const;
  void setFrame(Rect frame) const;

  bool isInputEnabled() const;
  void setInputEnabled(bool enabled);

  const View * superview() const;
  const Window * window() const;

  std::vector<View *> * subviews() const;
  void addSubview(View * subview);
  void removeFromSuperview();
  
  ~ViewImpl();
private:
  bool m_inputEnabled;
  Rect m_frame;
  Color m_bgcolor;
  CocoaView * m_view;
  std::vector<View *> * m_subviews;
  View * m_superview;
  Window * m_wnd;

  const View * m_self;
  friend class Window;
  friend class View;
};
  
} // namespace ui

#endif /* defined(__libui__cocoa__view__) */
