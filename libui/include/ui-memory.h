/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libui__memory__
#define __libui__memory__

#include "ui-base.h"

namespace ui {

class _libui_export Object {
public:
  Object();

  Object(const Object& other);
  Object& operator=(const Object& other);

  void retain();
  int  refCount() const;
  void release();

  ~Object();
protected:

  // Because of cloned objects must keeps the same refCount
  int * m_refCount;
};

} // namespace ui

#endif /* defined(__libui__memory__) */
