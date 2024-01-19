#ifndef FIGURE_H_
#define FIGURE_H_

#include <iostream>
#include <vector>

#include "face.h"
#include "matrix4x4.h"
#include "vertex.h"

namespace s21 {

template <typename T, typename U = int>
class Figure {
 public:
  Figure(void) = default;
  Figure(const Figure &other) = default;
  Figure(Figure &&other) = default;
  Figure &operator=(const Figure &other) = default;
  Figure &operator=(Figure &&other) = default;
  ~Figure(void) {}

 public:
  Figure &PushBack(const Vertex<T> &v);
  Figure &PushBack(const Face<U> &f);

 public:
  const std::vector<Vertex<T>> &GetVertices(void) const { return vertices_; }

 public:
  size_t VerticesNumber(void) const;
  size_t EdgesNumber(void) const;
  size_t FacesNumber(void) const;

 public:
  void Transform(const Matrix4x4<T> &transform);

 private:
  std::vector<Vertex<T>> vertices_;
  std::vector<Face<U>> faces_;
};

template <typename T, typename U>
inline Figure<T, U> &Figure<T, U>::PushBack(const Vertex<T> &v) {
  vertices_.push_back(v);
  return *this;
}

template <typename T, typename U>
inline Figure<T, U> &Figure<T, U>::PushBack(const Face<U> &f) {
  faces_.push_back(f);
  return *this;
}

template <typename T, typename U>
inline void Figure<T, U>::Transform(const Matrix4x4<T> &m) {
  (void)m;
}

template <typename T, typename U>
inline size_t Figure<T, U>::VerticesNumber(void) const {
  return vertices_.size();
}

template <typename T, typename U>
inline size_t Figure<T, U>::EdgesNumber(void) const {
  // todo
  return faces_.size();
}

template <typename T, typename U>
inline size_t Figure<T, U>::FacesNumber(void) const {
  return faces_.size();
}

}  // namespace s21

#endif  // FIGURE_H_
