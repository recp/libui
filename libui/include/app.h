/*
 * Copyright (c), Recep Aslantas. All rights reserved.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

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
