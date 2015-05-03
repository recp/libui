/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui_win_utils__
#define __libui_win_utils__

#include "../config.h"
#include "../../include/ui-window.h"

namespace ui {

HWND defaultFakeWindow();
DWORD translateWndStyleToWin32WS(int style);

} // namespace ui

#endif /* defined(__libui_win_utils__) */