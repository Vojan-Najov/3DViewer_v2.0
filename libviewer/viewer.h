#ifndef LIBVIEWER_VIEWER_H_
#define LIBVIEWER_VIEWER_H_

#include <string>

#include "render_base.h"
#include "scene.h"

namespace s21 {

struct ViewerOperationResult final {
  std::string errorMessage;

  bool IsSuccess(void) const { return errorMessage.empty(); }
  bool IsFail(void) const { return !errorMessage.empty(); }
};

class Viewer final {
 public:
  Viewer(void);
  Viewer(const Viewer &other) = delete;
  Viewer(Viewer &&other) = default;
  Viewer &operator=(const Viewer &other) = delete;
  Viewer &operator=(Viewer &&other) = default;
  ~Viewer(void) = default;

 public:
  ViewerOperationResult LoadObjFile(const char *pathname);
  void InitializeRender(void);
  void DrawScene(int width, int height, 
                 float xrotation = 0.0, float yrotation = 0.0);

 public:
  size_t GetVerticesNumber(void) const;
  size_t GetEdgesNumber(void) const;
  size_t GetFacesNumber(void) const;

  //  MoveObject();
  //  RotateObject();
  //  ScaleObject();

 private:
  std::unique_ptr<Scene<float, int>> scene_;
  std::unique_ptr<RenderBase<float, int>> render_;
};

}  // namespace s21

#endif  // LIBVIEWER_VIEWER_H_
