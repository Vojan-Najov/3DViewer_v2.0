#ifndef LIBVIEWER_FILE_READER_OBJ_H_
#define LIBVIEWER_FILE_READER_OBJ_H_

#include <cstring>
#include <fstream>
#include <limits>
#include <memory>
#include <set>
#include <string>

#include "file_reader_base.h"
#include "object.h"
#include "scene.h"
#include "viewer_operation_result.h"

namespace s21 {

template <typename T, typename U>
class VFObjFileReader : public FileReaderBase {
 public:
  VFObjFileReader(const char *pathname);
  ~VFObjFileReader(void) {}

 protected:
  VFObjFileReader(const VFObjFileReader &other) = delete;
  VFObjFileReader(VFObjFileReader &&other) = delete;
  VFObjFileReader &operator=(const VFObjFileReader &other) = delete;
  VFObjFileReader &operator=(VFObjFileReader &&other) = delete;

 public:
  ViewerOperationResult Read(Scene<T, U> &scene);

 private:
  size_t line_count_;
  std::set<std::string> skipped_tokens_;
};

template <typename T, typename U>
VFObjFileReader<T, U>::VFObjFileReader(const char *pathname)
    : FileReaderBase{pathname}, line_count_{0} {
  const char *tokens[] = {"vn", "vt", "l", "s", "g", "o", "mtllib", "usemtl"};
  size_t size = sizeof(tokens) / sizeof(const char *);
  skipped_tokens_.insert(&tokens[0], &tokens[size]);
}

template <typename T, typename U>
inline ViewerOperationResult VFObjFileReader<T, U>::Read(Scene<T, U> &scene) {
  if (!file_) {
    return ViewerOperationResult{std::strerror(errno)};
  }

  file_.seekg(0);
  line_count_ = 0;
  std::unique_ptr<Object<T, U>> obj{new Object<T, U>{}};

  while (file_) {
    ++line_count_;
    std::string token;
    file_ >> std::ws >> token;
    if (token[0] == '#' ||
        skipped_tokens_.find(token) != skipped_tokens_.end()) {
      file_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else if (token == "v") {
      Vertex<T> v;
      file_ >> v;
      obj->PushBack(std::move(v));
    } else if (token == "f") {
      Face<int> f;
      file_ >> f;
      obj->PushBack(f);
    } else {
      break;
    }
  }
  if (!file_.eof() && file_.fail()) {
    return ViewerOperationResult{"parse error on line: " +
                                 std::to_string(line_count_)};
  }
  scene.SetObject(std::move(obj));
  return ViewerOperationResult{};
}

}  // namespace s21

#endif  // LIBVIEWER_OBJ_FILE_READER_H_
