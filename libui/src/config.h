/*
 * Copyright (c), Recep Aslantas. All rights reserved.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../include/types.h"

#if defined(_WIN32) || defined(WIN32)
# define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
# include <SDKDDKVer.h>
#endif