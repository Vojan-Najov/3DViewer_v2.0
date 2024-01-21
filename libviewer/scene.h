#ifndef LIBVIEWER_SCENE_H_
#define LIBVIEWER_SCENE_H_

#include <memory>

#include "figure.h"

namespace s21 {

template <typename T, typename U>
class Scene final {
 public:
  Scene(void) = default;
  Scene(const Scene &other) = delete;
  Scene(Scene &&other) = default;
  Scene &operator=(const Scene &other) = delete;
  Scene &operator=(Scene &&other) = default;
  ~Scene(void) = default;

 public:
  void AddFigure(Figure<T, U> *so);
  void Init(void);

 public:
  Figure<T, U> &GetFigure(void);
  const Figure<T, U> &GetFigure(void) const;
  Vertex<T> GetCamera(void) const;
  T GetCameraFocalRo(void) const;
  size_t GetVerticesNumber(void) const;
  size_t GetEdgesNumber(void) const;
  size_t GetFacesNumber(void) const;

 public:
  bool IsEmpty(void) const { return !figure_; }

 private:
  Vertex<T> camera_;
  std::unique_ptr<Figure<T, U>> figure_{nullptr};

  // Settings settings_; it is singleton
};

template <typename T, typename U>
inline void Scene<T, U>::AddFigure(Figure<T, U> *so) {
  figure_ = std::unique_ptr<Figure<T, U>>(so);
}

template <typename T, typename U>
inline void Scene<T, U>::Init(void) {
  if (figure_) {
    figure_->CalculateCentre();
    figure_->CalculateDimension();
    camera_ = figure_->GetCentre();
    camera_.z() += 2 * figure_->GetDimension();
  }
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
inline Vertex<T> Scene<T, U>::GetCamera(void) const {
  return camera_;
}

template <typename T, typename U>
inline T Scene<T, U>::GetCameraFocalRo(void) const {
  T dim = figure_->GetDimension();
  return dim > 1.0e-6f ? dim / 10 : 1;
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
