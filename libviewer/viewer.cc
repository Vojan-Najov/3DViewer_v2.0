#include "viewer.h"

#include <cstdlib>
#include <iostream>

#include "obj_file_reader.h"
#include "render_ffp.h"

namespace s21 {

Viewer::Viewer(void) : scene_{nullptr}, render_{new RenderFFP<float, int>{}} {}

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
  scene_->Init();

  return ViewerOperationResult{};
}

size_t Viewer::GetVerticesNumber(void) const {
  if (!scene_) {
    return 0;
  }
  return scene_->GetVerticesNumber();
}

size_t Viewer::GetEdgesNumber(void) const {
  if (!scene_) {
    return 0;
  }
  return scene_->GetEdgesNumber();
}

size_t Viewer::GetFacesNumber(void) const {
  if (!scene_) {
    return 0;
  }
  return scene_->GetFacesNumber();
}

void Viewer::InitializeRender(void) { render_->Initialize(); }

void Viewer::DrawScene(int width, int height) {
  if (scene_) {
    render_->DrawScene(*scene_, width, height);
  } else {
    render_->DrawEmptyScene();
  }
}

}  // namespace s21
