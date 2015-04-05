/*
* Copyright (c), Recep Aslantas. All rights reserved.
*
* MIT License (MIT), http://opensource.org/licenses/MIT
* Full license can be found in the LICENSE file
*/

#ifndef __libui__types__
#define __libui__types__

#ifdef __APPLE__
# define _libui_export  
#elif defined(_WIN32)
# ifdef _libui_dll
#   define _libui_export __declspec(dllexport)
# else
#   define _libui_export __declspec(dllimport)
# endif
#endif

#endif /* defined(__libui__types__) */