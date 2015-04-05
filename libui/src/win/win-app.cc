/*
 * Copyright (c), Recep Aslantas. All rights reserved.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../config.h"
#include "win-app.h"

ui::AppImpl::AppImpl() {

}

void ui::AppImpl::run() {
  MSG msg;
  // HACCEL hAccelTable;

  while (GetMessage(&msg, NULL, 0, 0)) {
   // if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   // }
  }
}

//void app::appimpl::run(window *rootwindow) {
//
//}