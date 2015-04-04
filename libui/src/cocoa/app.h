/*
 * Copyright (c), Recep Aslantas. All rights reserved.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui_cocoa_app__
#define __libui_cocoa_app__

#ifdef __OBJC__
#import <Cocoa/Cocoa.h>
#endif

#include "../../include/window.h"

#ifdef __OBJC__
@interface CocoaApp : NSObject
- (void) run;
@end
#endif

namespace ui {
  
class AppImpl {
public:
  AppImpl();
  void run();
  void run(Window * rootWindow);

private:
#ifdef __OBJC__
  CocoaApp * m_app;
#endif
};

} // namespace ui

#endif /* defined (__libui__cocoa_app__) */