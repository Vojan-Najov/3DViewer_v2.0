#include "oglwindow.h"

OGLWindow::OGLWindow(QWidget *parent) : QOpenGLWidget{parent} {}

void OGLWindow::mousePressEvent(QMouseEvent *m) { mPos = m->pos(); }

void OGLWindow::mouseMoveEvent(QMouseEvent *m) {
    xRot += (m->pos().y() - mPos.y()) / M_PI;
    yRot += (m->pos().x() - mPos.x()) / M_PI;
    xRot = std::fmod(xRot, 360.0f);
    yRot = std::fmod(yRot, 360.0f);
    mPos = m->pos();

    update();
}

void OGLWindow::initializeGL(void) {

    emit InitializeGLNeeded();
}

void OGLWindow::paintGL(void) {
    emit RedrawNeeded(width(), height());
}

void OGLWindow::resizeGL(int w, int h) {
  emit ResizeNeeded(w, h);
}

void OGLWindow::pupdate() { update(); }
