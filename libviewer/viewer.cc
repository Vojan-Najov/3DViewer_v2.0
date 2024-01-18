#include "viewer.h"

#include <iostream>

#include "obj_file_reader.h"

namespace s21 {

ViewerOperationResult Viewer::LoadObjFile(const char *pathname) {
  VFObjFileReader<float, int> reader(pathname);
  if (reader.Fail()) {
    return ViewerOperationResult{"Error"};
  }

  Scene<float, int> *sceneptr = reader.ReadScene();
  if (!sceneptr) {
    return ViewerOperationResult{"Error"};
  }

  scene_ = std::unique_ptr<Scene<float, int>>{sceneptr};

  return ViewerOperationResult{};
}

size_t Viewer::GetVerticesNumber(void) const {
  return scene_->GetVerticesNumber();
}

size_t Viewer::GetEdgesNumber(void) const {
  return scene_->GetEdgesNumber();
}

size_t Viewer::GetFacesNumber(void) const {
  return scene_->GetFacesNumber();
}

}  // namespace s21
