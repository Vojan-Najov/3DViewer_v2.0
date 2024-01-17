#ifndef LIBVIEWER_VIEWER_H_
#define LIBVIEWER_VIEWER_H_

#include <string>

#include "scene.h"

namespace s21 {

struct ViewerOperationResult final {
  std::string errorMessage;

  bool IsSuccess(void) const { return errorMessage.empty(); }
  bool IsFail(void) const { return !errorMessage.empty(); }
};

class Viewer final {
 public:
  Viewer(void) = default;
  Viewer(const Viewer &other) = delete;
  Viewer(Viewer &&other) = default;
  Viewer &operator=(const Viewer &other) = delete;
  Viewer &operator=(Viewer &&other) = default;
  ~Viewer(void) = default;

 public:
  ViewerOperationResult LoadObjFile(const char *pathname);

  //  DrawScene();
  //  MoveObject();
  //  RotateObject();
  //  ScaleObject();

 private:
  std::unique_ptr<Scene<float, int>> scene_;
};

}  // namespace s21

#endif  // LIBVIEWER_VIEWER_H_
