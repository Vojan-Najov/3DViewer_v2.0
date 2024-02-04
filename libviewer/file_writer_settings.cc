#include "file_writer_settings.h"

#include "scene_settings.h"

namespace s21 {

void FileWriterSettings::Write(void) {
  float red, green, blue, alpha;
  SceneSettings &s = SceneSettings::GetInstance();

  if (Fail()) {
    return;
  }

  if (s.GetProjectionType() == ProjectionType::kParallel) {
    file_ << 0 << '\n';
  } else {
    file_ << 1 << '\n';
  }
  if (s.GetLineType() == LineType::kSolid) {
    file_ << 0 << '\n';
  } else {
    file_ << 1 << '\n';
  }
  if (s.GetVertexType() == VertexType::kNone) {
    file_ << 0 << '\n';
  } else if (s.GetVertexType() == VertexType::kCircle) {
    file_ << 1 << '\n';
  } else {
    file_ << 2 << '\n';
  }
  file_ << s.GetLineSize() << '\n';
  file_ << s.GetVertexSize() << '\n';
  s.GetLineColor(red, green, blue, alpha);
  file_ << red << " " << green << " " << blue << " " << alpha << '\n';
  s.GetVertexColor(red, green, blue, alpha);
  file_ << red << " " << green << " " << blue << " " << alpha << '\n';
  s.GetBackgroundColor(red, green, blue, alpha);
  file_ << red << " " << green << " " << blue << " " << alpha << '\n';
}

}  // namespace s21
