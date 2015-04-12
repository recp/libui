/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui__types__
#define __libui__types__

typedef const char * CStringPtr;
typedef char * CMutStringPtr;

/*
  The _libui_dll macro should not be defined in the client programs. 
  This is for exporting symbols for dynamic [link] library  
 */
#ifdef __APPLE__
#  define _libui_export __attribute__((visibility("default")))
#elif defined(_WIN32)
#  ifdef _libui_dll
#    define _libui_export __declspec(dllexport)
#  else
#    define _libui_export __declspec(dllimport)
#  endif
#endif

/*
 Enable standart C/C++ entry point 
  
 When client program include this header then the WinMain wont be called as 
 program entry.

 If client progams really need to use WinMain/_tWinMain... then define 
 this maco before including ui-base.h like this:
 
 #define _libui_skip_crt_entry
 #include "app.h" // app.h has already included ui-base.h
 */
#ifndef _libui_skip_crt_entry
# if defined(_WIN32) && defined(_MSC_VER)
#   pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
# endif
#endif

#endif /* defined(__libui__types__) */