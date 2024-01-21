#ifndef OGLWINDOW_H
#define OGLWINDOW_H

#define GL_SILENCE_DEPRECATION

#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

class OGLWindow : public QOpenGLWidget
{
  Q_OBJECT
 private:
  float xRot, yRot;
  QPoint mPos;

 public:
  explicit OGLWindow(QWidget *parent = nullptr);
  void pupdate(void);
  void mousePressEvent(QMouseEvent *m);
  void mouseMoveEvent(QMouseEvent *m);

 protected:
  void initializeGL(void);
  void resizeGL(int w, int h);
  void paintGL(void);

 signals:
  void InitializeGLNeeded(void);
  void RedrawNeeded(int width, int height);
  void ResizeNeeded(int width, int height);
};

#endif  // OGLWINDOW_H
