//
//  app.m
//  libui-test
//
//  Created by Recep ASLANTAS on 3/24/15.
//  Copyright (c) 2015 Recep ASLANTAS. All rights reserved.
//

#import "app.h"

@implementation CocoaApp

- (void)run {
  
  [NSApplication sharedApplication];
  [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
  
  id menubar = [NSMenu new];
  id appMenuItem = [NSMenuItem new];
  [menubar addItem:appMenuItem];
  [NSApp setMainMenu:menubar];
  
  id appMenu = [NSMenu new];
  id appName = [[NSProcessInfo processInfo] processName];
  id quitTitle = [@"Quit " stringByAppendingString:appName];
  id quitMenuItem = [[NSMenuItem alloc] initWithTitle:quitTitle
                                               action:@selector(terminate:) keyEquivalent:@"q"];
  [appMenu addItem:quitMenuItem];
  [appMenuItem setSubmenu:appMenu];
//  
//  id window = [[NSWindow alloc] initWithContentRect: NSMakeRect(300, 300, 200, 100)
//                                         styleMask: (NSTitledWindowMask |
//                                                     NSMiniaturizableWindowMask |
//                                                     NSResizableWindowMask)
//                                           backing: NSBackingStoreBuffered
//                                             defer: YES];
//  ;
////  [window cascadeTopLeftFromPoint:NSMakePoint(20,20)];
//  [window setTitle:appName];
//  [window makeKeyAndOrderFront:nil];
  
  [NSApp activateIgnoringOtherApps: NO];
  [NSApp run];


}

@end

//void app_run() {
//  [NSApplication sharedApplication];
//  [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
//  
//  id menubar = [NSMenu new];
//  id appMenuItem = [NSMenuItem new];
//  [menubar addItem:appMenuItem];
//  [NSApp setMainMenu:menubar];
//  
//  id appMenu = [NSMenu new];
//  id appName = [[NSProcessInfo processInfo] processName];
//  id quitTitle = [@"Quit " stringByAppendingString:appName];
//  id quitMenuItem = [[NSMenuItem alloc] initWithTitle:quitTitle
//                                               action:@selector(terminate:) keyEquivalent:@"q"];
//  [appMenu addItem:quitMenuItem];
//  [appMenuItem setSubmenu:appMenu];
//  
//  id window = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 200, 200)
//                                          styleMask:NSTitledWindowMask backing:NSBackingStoreBuffered defer:NO]
//  ;
//  [window cascadeTopLeftFromPoint:NSMakePoint(20,20)];
//  [window setTitle:appName];
//  [window makeKeyAndOrderFront:nil];
//  
//  [NSApp activateIgnoringOtherApps: NO];
//  [NSApp run];
//  
//}

namespace app = ui;

app::AppImpl::AppImpl() {
  id cocoaApp = [[CocoaApp alloc] init];
  m_app = cocoaApp;
}

void app::AppImpl::run() {
  [m_app run];
}

void app::AppImpl::run(Window *rootWindow) {
  
}
