/*
 * Copyright (c), Recep Aslantas. All rights reserved.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../include/ui-base.h"

#if defined(_WIN32) || defined(WIN32)

// Exclude rarely-used stuff from Windows headers
# define WIN32_LEAN_AND_MEAN 
# include <SDKDDKVer.h>

// Windows Header Files:
# include <windows.h>

// C RunTime Header Files
# include <stdlib.h>
# include <malloc.h>
# include <memory.h>
# include <tchar.h>

#endif