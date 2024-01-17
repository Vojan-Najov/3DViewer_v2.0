#ifndef LIBVIEWER_SCENE_H_
#define LIBVIEWER_SCENE_H_

#include <list>
#include <memory>

#include "scene_object.h"

namespace s21 {

template <typename T, typename U>
class Scene final {
 public:
  void AddObject(SceneObject<T, U> *so);
  const SceneObject<T, U> &GetObject(void) const;

 private:
  std::list<std::unique_ptr<SceneObject<T, U>>> objlst_;

  // Camera<T> camera_;
  // Model<T> *model_;
  // Settings settings_; it is singleton
};

template <typename T, typename U>
void Scene<T, U>::AddObject(SceneObject<T, U> *so) {
  objlst_.emplace_back(so);
}

template <typename T, typename U>
const SceneObject<T, U> &Scene<T, U>::GetObject(void) const {
  return *(objlst_.front());
}

}  // namespace s21

#endif  // LIBVIEWER_SCENE_H_
