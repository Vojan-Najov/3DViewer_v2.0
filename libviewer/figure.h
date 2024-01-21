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
  Vertex<T> GetCentre(void) const;
  T GetDimension(void) const;
  const std::vector<Vertex<T>> &GetVertices(void) const { return vertices_; }
  const std::vector<Face<U>> &GetFaces(void) const { return faces_; }

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

template <typename T, typename U>
inline Vertex<T> Figure<T, U>::GetCentre(void) const {
  T x{0}, y{0}, z{0};
  size_t n = vertices_.size();

  using vit = typename std::vector<Vertex<T>>::const_iterator;
  for (vit it = vertices_.begin(), last = vertices_.end(); it != last; ++it) {
    x += it->x();
    y += it->y();
    z += it->z();
  }
  x /= (float)n;
  y /= (float)n;
  z /= (float)n;

  return Vertex<T>{x, y, z};
}

template <typename T, typename U>
inline T Figure<T, U>::GetDimension(void) const {
  T dim{0};
  Vertex<T> centre = GetCentre();
  using vit = typename std::vector<Vertex<T>>::const_iterator;
  for (vit it = vertices_.begin(), last = vertices_.end(); it != last; ++it) {
    T tmp = std::sqrt(std::pow(it->x() - centre.x(), 2) +
                      std::pow(it->y() - centre.y(), 2) +
                      std::pow(it->z() - centre.z(), 2));
    if (tmp > dim) {
      dim = tmp;
    }
  }
  if (dim < 1.0e-6f) {
    dim = 1;
  }

  return dim;
}

}  // namespace s21

#endif  // FIGURE_H_
