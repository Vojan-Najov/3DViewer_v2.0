#ifndef OGLWINDOW_H
#define OGLWINDOW_H

#define GL_SILENCE_DEPRECATION

#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWheelEvent>

class OGLWindow : public QOpenGLWidget {
  Q_OBJECT
 private:
  float xRot{0.0f}, yRot{0.0f}, scale{1.0f};
  QPoint mPos;
  QPoint wPos;

 public:
  explicit OGLWindow(QWidget *parent = nullptr);
  void pupdate(void);
  void mousePressEvent(QMouseEvent *m);
  void mouseMoveEvent(QMouseEvent *m);
  void wheelEvent(QWheelEvent *m);
  void ResetMouseData(void);

 protected:
  void initializeGL(void);
  void resizeGL(int w, int h);
  void paintGL(void);

 signals:
  void ChangeCameraNeeded(float xrot, float yrot, float scale);
  void InitializeGLNeeded(void);
  void RedrawNeeded(int width, int height);
  void ResizeNeeded(int width, int height);
  void GetFrame();
};

#endif  // OGLWINDOW_H
