#ifndef LIBVIEWER_BASE_FILE_READER_H_
#define LIBVIEWER_BASE_FILE_READER_H_

#include <fstream>
#include <iostream>
#include <string>

#include "scene.h"
#include "wireframe.h"

namespace s21 {

class BaseFileReader {
 public:
  BaseFileReader(const char *pathname);

  bool Fail(void) const;

 protected:
  BaseFileReader(const BaseFileReader &other) = delete;
  BaseFileReader(BaseFileReader &&other) = delete;
  BaseFileReader &operator=(const BaseFileReader &other) = delete;
  BaseFileReader &operator=(BaseFileReader &&other) = delete;
  ~BaseFileReader(void);

 protected:
  std::ifstream file_;
};

}  // namespace s21

#endif  // LIBVIEWER_BASE_FILE_READER_H_
