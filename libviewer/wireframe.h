#ifndef WIREFRAME_H_
#define WIREFRAME_H_

#include <iostream>
#include <vector>

#include "scene_object.h"
#include "vertex.h"
#include "face.h"
#include "matrix4x4.h"

namespace s21 {

template <typename T, typename U = int>
class Wireframe : public SceneObject<T, U> {
 public:
	Wireframe(void) = default;
	Wireframe(const Wireframe &other) = default;
	Wireframe(Wireframe &&other) = default;
	Wireframe &operator=(const Wireframe &other) = default;
	Wireframe &operator=(Wireframe &&other) = default;
  ~Wireframe(void) {}

 public:
  Wireframe &PushBack(const Vertex<T> &v);
  Wireframe &PushBack(const Face<U> &f);

 public:
  size_t VerticesNumber(void) const override;
  size_t FacesNumber(void) const override;

 public:
  void Transform(const Matrix4x4<T> &transform) override;

 private:
	std::vector<Vertex<T>> vertices_;
	std::vector<Face<U>> faces_;
};

template <typename T, typename U>
inline Wireframe<T,U> &Wireframe<T,U>::PushBack(const Vertex<T> &v) {
	vertices_.push_back(v);
	return *this;
}

template <typename T, typename U>
inline Wireframe<T,U> &Wireframe<T,U>::PushBack(const Face<U> &f) {
	faces_.push_back(f);
	return *this;
}

template <typename T, typename U>
inline void Wireframe<T,U>::Transform(const Matrix4x4<T> &m) {
	(void) m;
}

template <typename T, typename U>
inline size_t Wireframe<T,U>::VerticesNumber(void) const {
	return vertices_.size();
}

template <typename T, typename U>
inline size_t Wireframe<T,U>::FacesNumber(void) const {
	return faces_.size();
}

}  // namespace s21

#endif  // WIREFRAME_H_
