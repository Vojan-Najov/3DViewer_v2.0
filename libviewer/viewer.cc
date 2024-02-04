#include "viewer.h"

#include <cstdlib>
#include <iostream>

#include "file_reader_obj.h"

namespace s21 {

Viewer::Viewer(void) : scene_{}, renderer_{} {}

Viewer::~Viewer(void) { SceneSettings::DestroyInstance(); }

ViewerOperationResult Viewer::LoadObjFile(const char *pathname) {
  VFObjFileReader<float, int> reader(pathname);
  if (reader.Fail()) {
    return ViewerOperationResult{std::string{pathname} + ": file open error"};
  }

  renderer_.Reset();
  return reader.Read(scene_);
}

size_t Viewer::GetVerticesNumber(void) const {
  return scene_.GetVerticesNumber();
}

size_t Viewer::GetEdgesNumber(void) const { return scene_.GetEdgesNumber(); }

size_t Viewer::GetFacesNumber(void) const { return scene_.GetFacesNumber(); }

float Viewer::GetDimension(void) const {
  return scene_.GetObject().Dimension();
}

bool Viewer::CheckScene(void) const { return !scene_.IsEmpty(); }

ViewerOperationResult Viewer::MoveObject(float x, float y, float z) {
  if (!scene_.IsEmpty()) {
    scene_.GetObject().Transform(TransformMatrixBuilder<float>::Move(x, y, z));
    return ViewerOperationResult{};
  }
  return ViewerOperationResult{"Empty scene"};
}

ViewerOperationResult Viewer::ScaleCamera(float scale) {
  renderer_.scale = scale;
  return ViewerOperationResult{};
}

ViewerOperationResult Viewer::RotateCamera(float xrot, float yrot) {
  renderer_.xrot = xrot;
  renderer_.yrot = yrot;
  return ViewerOperationResult{};
}

ViewerOperationResult Viewer::RotateObject(float x, float y, float z) {
  if (!scene_.IsEmpty()) {
    Vertex<float> centre = scene_.GetObject().Centre();
    float cx{centre.x()}, cy{centre.y()}, cz{centre.z()};
    scene_.GetObject().Transform(
        TransformMatrixBuilder<float>::Move(cx, cy, cz) *
        TransformMatrixBuilder<float>::Rotation(x, y, z) *
        TransformMatrixBuilder<float>::Move(-cx, -cy, -cz));
    return ViewerOperationResult{};
  }
  return ViewerOperationResult{"Empty scene"};
}

ViewerOperationResult Viewer::ScaleObject(float x, float y, float z) {
  if (!scene_.IsEmpty()) {
    Vertex<float> centre = scene_.GetObject().Centre();
    float cx{centre.x()}, cy{centre.y()}, cz{centre.z()};
    scene_.GetObject().Transform(
        TransformMatrixBuilder<float>::Move(cx, cy, cz) *
        TransformMatrixBuilder<float>::Scale(x, y, z) *
        TransformMatrixBuilder<float>::Move(-cx, -cy, -cz));
    return ViewerOperationResult{};
  }
  return ViewerOperationResult{"Empty scene"};
}

void Viewer::InitializeRender(void) { renderer_.Initialize(); }

void Viewer::DrawScene(int width, int height) {
  if (!scene_.IsEmpty()) {
    renderer_.DrawScene(scene_, width, height);
  } else {
    renderer_.DrawEmptyScene();
  }
}

void Viewer::ResizeViewport(int width, int height) {
  renderer_.ResizeViewport(width, height);
}

}  // namespace s21
