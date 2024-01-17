#ifndef LIBVIEWER_SCENE_H_
#define LIBVIEWER_SCENE_H_

#include <memory>

#include "figure.h"

namespace s21 {

template <typename T, typename U>
class Scene final {
 public:
  void AddFigure(Figure<T, U> *so);
  const Figure<T, U> &GetFigure(void) const;

 private:
  std::unique_ptr<Figure<T, U>> figure_;

  // Camera<T> camera_;
  // Settings settings_; it is singleton
};

template <typename T, typename U>
void Scene<T, U>::AddFigure(Figure<T, U> *so) {
  figure_ = std::unique_ptr<Figure<T, U>>(so);
}

template <typename T, typename U>
const Figure<T, U> &Scene<T, U>::GetFigure(void) const {
  return *figure_;
}

}  // namespace s21

#endif  // LIBVIEWER_SCENE_H_
