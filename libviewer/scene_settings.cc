#include "scene_settings.h"

#include "file_reader_settings.h"
#include "file_writer_settings.h"

namespace s21 {

SceneSettings *SceneSettings::instance = nullptr;

SceneSettings &SceneSettings::GetInstance(void) {
  if (!instance) {
    instance = new SceneSettings{};
    FileReaderSettings fr{VIEWER_SETTINGS_PATHNAME};
    fr.Read();
  }
  return *instance;
}

void SceneSettings::DestroyInstance(void) {
  FileWriterSettings fw{VIEWER_SETTINGS_PATHNAME};
  fw.Write();
  delete instance;
  instance = nullptr;
}

SceneSettings::SceneSettings()
    : projection_type_{ProjectionType::kParallel},
      line_type_{LineType::kSolid},
      vertex_type_{VertexType::kNone},
      line_size_{1},
      vertex_size_{1},
      line_color_{0, 0, 0.2, 0},
      vertex_color_{0, 0.2, 0, 0},
      background_color_{0.870588, 0.866667, 0.854902, 0} {}

enum ProjectionType SceneSettings::GetProjectionType(void) const {
  return projection_type_;
}

enum LineType SceneSettings::GetLineType(void) const { return line_type_; }

enum VertexType SceneSettings::GetVertexType(void) const {
  return vertex_type_;
}

float SceneSettings::GetLineSize(void) const { return line_size_; }

float SceneSettings::GetVertexSize(void) const { return vertex_size_; }

void SceneSettings::GetLineColor(float &red, float &green, float &blue,
                                 float &alpha) const {
  red = line_color_[0];
  green = line_color_[1];
  blue = line_color_[2];
  alpha = line_color_[3];
}

void SceneSettings::GetVertexColor(float &red, float &green, float &blue,
                                   float &alpha) const {
  red = vertex_color_[0];
  green = vertex_color_[1];
  blue = vertex_color_[2];
  alpha = vertex_color_[3];
}

void SceneSettings::GetBackgroundColor(float &red, float &green, float &blue,
                                       float &alpha) const {
  red = background_color_[0];
  green = background_color_[1];
  blue = background_color_[2];
  alpha = background_color_[3];
}

void SceneSettings::SetProjectionType(enum ProjectionType type) {
  projection_type_ = type;
}

void SceneSettings::SetLineType(enum LineType type) { line_type_ = type; }

void SceneSettings::SetVertexType(enum VertexType type) { vertex_type_ = type; }

bool SceneSettings::SetLineSize(float size) {
  if (size < 0.0f) {
    return false;
  }
  line_size_ = size;
  return true;
}

bool SceneSettings::SetVertexSize(float size) {
  if (size < 0.0f) {
    return false;
  }
  vertex_size_ = size;
  return true;
}

bool SceneSettings::SetLineColor(float red, float green, float blue,
                                 float alpha) {
  line_color_[0] = red;
  line_color_[1] = green;
  line_color_[2] = blue;
  line_color_[3] = alpha;
  return true;
}

bool SceneSettings::SetVertexColor(float red, float green, float blue,
                                   float alpha) {
  vertex_color_[0] = red;
  vertex_color_[1] = green;
  vertex_color_[2] = blue;
  vertex_color_[3] = alpha;
  return true;
}

bool SceneSettings::SetBackgroundColor(float red, float green, float blue,
                                       float alpha) {
  background_color_[0] = red;
  background_color_[1] = green;
  background_color_[2] = blue;
  background_color_[3] = alpha;
  return true;
}

}  // namespace s21
