
TODO:

- [ ] Basic implementation of window/view
    - [x] Cocoa (app, window, view, menu)
    - [x] Win32 (app, window, view)
    - [ ] WinRT
    - [ ] GTK
    - [ ] Qt ?
- [ ] Memory management
- [ ] Mouse / Touch events
- [ ] Add ability to inheritance
- [ ] Layered View/Window (maybe it must always be layered?)
  - [ ] Direct2D for win32/winrt
  - [ ] CoreAnimation (CALayer...) for cocoa
  - [ ] !!
- [ ] Multi-thread support
- [ ] 2D Graphics drawing
  - [ ] Cairo?
  - [ ] Direct2D for win32
  - [ ] Quartz2D for cocoa
  - [ ] !!
- [ ] 3D Graphics support
  - [ ] OpenGL
  - [ ] DirectX
  - [ ] Metal
  - [ ] Vulkan
  - [ ] Vendor provided tech optimizations (Nvidia/AMD; Cuda/OptiX, Mantle..)
  - [ ] !!
- [ ] Basic built-in controls
  - [ ] Button
  - [ ] Context Menu
  - [ ] Grid View
  - [ ] !!
- [ ] Build 
  - [ ] Autotools for Unix-like systems
  - [ ] MSBuild for Windows (MS VC++)
  - [ ] MinGW for Win? or GYP Even MSBuild?
- [ ] Test

C++ STL (libc++) vs NSPR vs libuv vs C way (libc, POSIX facilities..) for thread, files, sock/pipe/fifo...
