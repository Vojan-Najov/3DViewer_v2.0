#include "file_reader_settings.h"

#include "scene_settings.h"

namespace s21 {

void FileReaderSettings::Read(void) {
  int type{0};
  float size{1}, red{0}, green{0}, blue{0}, alpha{0};
  SceneSettings &s = SceneSettings::GetInstance();

  if (Fail()) {
    return;
  }

  file_ >> type;
  if (type == 1) {
    s.SetProjectionType(ProjectionType::kCentral);
  } else {
    s.SetProjectionType(ProjectionType::kParallel);
  }
  file_ >> type;
  if (type == 1) {
    s.SetLineType(LineType::kDashed);
  } else {
    s.SetLineType(LineType::kSolid);
  }
  file_ >> type;
  if (type == 1) {
    s.SetVertexType(VertexType::kCircle);
  } else if (type == 2) {
    s.SetVertexType(VertexType::kSquare);
  } else {
    s.SetVertexType(VertexType::kNone);
  }
  file_ >> size;
  size = size < 1.0f ? 1.0f : size;
  s.SetLineSize(size);
  file_ >> size;
  size = size < 1.0f ? 1.0f : size;
  s.SetVertexSize(size);
  file_ >> red >> green >> blue >> alpha;
  if (red < 0.0f || red > 1.0f || green < 0.0f || green > 1.0f || blue < 0.0f ||
      blue > 1.0f || alpha < 0.0f || alpha > 1.0f) {
    red = 0.0f;
    green = 0.0f;
    blue = 0.0f;
    alpha = 0.0f;
  }
  s.SetLineColor(red, green, blue, alpha);
  file_ >> red >> green >> blue >> alpha;
  if (red < 0.0f || red > 1.0f || green < 0.0f || green > 1.0f || blue < 0.0f ||
      blue > 1.0f || alpha < 0.0f || alpha > 1.0f) {
    red = 0.0f;
    green = 0.0f;
    blue = 0.0f;
    alpha = 0.0f;
  }
  s.SetVertexColor(red, green, blue, alpha);
  file_ >> red >> green >> blue >> alpha;
  if (red < 0.0f || red > 1.0f || green < 0.0f || green > 1.0f || blue < 0.0f ||
      blue > 1.0f || alpha < 0.0f || alpha > 1.0f) {
    red = 1.0f;
    green = 1.0f;
    blue = 1.0f;
    alpha = 0.0f;
  }
  s.SetBackgroundColor(red, green, blue, alpha);
}

}  // namespace s21
