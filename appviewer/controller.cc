#include "controller.h"

#include <QDebug>

namespace s21 {

Controller::Controller(Viewer &viewer) : viewer_{viewer} {}

bool Controller::LoadObjFile(const QString &filename) {
  viewer_.LoadObjFile(filename.toLatin1());
  return true;
}

size_t Controller::GetVerticesNumber(void) {
  return viewer_.GetVerticesNumber();
}

size_t Controller::GetEdgesNumber(void) { return viewer_.GetEdgesNumber(); }

size_t Controller::GetFacesNumber(void) { return viewer_.GetFacesNumber(); }

float Controller::GetDimension(void) { return viewer_.GetDimension(); }

QString Controller::GetErrorMessage(void) { return "TODO"; }

bool Controller::CheckScene(void) const { return viewer_.CheckScene(); }

void Controller::InitializeGLHandler(void) { viewer_.InitializeRender(); }

void Controller::RedrawGLHandler(int width, int height) {
  viewer_.DrawScene(width, height);
}

void Controller::ResizeGLHandler(int width, int height) {
  viewer_.ResizeViewport(width, height);
}

void Controller::ChangeCamera(float xrot, float yrot, float scale) {
  viewer_.RotateCamera(xrot, yrot);
  viewer_.ScaleCamera(scale);
}

void Controller::ColorSettingsVertex(float red, float green, float blue) {
  SceneSettings::GetInstance().SetVertexColor(red, green, blue, 0);
}

void Controller::ColorSettingsBackground(float red, float green, float blue) {
  SceneSettings::GetInstance().SetBackgroundColor(red, green, blue, 0);
}

void Controller::ColorSettingsLine(float red, float green, float blue) {
  SceneSettings::GetInstance().SetLineColor(red, green, blue, 0);
}

void Controller::LineType(size_t line_type) {
  SceneSettings::GetInstance().SetLineType(
      static_cast<enum LineType>(line_type));
}

void Controller::VertexType(size_t vertex_type) {
  SceneSettings::GetInstance().SetVertexType(
      static_cast<enum VertexType>(vertex_type));
}

void Controller::ProjectionType(size_t projection_type) {
  SceneSettings::GetInstance().SetProjectionType(
      static_cast<enum ProjectionType>(projection_type));
}

void Controller::LineSlider(size_t line_slider) {
  SceneSettings::GetInstance().SetLineSize(line_slider);
}

void Controller::VertexSlider(size_t vertex_slider) {
  SceneSettings::GetInstance().SetVertexSize(vertex_slider);
}

void Controller::MoveScale(float x, float y, float z) {
  viewer_.ScaleObject(x, y, z);
}

void Controller::MoveRotation(float x, float y, float z) {
  viewer_.RotateObject(x, y, z);
}

void Controller::MoveTranslate(float x, float y, float z) {
  viewer_.MoveObject(x, y, z);
}

}  // namespace s21
