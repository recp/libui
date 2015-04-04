//
//  app.h
//  libui-test
//
//  Created by Recep ASLANTAS on 3/24/15.
//  Copyright (c) 2015 Recep ASLANTAS. All rights reserved.
//

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