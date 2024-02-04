#ifndef LIBVIEWER_VIEWER_H_
#define LIBVIEWER_VIEWER_H_

#include <string>

#include "renderer.h"
#include "scene.h"
#include "transform_matrix_builder.h"
#include "viewer_operation_result.h"

namespace s21 {

class Viewer final {
 public:
  Viewer(void);
  Viewer(const Viewer &other) = delete;
  Viewer(Viewer &&other) = default;
  Viewer &operator=(const Viewer &other) = delete;
  Viewer &operator=(Viewer &&other) = default;
  ~Viewer(void);

 public:
  ViewerOperationResult LoadObjFile(const char *pathname);
  void InitializeRender(void);
  void DrawScene(int width, int height);
  void ResizeViewport(int width, int height);

 public:
  size_t GetVerticesNumber(void) const;
  size_t GetEdgesNumber(void) const;
  size_t GetFacesNumber(void) const;
  float GetDimension(void) const;
  bool CheckScene(void) const;

  ViewerOperationResult MoveObject(float x, float y, float z);
  ViewerOperationResult RotateObject(float x, float y, float z);
  ViewerOperationResult ScaleObject(float x, float y, float z);
  ViewerOperationResult ScaleCamera(float scale);
  ViewerOperationResult RotateCamera(float xrot, float yrot);

 private:
  Scene<GLfloat, GLsizei> scene_;
  Renderer<GLfloat, GLsizei> renderer_;
};

}  // namespace s21

#endif  // LIBVIEWER_VIEWER_H_
