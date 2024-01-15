#ifndef LIBVIEWER_SCENE_OBJECT_H_
#define LIBVIEWER_SCENE_OBJECT_H_

#include "matrix4x4.h"

namespace s21 {

template <typename T>
class SceneObject {
 public:
  virtual void Transform(const Matrix4x4<T> &m) = 0;
  virtual ~SceneObject(void) {}
};

}  // namespace s21

#endif  // LIBVIEWER_SCENE_OBJECT_H_
