/*
* Copyright (c), Recep Aslantas. All rights reserved.
*
* MIT License (MIT), http://opensource.org/licenses/MIT
* Full license can be found in the LICENSE file
*/

#ifndef __libui_debug_logutils__
#define __libui_debug_logutils__

#include "../config.h"

namespace ui {
namespace debug {

void log(CStringPtr format, ...);
void logt(CStringPtr tag, CStringPtr format, ...);

} // namespace debug
} // namespace ui

#endif /* defined(__libui_debug_logutils__) */