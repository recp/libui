/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "menu-item.h"
#include "menu.h"

@implementation CocoaMenuItem

- (void)customAction: (id)sender {
  (*m_pMenuAction)(m_menuItem);
}

- (id)target {
  return self;
}

- (void)dealloc {
  m_menuItem = nil;
  m_pMenuAction = nil;
}

@end

ui::MenuItem::MenuItemImpl::MenuItemImpl(MenuItem * _self) {
  m_cocoaMenuItem = [[CocoaMenuItem alloc] init];
  m_cocoaMenuItem->m_menuItem = _self;
  m_self = _self;
}

ui::MenuItem::MenuItemImpl::MenuItemImpl(MenuItem * _self, CStringPtr title) {
  m_title = title;

  NSString * _nsTitle = [NSString stringWithCString: title
                                           encoding: NSUTF8StringEncoding];

  m_cocoaMenuItem = [[CocoaMenuItem alloc] initWithTitle: _nsTitle
                                                  action: nil
                                           keyEquivalent: @""];

  m_cocoaMenuItem->m_menuItem = _self;
  m_self = _self;
}

ui::MenuItem::MenuItemImpl::MenuItemImpl(MenuItem * _self,
                                         MenuItemAction action) {
  m_menuItemAction = action;

  m_cocoaMenuItem = [[CocoaMenuItem alloc] init];

  m_cocoaMenuItem->m_menuItem = _self;
  m_cocoaMenuItem->m_pMenuAction = &m_menuItemAction;
  [m_cocoaMenuItem setAction: @selector(customAction:)];

  m_self = _self;
}

ui::MenuItem::MenuItemImpl::MenuItemImpl(MenuItem * _self,
                                         CStringPtr title,
                                         MenuItemAction action) {
  m_title = title;
  m_menuItemAction = action;

  NSString * _nsTitle = [NSString stringWithCString: title
                                           encoding: NSUTF8StringEncoding];

  m_cocoaMenuItem = [[CocoaMenuItem alloc] initWithTitle: _nsTitle
                                                  action: nil
                                           keyEquivalent: @""];

  m_cocoaMenuItem->m_menuItem = _self;
  m_cocoaMenuItem->m_pMenuAction = &m_menuItemAction;
  [m_cocoaMenuItem setAction: @selector(customAction:)];

  m_self = _self;
}

ui::CStringPtr
ui::MenuItem::MenuItemImpl::title() const {
  return m_title;
}

void
ui::MenuItem::MenuItemImpl::title(CStringPtr title) {
  m_title = title;

  NSString * _nsTitle = [NSString stringWithCString: title
                                           encoding: NSUTF8StringEncoding];
  [m_cocoaMenuItem setTitle: _nsTitle];
}

ui::Image
ui::MenuItem::MenuItemImpl::image() const {
  return m_image;
}

void
ui::MenuItem::MenuItemImpl::image(Image image) {
  m_image = image;
  // TODO:
}

bool
ui::MenuItem::MenuItemImpl::highlighted() const {
  return m_highlighted;
}

void
ui::MenuItem::MenuItemImpl::highlighted(bool highlighted) {
  m_highlighted = highlighted;
  // TODO:
}

bool
ui::MenuItem::MenuItemImpl::enabled() const {
  return m_enabled;
}

void
ui::MenuItem::MenuItemImpl::enabled(bool enabled) {
  m_enabled = enabled;
  [m_cocoaMenuItem setEnabled: enabled];
}

ui::Menu *
ui::MenuItem::MenuItemImpl::menu() const {
  return m_menu;
}

ui::Menu *
ui::MenuItem::MenuItemImpl::subMenu() const {
  return m_subMenu;
}

void
ui::MenuItem::MenuItemImpl::subMenu(Menu * menu) {
  m_subMenu = menu;
  [m_cocoaMenuItem setSubmenu: menu->m_impl->m_cocoaMenu];
}

ui::CStringPtr
ui::MenuItem::MenuItemImpl::keyEquivalent() const {
  return m_keyEquivalent;
}

void
ui::MenuItem::MenuItemImpl::keyEquivalent(CStringPtr keyEquivalent) {
  m_keyEquivalent = keyEquivalent;

  if (!keyEquivalent)
    m_keyEquivalent = "";

  NSString * _nsKeyEq = [NSString stringWithCString: m_keyEquivalent
                                           encoding: NSUTF8StringEncoding];

  [m_cocoaMenuItem setKeyEquivalent: _nsKeyEq];
}

void
ui::MenuItem::MenuItemImpl::setAction(MenuItemAction action) {
  m_menuItemAction = action;
  m_cocoaMenuItem->m_pMenuAction = &m_menuItemAction;
  [m_cocoaMenuItem setAction: @selector(customAction:)];
}

ui::MenuItem::MenuItemImpl::~MenuItemImpl() {
  m_cocoaMenuItem = nil;
}
