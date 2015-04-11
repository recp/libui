/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

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
                                               action:@selector(terminate:)
                                        keyEquivalent:@"q"];
  [appMenu addItem:quitMenuItem];
  [appMenuItem setSubmenu:appMenu];

  [NSApp activateIgnoringOtherApps: NO];
  [NSApp run];
}

@end

ui::AppImpl::AppImpl() {
  id cocoaApp = [[CocoaApp alloc] init];
  m_app = cocoaApp;
}

void ui::AppImpl::run() {
  [m_app run];
}

void ui::AppImpl::run(Window *rootWindow) {

}
