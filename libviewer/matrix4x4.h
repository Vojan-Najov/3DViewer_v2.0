#ifndef MATRIX4X4_H_
#define MATRIX4X4_H_

#include <cmath>
#include <cstddef>
#include <iostream>

namespace s21 {

template <typename T>
class Vertex;

template <typename T>
class Matrix4x4 {
 private:
  T matr_[4][4];

 public:
  Matrix4x4(){};
  Matrix4x4(const Matrix4x4<T> &source) { (*this) = source; }
  Matrix4x4(Matrix4x4<T> &&source) { (*this) = std::move(source); }
  Matrix4x4(const std::initializer_list<std::initializer_list<T>> source) {
    auto pointer = source.begin();
    size_t i = 0;
    while (pointer != source.end()) {
      std::copy(pointer->begin(), pointer->end(), matr_[i]);
      i++;
      pointer++;
    }
  }
  Matrix4x4(const Vertex<T> &source) {
    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 4; j++) {
        if (i == j)
          (*this)(i, j) = source[i];
        else
          (*this)(i, j) = 0;
      }
    }
  }
  ~Matrix4x4(){};

  void initialize_point(Vertex<T> &point) {
    point.x = matr_[0][0];
    point.y = matr_[1][1];
    point.z = matr_[2][2];
    point.w = matr_[3][3];
  }

  Vertex<T> transform_point() {
    Vertex<T> point;
    point.x = matr_[0][0];
    point.y = matr_[1][1];
    point.z = matr_[2][2];
    point.w = matr_[3][3];
    return point;
  }

  Matrix4x4 &operator=(const Matrix4x4<T> &source) {
    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 4; j++) {
        matr_[i][j] = source.matr_[i][j];
      }
    }
    return (*this);
  }

  Matrix4x4 &operator=(Matrix4x4<T> &&source) {
    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 4; j++) {
        matr_[i][j] = source.matr_[i][j];
      }
    }
    return (*this);
  }

  Matrix4x4 operator*(const Matrix4x4<T> &source) {
    Matrix4x4<T> temp = {
        {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 4; j++) {
        for (size_t k = 0; k < 4; k++) {
          temp.matr_[i][j] += (*this).matr_[i][k] * source.matr_[k][j];
        }
      }
    }
    return temp;
  }

  Matrix4x4 &operator*=(const Matrix4x4<T> &source) {
    (*this) = (*this) * source;
    return (*this);
  }

  const T operator()(size_t i, size_t j) const { return matr_[i][j]; }

  T &operator()(size_t i, size_t j) { return matr_[i][j]; }

  bool operator==(const Matrix4x4<T> &source) {
    bool result = true;
    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 4; j++) {
        if (abs((*this)(i, j) - source(i, j)) > 1e-7) {
          result = false;
          break;
        }
      }
      if (!result) break;
    }
    return result;
  }

  void print() {
    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 4; j++) {
        std::cout << matr_[i][j] << ' ';
      }
      std::cout << '\n';
    }
  }
};

}  // namespace s21

#endif  // MATRIX4X4_H_
