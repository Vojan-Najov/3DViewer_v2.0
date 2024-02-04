#ifndef APPVIEWER_CONTROLLER_H_
#define APPVIEWER_CONTROLLER_H_

#include <QObject>
#include <QString>

#include "viewer.h"

namespace s21 {

class Controller : public QObject {
  Q_OBJECT

 public:
  Controller(Viewer &viewer);

 public:
  bool LoadObjFile(const QString &filename);

 public:
  size_t GetVerticesNumber(void);
  size_t GetEdgesNumber(void);
  size_t GetFacesNumber(void);
  float GetDimension(void);
  QString GetErrorMessage(void);
  bool CheckScene(void) const;

  void ColorSettingsVertex(float redF, float greenF, float blueF);
  void ColorSettingsBackground(float redF, float greenF, float blueF);
  void ColorSettingsLine(float redF, float greenF, float blueF);
  void LineType(size_t line_type);
  void VertexType(size_t vertex_type);
  void ProjectionType(size_t projection_type);
  void LineSlider(size_t line_slider);
  void VertexSlider(size_t vertex_slider);
  void MoveScale(float x, float y, float z);
  void MoveRotation(float x, float y, float z);
  void MoveTranslate(float x, float y, float z);

 public slots:
  void ChangeCamera(float xrot, float yrot, float scale);
  void InitializeGLHandler(void);
  void RedrawGLHandler(int width, int height);
  void ResizeGLHandler(int width, int height);

 private:
  Viewer &viewer_;
};

}  // namespace s21

#endif  // APPVIEWER_CONTROLLER_H_
