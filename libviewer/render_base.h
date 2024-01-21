#ifndef LIBVIEWER_RENDER_BASE_H_
#define LIBVIEWER_RENDER_BASE_H_

#include "scene.h"

namespace s21 {

template <typename T, typename U>
class RenderBase {
 public:
  virtual void Initialize(void) = 0;
  virtual void DrawEmptyScene(void) = 0;
  virtual void DrawScene(Scene<T, U> &scene, int width, int height) = 0;
  virtual void ResizeViewport(int width, int height) = 0;
  virtual ~RenderBase(void){};
};

}  // namespace s21

#endif  // LIBVIEWER_RENDER_BASE_H_
