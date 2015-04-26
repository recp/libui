/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../config.h"
#include "win-app.h"

ui::AppImpl::AppImpl() {

}

void 
ui::AppImpl::run() {
  MSG msg;

  /*
     TODO:
     https://msdn.microsoft.com/en-us/library/windows/desktop/ms646373(v=vs.85).aspx
   */
  // HACCEL hAccelTable;
  // static LPCTSTR lpTableName = L"ui_app_accel_tbl";
  // hAccelTable = LoadAccelerators(hInstance, lpTableName);
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