#ifndef LIBVIEWER_FACE_H_
#define LIBVIEWER_FACE_H_

#include <istream>

namespace s21 {

template <typename T>
class Face {
 public:
  using Iterator = typename std::vector<T>::iterator;
  using ConstIterator = typename std::vector<T>::const_iterator;

 public:
  Face(void) { vertex_indices_.reserve(4); }
  Face(const Face &other) = default;
  Face(Face &&other) = default;
  Face &operator=(const Face &other) = default;
  Face &operator=(Face &&other) = default;
  ~Face(void) = default;

 public:
  void PushBackVertexIndex(T idx) { vertex_indices_.push_back(idx); }

 public:
  Iterator Begin(void) { return vertex_indices_.begin(); }
  ConstIterator Begin(void) const { return vertex_indices_.begin(); }
  Iterator End(void) { return vertex_indices_.end(); }
  ConstIterator End(void) const { return vertex_indices_.end(); }

 public:
  bool Empty(void) const { return vertex_indices_.empty(); }
  size_t Size(void) const { return vertex_indices_.size(); }
  const T *Data(void) const { return vertex_indices_.data(); }

 private:
  std::vector<T> vertex_indices_;
};

template <typename T>
std::istream &operator>>(std::istream &is, Face<T> &f) {
  std::istream::sentry s{is};

  if (s) {
    is >> std::ws;
    if (is.peek() == 'f') {
      is.get();
    }
    while (true) {
      while (is && is.peek() != '\n' && std::isspace(is.peek())) {
        is.get();
      }
      if (!is) {
        break;
      }
      if (is.peek() == '\n') {
        is.get();
        break;
      }
      int vertex_index;
      is >> vertex_index;
      f.PushBackVertexIndex(static_cast<T>(vertex_index));
      if (is && is.peek() == '/') {
        is.get();
        is >> std::noskipws;
        if (is.peek() != '/') {
          int texture_coordinate_index;
          is >> texture_coordinate_index;
        }
        if (is && is.peek() == '/') {
          is.get();
          is >> std::noskipws;
          int normal_index;
          is >> normal_index;
        }
      }
    }
    if (is && is.peek() == '\n') {
      is.get();
    }
  }

  is >> std::skipws;
  return is;
}

}  // namespace s21

#endif  // LIBVIEWER_FACE_H_
