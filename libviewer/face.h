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
  void PushBackVertexIndex(T index);

 public:
  Iterator Begin(void);
  ConstIterator Begin(void) const;
  Iterator End(void);
  ConstIterator End(void) const;

 public:
  size_t Size(void) const { return vertex_indices_.size(); }
  const T *Data(void) const { return vertex_indices_.data(); }

 private:
  std::vector<T> vertex_indices_;
};

template <typename T>
inline void Face<T>::PushBackVertexIndex(T index) {
  vertex_indices_.push_back(index);
}

template <typename T>
inline typename Face<T>::Iterator Face<T>::Begin(void) {
  return vertex_indices_.begin();
}

template <typename T>
inline typename Face<T>::ConstIterator Face<T>::Begin(void) const {
  return vertex_indices_.begin();
}

template <typename T>
inline typename Face<T>::Iterator Face<T>::End(void) {
  return vertex_indices_.end();
}

template <typename T>
inline typename Face<T>::ConstIterator Face<T>::End(void) const {
  return vertex_indices_.end();
}

template <typename T>
std::istream &operator>>(std::istream &is, Face<T> &f) {
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
        f.PushBackVertexIndex(static_cast<T>(vertex_index - 1));
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
