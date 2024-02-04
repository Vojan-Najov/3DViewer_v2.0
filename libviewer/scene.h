#ifndef LIBVIEWER_SCENE_H_
#define LIBVIEWER_SCENE_H_

#include <memory>

#include "object.h"
#include "scene_settings.h"

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
  void SetObject(std::unique_ptr<Object<T, U>> &&obj);

 public:
  Object<T, U> &GetObject(void);
  const Object<T, U> &GetObject(void) const;
  Vertex<T> &GetCamera(void);
  const Vertex<T> &GetCamera(void) const;
  T GetCameraFocalRo(void) const;
  size_t GetVerticesNumber(void) const;
  size_t GetEdgesNumber(void) const;
  size_t GetFacesNumber(void) const;

 public:
  bool IsEmpty(void) const { return !object_; }

 private:
  Vertex<T> camera_{};
  std::unique_ptr<Object<T, U>> object_{nullptr};
};

template <typename T, typename U>
inline void Scene<T, U>::SetObject(std::unique_ptr<Object<T, U>> &&obj) {
  object_ = std::move(obj);
  if (object_) {
    object_->PrepareToRendering();
    camera_ = object_->Centre();
    camera_.z() += 2 * object_->Dimension();
  }
}

template <typename T, typename U>
inline Object<T, U> &Scene<T, U>::GetObject(void) {
  return *object_;
}

template <typename T, typename U>
inline const Object<T, U> &Scene<T, U>::GetObject(void) const {
  return *object_;
}

template <typename T, typename U>
inline Vertex<T> &Scene<T, U>::GetCamera(void) {
  return camera_;
}

template <typename T, typename U>
inline const Vertex<T> &Scene<T, U>::GetCamera(void) const {
  return camera_;
}

template <typename T, typename U>
inline T Scene<T, U>::GetCameraFocalRo(void) const {
  T dim = object_->Dimension();
  return dim > 1.0e-6f ? dim / 10 : 1;
  // return 1e-6;
}

template <typename T, typename U>
inline size_t Scene<T, U>::GetVerticesNumber(void) const {
  if (object_) {
    return object_->VerticesNumber();
  }
  return 0;
}

template <typename T, typename U>
inline size_t Scene<T, U>::GetEdgesNumber(void) const {
  if (object_) {
    return object_->EdgesNumber();
  }
  return 0;
}

template <typename T, typename U>
inline size_t Scene<T, U>::GetFacesNumber(void) const {
  if (object_) {
    return object_->FacesNumber();
  }
  return 0;
}

}  // namespace s21

#endif  // LIBVIEWER_SCENE_H_
