#ifndef LIBVIEWER_VEC4_H_
#define LIBVIEWER_VEC4_H_

#include <cmath>

namespace s21 {

template <typename T>
class Vec4 {
 public:
  Vec4(void) : vec_{0, 0, 0, 1} {}
  Vec4(const T &x, const T &y, const T &z, const T &w = T{1});
  Vec4(const Vec4 &v) = default;
  Vec4(Vec4 &&v) = default;
  Vec4 &operator=(const Vec4 &v) = default;
  Vec4 &operator=(Vec4 &&v) = default;
  ~Vec4(void) = default;

 public:
  T &x(void) { return vec_[0]; }
  const T &x(void) const { return vec_[0]; }
  T &y(void) { return vec_[1]; }
  const T &y(void) const { return vec_[1]; }
  T &z(void) { return vec_[2]; }
  const T &z(void) const { return vec_[2]; }
  T &w(void) { return vec_[3]; }
  const T &w(void) const { return vec_[3]; }
  T length(void) const;

 public:
  T &operator[](size_t idx) { return vec_[idx]; }
  const T &operator[](size_t idx) const { return vec_[idx]; }
  Vec4 operator+(const Vec4 &v) const;
  Vec4 operator-(const Vec4 &v) const;
  Vec4 operator*(const T &scalar) const;
  Vec4 &operator+=(const Vec4 &v);
  Vec4 &operator-=(const Vec4 &v);
  Vec4 &operator*=(const T &scalar);

 private:
  T vec_[4];
};

template <typename T>
Vec4<T>::Vec4(const T &x, const T &y, const T &z, const T &w)
    : vec_{x, y, z, w} {}

template <typename T>
inline T Vec4<T>::length(void) const {
  return std::sqrt(vec_[0] * vec_[0] + vec_[1] * vec_[1] + vec_[2] * vec_[2]);
}

template <typename T>
inline Vec4<T> Vec4<T>::operator+(const Vec4 &v) const {
  return Vec4{vec_[0] / vec_[3] + v.vec_[0] / v.vec_[3],
              vec_[1] / vec_[3] + v.vec_[1] / v.vec_[3],
              vec_[2] / vec_[3] + v.vec_[2] / v.vec_[3], 1};
}

template <typename T>
inline Vec4<T> Vec4<T>::operator-(const Vec4 &v) const {
  return Vec4{vec_[0] / vec_[3] - v.vec_[0] / v.vec_[3],
              vec_[1] / vec_[3] - v.vec_[1] / v.vec_[3],
              vec_[2] / vec_[3] - v.vec_[2] / v.vec_[3], 1};
}

template <typename T>
inline Vec4<T> Vec4<T>::operator*(const T &scalar) const {
  return Vec4{vec_[0] / vec_[3] * scalar, vec_[1] / vec_[3] * scalar,
              vec_[2] / vec_[3] * scalar, 1};
}

template <typename T>
inline Vec4<T> &Vec4<T>::operator+=(const Vec4 &v) {
  vec_[0] = vec_[0] / vec_[3] + v.vec_[0] / v.vec_[3];
  vec_[1] = vec_[1] / vec_[3] + v.vec_[1] / v.vec_[3];
  vec_[2] = vec_[2] / vec_[3] + v.vec_[2] / v.vec_[3];
  vec_[3] = 1;
  return *this;
}

template <typename T>
inline Vec4<T> &Vec4<T>::operator-=(const Vec4 &v) {
  vec_[0] = vec_[0] / vec_[3] - v.vec_[0] / v.vec_[3];
  vec_[1] = vec_[1] / vec_[3] - v.vec_[1] / v.vec_[3];
  vec_[2] = vec_[2] / vec_[3] - v.vec_[2] / v.vec_[3];
  vec_[3] = 1;
  return *this;
}

template <typename T>
inline Vec4<T> &Vec4<T>::operator*=(const T &scalar) {
  vec_[0] = vec_[0] / vec_[3] * scalar;
  vec_[1] = vec_[1] / vec_[3] * scalar;
  vec_[2] = vec_[2] / vec_[3] * scalar;
  vec_[3] = 1;
  return *this;
}

template <typename T>
inline Vec4<T> operator*(const T &scalar, const Vec4<T> &v) {
  return v * scalar;
}

template <typename T>
inline bool operator==(const Vec4<T> &lhs, const Vec4<T> &rhs) {
  return lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z() &&
         lhs.w() == rhs.w();
}

template <typename T>
inline bool operator!=(const Vec4<T> &lhs, const Vec4<T> &rhs) {
  return !(lhs == rhs);
}

}  // namespace s21

#endif  // LIBVIEWER_VEC4_H_
