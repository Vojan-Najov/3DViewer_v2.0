#ifndef WIREFRAME_H_
#define WIREFRAME_H_

#include <iostream>
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
  size_t VerticesNumber(void) const override;

 public:
  void Transform(const Matrix4x4<T> &transform) override;

 private:
	std::vector<Vertex<T>> vertices_;
};

template <typename T>
inline Wireframe<T> &Wireframe<T>::PushBack(const Vertex<T> &v) {
	vertices_.push_back(v);
	return *this;
}

template <typename T>
inline void Wireframe<T>::Transform(const Matrix4x4<T> &m) {
	(void) m;
}

template <typename T>
inline size_t Wireframe<T>::VerticesNumber(void) const {
	return vertices_.size();
}

}  // namespace s21

#endif  // WIREFRAME_H_
