#ifndef LIBVIEWER_OBJ_FILE_READER_H_
#define LIBVIEWER_OBJ_FILE_READER_H_

#include <fstream>
#include <string>

#include "base_file_reader.h"
#include "figure.h"
#include "scene.h"

namespace s21 {

template <typename T, typename U>
class VFObjFileReader : public BaseFileReader {
 public:
  VFObjFileReader(const char *pathname) : BaseFileReader(pathname) {}
  ~VFObjFileReader(void) {}

 protected:
  VFObjFileReader(const VFObjFileReader &other) = delete;
  VFObjFileReader(VFObjFileReader &&other) = delete;
  VFObjFileReader &operator=(const VFObjFileReader &other) = delete;
  VFObjFileReader &operator=(VFObjFileReader &&other) = delete;

 public:
  Scene<T, U> *ReadScene(void);
};

template <typename T, typename U>
inline Scene<T, U> *VFObjFileReader<T, U>::ReadScene(void) {
  if (!file_) {
    return nullptr;
  }

  file_.seekg(0);
  Figure<T> *figure = new Figure<T, U>{};

  while (file_) {
    std::string token;
    file_ >> token;
    if (token == "v") {
      Vertex<T> v;
      file_ >> v;
      figure->PushBack(v);
    } else if (token == "f") {
      Face<U> f;
      file_ >> f;
      figure->PushBack(f);
    } else {
      std::string line;
      std::getline(file_, line, '\n');
    }
  }

  Scene<T, U> *sc = new Scene<T, U>;
  sc->AddFigure(figure);

  return sc;
}

}  // namespace s21

#endif  // LIBVIEWER_OBJ_FILE_READER_H_
