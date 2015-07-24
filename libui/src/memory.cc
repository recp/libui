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

ui::Object::Object(const Object& other) {
  m_refCount = other.m_refCount;
}

ui::Object&
ui::Object::Object::operator=(const Object& other) {
  if (this != &other)
    m_refCount = other.m_refCount;

  return *this;
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
