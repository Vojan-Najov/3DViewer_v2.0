#ifndef LIBVIEWER_SCENE_H_
#define LIBVIEWER_SCENE_H_

#include <list>

#include "scene_object.h"

namespace s21 {

template <typename T>
class Scene final {
 public:
  void AddObject(SceneObject<T> *so);
	const SceneObject<T> &GetObject(void) const;

 private:
	std::list<std::unique_ptr<SceneObject<T>>> objlst_;
	
  // Camera<T> camera_;
  // Model<T> *model_;
  // Settings settings_; it is singleton
};

template <typename T>
void Scene<T>::AddObject(SceneObject<T> *so) {
	objlst_.emplace_back(so);
}

template <typename T>
const SceneObject<T> & Scene<T>::GetObject(void) const {
	return *(objlst_.front());
}

}  // namespace s21

#endif  // LIBVIEWER_SCENE_H_
