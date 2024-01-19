#include "controller.h"

namespace s21 {

Controller::Controller(Viewer &viewer) : viewer_{viewer} {}

bool Controller::LoadObjFile(const QString &filename) {
    viewer_.LoadObjFile(filename.toLatin1());
    return true;
}

size_t Controller::GetVerticesNumber(void) {
  return viewer_.GetVerticesNumber();
}

size_t Controller::GetEdgesNumber(void) {
  return viewer_.GetEdgesNumber();
}

size_t Controller::GetFacesNumber(void) {
  return viewer_.GetFacesNumber();
}

QString Controller::GetErrorMessage(void) {
    return "TODO";
}

void Controller::InitializeGLHandler(void) {
    viewer_.InitializeRender();
}

void Controller::DrawScene(void) {
    viewer_.DrawScene();
}


}  // namespace s21

