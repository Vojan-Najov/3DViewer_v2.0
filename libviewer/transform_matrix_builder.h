#ifndef TRANSFORM_MATRIX_BUILDER_H_
#define TRANSFORM_MATRIX_BUILDER_H_

#include <cmath>
#define PI 3.1415926

#include "matrix4x4.h"

namespace s21 {

template <typename T>
class TransformMatrixBuilder {
 public:
  static Matrix4x4<T> Rotation(T x, T y, T z) {
    T rad = x * PI / 180.;
    Matrix4x4<T> x_rot = {{1, 0, 0, 0},
                          {0, std::cos(rad), -std::sin(rad), 0},
                          {0, std::sin(rad), std::cos(rad), 0},
                          {0, 0, 0, 1}};
    rad = y * PI / 180.;
    Matrix4x4<T> y_rot = {{std::cos(rad), 0, std::sin(rad), 0},
                          {0, 1, 0, 0},
                          {-std::sin(rad), 0, std::cos(rad), 0},
                          {0, 0, 0, 1}};
    rad = z * PI / 180.;
    Matrix4x4<T> z_rot = {{std::cos(rad), -std::sin(rad), 0, 0},
                          {std::sin(rad), std::cos(rad), 0, 0},
                          {0, 0, 1, 0},
                          {0, 0, 0, 1}};
    return x_rot * y_rot * z_rot;
    return x_rot;
  }

  static Matrix4x4<T> Move(T x, T y, T z) {
    Matrix4x4<T> move = {
        {1, 0, 0, x}, {0, 1, 0, y}, {0, 0, 1, z}, {0, 0, 0, 1}};
    return move;
  }

  static Matrix4x4<T> Scale(T x, T y, T z) {
    Matrix4x4<T> scale = {
        {x, 0, 0, 0}, {0, y, 0, 0}, {0, 0, z, 0}, {0, 0, 0, 1}};
    return scale;
  }
};

}  // namespace s21

#endif  // TRANSFORM_MATRIX_BUILDER_H_
