#ifndef WIREFRAME_H_
#define WIREFRAME_H_

#include <vector>

#include "scene_object.h"
#include "vertex.h"
#include "matrix4x4.h"

namespace s21 {

template <typename T>
class Wireframe : public SceneObject<T> {
 public:
	Wireframe(void) = default;
	Wireframe(const Wireframe &other) = default;
	Wireframe(Wireframe &&other) = default;
	Wireframe &operator=(const Wireframe &other) = default;
	Wireframe &operator=(Wireframe &&other) = default;
  ~Wireframe(void) {}

 public:
  Wireframe &PushBack(const Vertex<T> &v);

 public:
  void Transform(const Matrix4x4<T> &transform) override;

 private:
	std::vector<Vertex<T>> verteces_;
};

template <typename T>
inline Wireframe<T> &Wireframe<T>::PushBack(const Vertex<T> &v) {
	verteces_.push_back(v);
	return *this;
}

template <typename T>
inline void Wireframe<T>::Transform(const Matrix4x4<T> &m) {
	(void) m;
}

}  // namespace s21

#endif  // WIREFRAME_H_
