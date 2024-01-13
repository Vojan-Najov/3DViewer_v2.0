#ifndef LIBVIEWER_VIEWER_H_
#define LIBVIEWER_VIEWER_H_

#include "scene.h"

class ViewerOperationResult final {
 public:
  bool isSuccesses(void) const { return !errorMessage.empty(); }
  bool isFail(void) const { return !errorMessage.empty(); }

 public:
  std::string errorMessage;
};

class Viewer final {
 public:
  ViewerOperationResult LoadObjFile(const char *pathname);

//  DrawScene();
//  MoveObject();
//  RotateObject();
//  ScaleObject();

 private:
  Scene<float> scene_;
};

#endif  // LIBVIEWER_VIEWER_H_
