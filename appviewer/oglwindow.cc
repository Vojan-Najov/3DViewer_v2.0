#include "oglwindow.h"

#include <iostream>

OGLWindow::OGLWindow(QWidget *parent) : QOpenGLWidget{parent} {}

void OGLWindow::mousePressEvent(QMouseEvent *m) { mPos = m->pos(); }

void OGLWindow::mouseMoveEvent(QMouseEvent *m) {
  xRot += (m->pos().y() - mPos.y()) / M_PI;
  yRot += (m->pos().x() - mPos.x()) / M_PI;
  xRot = std::fmod(xRot, 360.0f);
  yRot = std::fmod(yRot, 360.0f);
  mPos = m->pos();

  emit ChangeCameraNeeded(xRot, yRot, scale);
  update();
  emit GetFrame();
}

void OGLWindow::wheelEvent(QWheelEvent *w) {
  scale += w->angleDelta().y() / 1000.0f;
  if (scale <= 0) {
    scale = 0.1;
  }

  emit ChangeCameraNeeded(xRot, yRot, scale);
  update();
  emit GetFrame();
}

void OGLWindow::initializeGL(void) { emit InitializeGLNeeded(); }

void OGLWindow::paintGL(void) { emit RedrawNeeded(width(), height()); }

void OGLWindow::resizeGL(int w, int h) { emit ResizeNeeded(w, h); }

void OGLWindow::pupdate() {
  emit ChangeCameraNeeded(xRot, yRot, scale);
  update();
  emit GetFrame();
}

void OGLWindow::ResetMouseData(void) {
  xRot = 0.0f;
  yRot = 0.0f;
  scale = 1.0f;
}
