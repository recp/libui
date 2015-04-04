//
//  app.h
//  libui-test
//
//  Created by Recep ASLANTAS on 3/24/15.
//  Copyright (c) 2015 Recep ASLANTAS. All rights reserved.
//

#ifndef __libui__app__
#define __libui__app__

#include "window.h"

namespace ui {
  
class App {
public:
  App();
  void run();
  void run(Window * rootWindow);
private:
  class AppImpl * m_impl;
};

} // namespace ui

#endif /* defined(__libui__app__) */
