/*
* Copyright (c), Recep Aslantas. All rights reserved.
*
* MIT License (MIT), http://opensource.org/licenses/MIT
* Full license can be found in the LICENSE file
*/

#ifndef __libui__types__
#define __libui__types__

/*
  The _libui_dll macro should not be defined in the client programs. 
  This is for exporting symbols for dynamic [link] library  
 */
#ifdef __APPLE__
# define _libui_export  
#elif defined(_WIN32)
# ifdef _libui_dll
#   define _libui_export __declspec(dllexport)
# else
#   define _libui_export __declspec(dllimport)
# endif
#endif

#ifndef _libui_skip_crt_entry
# if defined(_WIN32) && defined(_MSC_VER)
#   pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
# endif
#endif

#endif /* defined(__libui__types__) */