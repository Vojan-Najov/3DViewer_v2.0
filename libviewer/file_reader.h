#ifndef LIBVIEWER_FILE_READER_H_
#define LIBVIEWER_FILE_READER_H_

#include <string>
#include <fstream>
#include <iostream>

#include "scene.h"
#include "wireframe.h"

namespace s21 {

class BaseFileReader {
 public:
  BaseFileReader(const char *pathname);

 protected:
  BaseFileReader(const BaseFileReader &other) = delete;
  BaseFileReader(BaseFileReader &&other) = delete;
  BaseFileReader &operator=(const BaseFileReader &other) = delete;
  BaseFileReader &operator=(BaseFileReader &&other) = delete;
  ~BaseFileReader(void);

 protected:
  std::ifstream file_;
};

BaseFileReader::BaseFileReader(const char *pathname) {
  file_.open(pathname);
}

BaseFileReader::~BaseFileReader(void) {
  file_.close();
}

template <typename T>
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
  Scene<T> *ReadScene(void);
};

template <typename T>
inline Scene<T> *VFObjFileReader<T>::ReadScene(void) {
	Wireframe<T> *wf = new Wireframe<T>{};

	while (file_) {
		std::string token;
		file_ >> token;
		if (token == "v") {
			Vertex<T> v;
			file_ >> v;
			wf->PushBack(v);
		} else if (token == "f") {
			std::string line;
			std::getline(file_, line, '\n');
		} else {
			std::string line;
			std::getline(file_, line, '\n');
		}
	}

  Scene<T> *sc = new Scene<T>;
	sc->AddObject(wf);

  return sc;
}

}  // namespace s21

#endif  // LIBVIEWER_FILE_READER_H_
