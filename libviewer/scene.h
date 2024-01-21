#ifndef LIBVIEWER_SCENE_H_
#define LIBVIEWER_SCENE_H_

#include <memory>

#include "figure.h"

namespace s21 {

template <typename T, typename U>
class Scene final {
 public:
  void AddFigure(Figure<T, U> *so);
  Figure<T, U> &GetFigure(void);
  const Figure<T, U> &GetFigure(void) const;

 public:
  size_t GetVerticesNumber(void) const;
  size_t GetEdgesNumber(void) const;
  size_t GetFacesNumber(void) const;

 public:
  bool IsEmpty(void) const { return !figure_; }

 private:
  std::unique_ptr<Figure<T, U>> figure_{nullptr};

  // Camera<T> camera_;
  // Settings settings_; it is singleton
};

template <typename T, typename U>
inline void Scene<T, U>::AddFigure(Figure<T, U> *so) {
  figure_ = std::unique_ptr<Figure<T, U>>(so);
}

template <typename T, typename U>
inline Figure<T, U> &Scene<T, U>::GetFigure(void) {
  return *figure_;
}

template <typename T, typename U>
inline const Figure<T, U> &Scene<T, U>::GetFigure(void) const {
  return *figure_;
}

template <typename T, typename U>
inline size_t Scene<T, U>::GetVerticesNumber(void) const {
  return figure_->VerticesNumber();
}

template <typename T, typename U>
inline size_t Scene<T, U>::GetEdgesNumber(void) const {
  return figure_->EdgesNumber();
}

template <typename T, typename U>
inline size_t Scene<T, U>::GetFacesNumber(void) const {
  return figure_->FacesNumber();
}

}  // namespace s21

#endif  // LIBVIEWER_SCENE_H_
