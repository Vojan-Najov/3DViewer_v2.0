#ifndef LIBVIEWER_VERTEX_H_
#define LIBVIEWER_VERTEX_H_

#include <istream>

namespace s21 {

template <typename T>
class Vertex {
 public:
  Vertex(void);
  Vertex(const T& x, const T& y, const T& z, const T& w = T{1});
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
  T& operator[](size_t idx);
  const T& operator[](size_t idx) const;

 public:
  Vertex operator*(const T &ratio) const noexcept;
  Vertex &operator*=(const T &ratio) noexcept;

 private:
  T p_[4];
};

template <typename T>
Vertex<T>::Vertex(void) : p_{T{}, T{}, T{}, T{1}} {}

template <typename T>
Vertex<T>::Vertex(const T& x, const T& y, const T& z, const T& w)
    : p_{x, y, z, w}
{}

template <typename T>
inline T& Vertex<T>::x(void) noexcept { return p_[0]; }

template <typename T>
inline const T& Vertex<T>::x(void) const noexcept { return p_[0]; }

template <typename T>
inline T& Vertex<T>::y(void) noexcept { return p_[1]; }

template <typename T>
inline const T& Vertex<T>::y(void) const noexcept { return p_[1]; }

template <typename T>
inline T& Vertex<T>::z(void) noexcept { return p_[2]; }

template <typename T>
inline const T& Vertex<T>::z(void) const noexcept { return p_[2]; }

template <typename T>
inline T& Vertex<T>::w(void) noexcept { return p_[3]; }

template <typename T>
inline const T& Vertex<T>::w(void) const noexcept { return p_[3]; }

template <typename T>
inline T& Vertex<T>::operator[](size_t idx){ return p_[idx]; }

template <typename T>
inline const T& Vertex<T>::operator[](size_t idx) const { return p_[idx]; }

template <typename T>
inline Vertex<T> Vertex<T>::operator*(const T &ratio) const noexcept {
	return Vertex{p_[0] * ratio, p_[1] * ratio, p_[2] * ratio, p_[3]};
}

template <typename T>
inline Vertex<T> &Vertex<T>::operator*=(const T &ratio) noexcept {
	p_[0] *= ratio;
	p_[1] *= ratio;
	p_[2] *= ratio;
	return *this;
}

template <typename T>
Vertex<T> operator*(T ratio, Vertex<T> point) {
	return point * ratio;
}

template <typename T>
std::istream & operator>>(std::istream &is, Vertex<T> &v) {
	std::istream::sentry s{is};

	if (s) {
		char c;
		double x{0.0}, y{0.0}, z{0.0}, w{1.0};

		is >> c;
		if (c != 'v') {
			is.setstate(std::ios_base::failbit);
		}

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
		v[3] = static_cast<T>(w);
	}

	return is;
}

}  // namespace s21

#endif // LIBVIEWER_VERTEX_H_
