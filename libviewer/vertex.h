#ifndef LIBVIEWER_VERTEX_H_
#define LIBVIEWER_VERTEX_H_

#include <istream>

#include "matrix4x4.h"
#include "vec4.h"

namespace s21 {

template <typename T>
class Vertex {
 public:
  Vertex(void) = default;
  Vertex(const Vec4<T> &vec) : vec_{vec} {}
  Vertex(const T &x, const T &y, const T &z, const T &w = T{1})
      : vec_{x, y, z, w} {}
  Vertex(const Vertex &v) = default;
  Vertex(Vertex &&v) = default;
  Vertex &operator=(const Vertex &v) = default;
  Vertex &operator=(Vertex &&v) = default;
  ~Vertex(void) = default;

 public:
  T &x(void) { return vec_.x(); }
  const T &x(void) const { return vec_.x(); }
  T &y(void) { return vec_.y(); }
  const T &y(void) const { return vec_.y(); }
  T &z(void) { return vec_.z(); }
  const T &z(void) const { return vec_.z(); }
  T &w(void) { return vec_.w(); }
  const T &w(void) const { return vec_.w(); }

 public:
  T &operator[](size_t idx) { return vec_[idx]; }
  const T &operator[](size_t idx) const { return vec_[idx]; }
  Vertex operator+(const Vec4<T> &vec) const { return vec_ + vec; }
  Vertex &operator+=(const Vec4<T> &vec) {
    vec_ += vec;
    return *this;
  }
  Vec4<T> operator-(const Vertex &v) const { return vec_ - v.vec_; }
  Vertex operator-(const Vec4<T> &vec) const { return vec_ - vec; }
  Vertex &operator-=(const Vec4<T> &vec) {
    vec_ -= vec;
    return *this;
  }
  Vertex operator*(const T &sclr) const { return vec_ * sclr; }
  Vertex &operator*=(const T &sclr) {
    vec_ *= sclr;
    return *this;
  }

 public:
  Vertex &Transform(const Matrix4x4<T> &mtrx) {
    vec_ = mtrx * vec_;
    return *this;
  }

 private:
  Vec4<T> vec_;
};

template <typename T>
inline Vertex<T> operator*(const T &sclr, const Vertex<T> &v) {
  return v * sclr;
}

template <typename T>
inline bool operator==(const Vertex<T> &lhs, const Vertex<T> &rhs) {
  return lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z() &&
         lhs.w() == rhs.w();
}

template <typename T>
inline bool operator!=(const Vertex<T> &lhs, const Vertex<T> &rhs) {
  return !(lhs == rhs);
}

template <typename T>
inline std::istream &operator>>(std::istream &is, Vertex<T> &v) {
  std::istream::sentry s{is};

  if (s) {
    double x{0.0}, y{0.0}, z{0.0}, w{1.0};
    is >> std::ws;
    if (is.peek() == 'v') {
      is.get();
    }
    is >> x >> y >> z;
    while (std::isspace(is.peek()) && is.peek() != '\n') {
      is.get();
    }
    if (is && is.peek() != '\n') {
      is >> w;
    }
    v.x() = static_cast<T>(x);
    v.y() = static_cast<T>(y);
    v.z() = static_cast<T>(z);
    v.w() = static_cast<T>(w);
  }

  return is;
}

template <typename T>
inline std::ostream &operator<<(std::ostream &os, const Vertex<T> &v) {
  os << "v " << v.x() << ' ' << v.y() << ' ' << v.z() << ' ' << v.w();
  return os;
}

}  // namespace s21

#endif  // LIBVIEWER_VERTEX_H_
