#ifndef LIBVIEWER_FACE_H_
#define LIBVIEWER_FACE_H_

#include <istream>

namespace s21 {

template <typename T>
class Face {
 public:
	void PushBackVertexIndex(T index);
 private:
  std::vector<T> vertex_indices_;
};

template <typename T>
inline void Face<T>::PushBackVertexIndex(T index) {
	vertex_indices_.push_back(index);
}

template <typename T>
std::istream & operator>>(std::istream &is, Face<T> &f) {
	std::istream::sentry s{is};

	if (s) {
		is >> std::ws;
		if (is.peek() == 'f') {
			is.get();
		}
		while (is && is.peek() != '\n') {
			while (is.peek() != '\n' && std::isspace(is.peek())) {
				is.get();
			}
			int vertex_index;
			is >> vertex_index;
			if (is && is.peek() == '/') {
				is.get();
				is >> std::noskipws;
				int texture_coordinate_index;
				is >> texture_coordinate_index;
				if (is && is.peek() == '/') {
					is.get();
					is >> std::noskipws;
					int normal_index;
					is >> normal_index;
				}
			}
			if (is) {
				f.PushBackVertexIndex(static_cast<T>(vertex_index));
			}
		}
		if (is && is.peek() == '\n') {
			is.get();
		}
	}

	return is;
}

}  // namespace s21

#endif  // LIBVIEWER_FACE_H_
