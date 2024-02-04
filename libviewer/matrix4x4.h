#ifndef LIBVIEWER_MATRIX4X4_H_
#define LIBVIEWER_MATRIX4X4_H_

#include "vec4.h"

namespace s21 {

template <typename T>
class Matrix4x4 {
 public:
  Matrix4x4(void);
  Matrix4x4(const Vec4<T> &v1, const Vec4<T> &v2, const Vec4<T> &v3,
            const Vec4<T> &v4);
  Matrix4x4(const Matrix4x4 &m) = default;
  Matrix4x4(Matrix4x4 &&m) = default;
  Matrix4x4 &operator=(const Matrix4x4 &m) = default;
  Matrix4x4 &operator=(Matrix4x4 &&m) = default;
  ~Matrix4x4(void) = default;

 public:
  T &operator()(size_t i, size_t j) { return m_[4 * i + j]; }
  const T &operator()(size_t i, size_t j) const { return m_[4 * i + j]; }
  Matrix4x4 operator*(const T &scalar) const;
  Matrix4x4 &operator*=(const T &scalar);
  Matrix4x4 operator*(const Matrix4x4 &m) const;
  Matrix4x4 &operator*=(const Matrix4x4 &m);
  Vec4<T> operator*(const Vec4<T> &v) const;

 private:
  T m_[16];
};

template <typename T>
Matrix4x4<T>::Matrix4x4(void)
    : m_{T{}, T{}, T{}, T{}, T{}, T{}, T{}, T{},
         T{}, T{}, T{}, T{}, T{}, T{}, T{}, T{}} {}

template <typename T>
Matrix4x4<T>::Matrix4x4(const Vec4<T> &v1, const Vec4<T> &v2, const Vec4<T> &v3,
                        const Vec4<T> &v4)
    : m_{v1.x(), v1.y(), v1.z(), v1.w(), v2.x(), v2.y(), v2.z(), v2.w(),
         v3.x(), v3.y(), v3.z(), v3.w(), v4.x(), v4.y(), v4.z(), v4.w()} {}

template <typename T>
inline Matrix4x4<T> Matrix4x4<T>::operator*(const T &sclr) const {
  return Matrix4x4{
      Vec4<T>{sclr * m_[0], sclr * m_[1], sclr * m_[2], sclr * m_[3]},
      Vec4<T>{sclr * m_[4], sclr * m_[5], sclr * m_[6], sclr * m_[7]},
      Vec4<T>{sclr * m_[8], sclr * m_[9], sclr * m_[10], sclr * m_[11]},
      Vec4<T>{sclr * m_[12], sclr * m_[13], sclr * m_[14], sclr * m_[15]}};
}

template <typename T>
inline Matrix4x4<T> &Matrix4x4<T>::operator*=(const T &sclr) {
  for (int i = 0; i < 16; ++i) {
    m_[i] *= sclr;
  }
  return *this;
}

template <typename T>
inline Matrix4x4<T> Matrix4x4<T>::operator*(const Matrix4x4 &m) const {
  Vec4<T> v1{
      m_[0] * m.m_[0] + m_[1] * m.m_[4] + m_[2] * m.m_[8] + m_[3] * m.m_[12],
      m_[0] * m.m_[1] + m_[1] * m.m_[5] + m_[2] * m.m_[9] + m_[3] * m.m_[13],
      m_[0] * m.m_[2] + m_[1] * m.m_[6] + m_[2] * m.m_[10] + m_[3] * m.m_[14],
      m_[0] * m.m_[3] + m_[1] * m.m_[7] + m_[2] * m.m_[11] + m_[3] * m.m_[15]};
  Vec4<T> v2{
      m_[4] * m.m_[0] + m_[5] * m.m_[4] + m_[6] * m.m_[8] + m_[7] * m.m_[12],
      m_[4] * m.m_[1] + m_[5] * m.m_[5] + m_[6] * m.m_[9] + m_[7] * m.m_[13],
      m_[4] * m.m_[2] + m_[5] * m.m_[6] + m_[6] * m.m_[10] + m_[7] * m.m_[14],
      m_[4] * m.m_[3] + m_[5] * m.m_[7] + m_[6] * m.m_[11] + m_[7] * m.m_[15]};
  Vec4<T> v3{
      m_[8] * m.m_[0] + m_[9] * m.m_[4] + m_[10] * m.m_[8] + m_[11] * m.m_[12],
      m_[8] * m.m_[1] + m_[9] * m.m_[5] + m_[10] * m.m_[9] + m_[11] * m.m_[13],
      m_[8] * m.m_[2] + m_[9] * m.m_[6] + m_[10] * m.m_[10] + m_[11] * m.m_[14],
      m_[8] * m.m_[3] + m_[9] * m.m_[7] + m_[10] * m.m_[11] +
          m_[11] * m.m_[15]};
  Vec4<T> v4{m_[12] * m.m_[0] + m_[13] * m.m_[4] + m_[14] * m.m_[8] +
                 m_[15] * m.m_[12],
             m_[12] * m.m_[1] + m_[13] * m.m_[5] + m_[14] * m.m_[9] +
                 m_[15] * m.m_[13],
             m_[12] * m.m_[2] + m_[13] * m.m_[6] + m_[14] * m.m_[10] +
                 m_[15] * m.m_[14],
             m_[12] * m.m_[3] + m_[13] * m.m_[7] + m_[14] * m.m_[11] +
                 m_[15] * m.m_[15]};
  return Matrix4x4{v1, v2, v3, v4};
}

template <typename T>
inline Matrix4x4<T> &Matrix4x4<T>::operator*=(const Matrix4x4 &m) {
  *this = *this * m;
  return *this;
}

template <typename T>
inline Vec4<T> Matrix4x4<T>::operator*(const Vec4<T> &v) const {
  return Vec4<T>{m_[0] * v[0] + m_[1] * v[1] + m_[2] * v[2] + m_[3] * v[3],
                 m_[4] * v[0] + m_[5] * v[1] + m_[6] * v[2] + m_[7] * v[3],
                 m_[8] * v[0] + m_[9] * v[1] + m_[10] * v[2] + m_[11] * v[3],
                 m_[12] * v[0] + m_[13] * v[1] + m_[14] * v[2] + m_[15] * v[3]};
}

}  // namespace s21

#endif  // LIBVIEWER_MATRIX4X4_H_
