#ifndef LIBVIEWER_VERTEX_H_
#define LIBVIEWER_VERTEX_H_

#include <istream>

namespace s21 {

template <typename T>
class Matrix4x4;

template <typename T>
class Vertex {
 public:
  Vertex(void);
  Vertex(const T &x, const T &y, const T &z, const T &w = T{1});
  explicit Vertex(const char *str);
  Vertex(const Vertex &other) = default;
  Vertex(Vertex &&other) = default;
  Vertex &operator=(const Vertex &other) = default;
  Vertex &operator=(Vertex &&other) = default;
  ~Vertex(void) = default;

 public:
  T &x(void) noexcept;
  const T &x(void) const noexcept;
  T &y(void) noexcept;
  const T &y(void) const noexcept;
  T &z(void) noexcept;
  const T &z(void) const noexcept;
  T &w(void) noexcept;
  const T &w(void) const noexcept;

 public:
  T &operator[](size_t idx);
  const T &operator[](size_t idx) const;

 public:
  Vertex operator*(const T &ratio) const noexcept;
  Vertex &operator*=(const T &ratio) noexcept;

 public:
  Vertex(const Matrix4x4<T> source) {
    for (size_t i = 0; i < 4; i++) {
      point_[i] = source(i, i);
    }
  }

  Vertex operator*(const Matrix4x4<T> &transform) const {
    Vertex<T> temp = {0, 0, 0, 0};
    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 4; j++) {
        temp[i] += (*this)[j] * transform(j, i);
      }
    }
    return temp;
  }

  Vertex &operator*=(const Matrix4x4<T> &transform) {
    (*this) = (*this) * transform;
    return (*this);
  }

  Vertex &operator=(Matrix4x4<T> &&source) {
    for (size_t i = 0; i < 4; i++) {
      (*this)[i] = source(i, i);
    }
    return (*this);
  }

  Vertex operator+(const Vertex<T> &source) {
    Vertex<T> temp;
    for (size_t i = 0; i < 4; i++) {
      temp[i] = (*this)[i] + source[i];
    }
    return temp;
  }

  Vertex &operator+=(const Vertex<T> &source) {
    for (size_t i = 0; i < 4; i++) {
      (*this)[i] += source[i];
    }
    return (*this);
  }

 private:
  T point_[4];
};

template <typename T>
Vertex<T>::Vertex(void) : point_{T{}, T{}, T{}, T{1}} {}

template <typename T>
Vertex<T>::Vertex(const T &x, const T &y, const T &z, const T &w)
    : point_{x, y, z, w} {}

template <typename T>
Vertex<T>::Vertex(const char *str) : Vertex{} {
  (void)str;
}

template <typename T>
inline T &Vertex<T>::x(void) noexcept {
  return point_[0];
}

template <typename T>
inline const T &Vertex<T>::x(void) const noexcept {
  return point_[0];
}

template <typename T>
inline T &Vertex<T>::y(void) noexcept {
  return point_[1];
}

template <typename T>
inline const T &Vertex<T>::y(void) const noexcept {
  return point_[1];
}

template <typename T>
inline T &Vertex<T>::z(void) noexcept {
  return point_[2];
}

template <typename T>
inline const T &Vertex<T>::z(void) const noexcept {
  return point_[2];
}

template <typename T>
inline T &Vertex<T>::w(void) noexcept {
  return point_[3];
}

template <typename T>
inline const T &Vertex<T>::w(void) const noexcept {
  return point_[3];
}

template <typename T>
inline T &Vertex<T>::operator[](size_t idx) {
  return point_[idx];
}

template <typename T>
inline const T &Vertex<T>::operator[](size_t idx) const {
  return point_[idx];
}

template <typename T>
inline Vertex<T> Vertex<T>::operator*(const T &ratio) const noexcept {
  return Vertex{point_[0] * ratio, point_[1] * ratio, point_[2] * ratio,
                point_[3]};
}

template <typename T>
inline Vertex<T> &Vertex<T>::operator*=(const T &ratio) noexcept {
  point_[0] *= ratio;
  point_[1] *= ratio;
  point_[2] *= ratio;
  return *this;
}

template <typename T>
Vertex<T> operator*(T ratio, Vertex<T> point) {
  return point * ratio;
}

template <typename T>
std::istream &operator>>(std::istream &is, Vertex<T> &v) {
  std::istream::sentry s{is};

  if (s) {
    std::istream::int_type c;
    double x{0.0}, y{0.0}, z{0.0}, w{1.0};

    is >> std::ws;
    if (is.peek() == 'v') {
      c = is.get();
    }
    // c = is.peek();
    // if (c == '\n' || !std::isspace(c) || !std::isdigit(c)) {
    //	is.setstate(std::ios_base::failbit);
    // }
    (void)c;

    is >> x >> y >> z;
    if (is) {
      is >> w;
      if (is.fail()) {
        is.clear();
      }
    }
    v[0] = static_cast<T>(x);
    v[1] = static_cast<T>(y);
    v[2] = static_cast<T>(z);
    v[3] = static_cast<T>(1.0);
  }

  return is;
}

}  // namespace s21

#endif  // LIBVIEWER_VERTEX_H_
