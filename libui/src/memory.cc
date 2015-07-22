/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../include/ui-memory.h"

ui::Object::Object() {
  m_refCount = new int(1);
}

void
ui::Object::retain() {
  (*m_refCount)++;
}

int
ui::Object::refCount() const {
  return *m_refCount;
}

void
ui::Object::release() {
  (*m_refCount)--;
}

ui::Object::~Object() {
  if (*m_refCount <= 0)
    delete m_refCount;
}
