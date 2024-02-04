#ifndef LIBVIEWER_OBJECT_H_
#define LIBVIEWER_OBJECT_H_

#include <iostream>
#include <string>
#include <vector>

#include "face.h"
#include "vertex.h"

namespace s21 {

template <typename T, typename U>
class Object {
 public:
  using Vertices = std::vector<Vertex<T>>;
  using VertexIterator = typename std::vector<Vertex<T>>::iterator;
  using VertexConstIterator = typename std::vector<Vertex<T>>::const_iterator;
  using EdgeIterator = typename std::vector<U>::iterator;
  using EdgeConstIterator = typename std::vector<U>::const_iterator;

 public:
  Object(void);
  Object(const Object &o) = delete;
  Object(Object &&o) = default;
  Object &operator=(const Object &o) = delete;
  Object &operator=(Object &&o) = delete;
  ~Object(void) = default;

 public:
  Object<T, U> &PushBack(const Vertex<T> &v);
  Object<T, U> &PushBack(Vertex<T> &&v);
  Object<T, U> &PushBack(const Face<int> &f);
  Object &Transform(const Matrix4x4<T> &mtrx);
  void PrepareToRendering(void);

 public:
  const std::vector<Vertex<T>> &GetVertices(void) const { return vertices_; }
  const std::vector<U> &GetEdges(void) const { return edges_; }

 public:
  Vertex<T> Centre(void) const { return centre_; }
  T Dimension(void) const { return (dimension_ - centre_).length(); }
  size_t VerticesNumber(void) const { return vertices_.size(); }
  size_t EdgesNumber(void) const { return edges_.size() / 2; }
  size_t FacesNumber(void) const { return faces_number_; }

 private:
  void CalculateCentre(void);
  void CalculateDimension(void);
  U ToVertexIndex(int index) const;

 private:
  Vertex<T> centre_;
  Vertex<T> dimension_;
  size_t faces_number_;
  std::vector<Vertex<T>> vertices_;
  std::vector<U> edges_;
};

template <typename T, typename U>
Object<T, U>::Object(void) : faces_number_{0} {
  vertices_.reserve(1024 * 1024);
  edges_.reserve(1024 * 1024);
}

template <typename T, typename U>
inline Object<T, U> &Object<T, U>::PushBack(const Vertex<T> &v) {
  vertices_.push_back(v);
  return *this;
}

template <typename T, typename U>
inline Object<T, U> &Object<T, U>::PushBack(Vertex<T> &&v) {
  vertices_.push_back(std::forward<Vertex<T>>(v));
  return *this;
}

template <typename T, typename U>
inline Object<T, U> &Object<T, U>::PushBack(const Face<int> &f) {
  if (f.Size() < 2) {
    return *this;
  }

  Face<int>::ConstIterator it = f.Begin();
  Face<int>::ConstIterator last = f.End();
  edges_.push_back(ToVertexIndex(*it));
  for (++it; it != last; ++it) {
    edges_.push_back(ToVertexIndex(*it));
    edges_.push_back(ToVertexIndex(*it));
  }
  edges_.push_back(ToVertexIndex(*f.Begin()));
  ++faces_number_;

  return *this;
}

template <typename T, typename U>
inline Object<T, U> &Object<T, U>::Transform(const Matrix4x4<T> &mtrx) {
  typename std::vector<Vertex<T>>::iterator it = vertices_.begin();
  typename std::vector<Vertex<T>>::iterator last = vertices_.end();
  for (; it != last; ++it) {
    it->Transform(mtrx);
  }
  centre_.Transform(mtrx);
  dimension_.Transform(mtrx);
  return *this;
}

template <typename T, typename U>
inline void Object<T, U>::PrepareToRendering(void) {
  CalculateCentre();
  CalculateDimension();
}

template <typename T, typename U>
inline void Object<T, U>::CalculateCentre(void) {
  T x{0}, y{0}, z{0};
  size_t n = VerticesNumber();

  VertexConstIterator vit = vertices_.begin();
  VertexConstIterator vlast = vertices_.end();
  for (; vit != vlast; ++vit) {
    x += vit->x();
    y += vit->y();
    z += vit->z();
  }
  x /= static_cast<T>(n);
  y /= static_cast<T>(n);
  z /= static_cast<T>(n);

  centre_[0] = x;
  centre_[1] = y;
  centre_[2] = z;
}

template <typename T, typename U>
inline void Object<T, U>::CalculateDimension(void) {
  T dim{0};

  dimension_ = centre_;
  VertexConstIterator vit = vertices_.begin();
  VertexConstIterator vlast = vertices_.end();
  for (; vit != vlast; ++vit) {
    T length = (*vit - centre_).length();
    if (length > dim) {
      dimension_ = *vit;
      dim = length;
    }
  }
}

template <typename T, typename U>
inline U Object<T, U>::ToVertexIndex(int index) const {
  int idx{0};
  size_t vsize = static_cast<U>(vertices_.size());

  if (index > 0) {
    idx = index - 1;
  } else if (index < 0 && size_t(-index) <= vsize) {
    idx = vsize + index;
  }

  return idx;
}

}  // namespace s21

#endif  // LIBVIEWER_OBJECT_H_
