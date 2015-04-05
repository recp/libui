/*
 * Copyright (c), Recep Aslantas. All rights reserved.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui__app__
#define __libui__app__

#include "types.h"
#include "ui-window.h"

namespace ui {

class _libui_export App {
public:
  App();
  void run();
  void run(Window * rootWindow);
private:
  class AppImpl * m_impl;
};

} // namespace ui

#endif /* defined(__libui__app__) */
