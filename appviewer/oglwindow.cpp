#include "oglwindow.h"

OGLWindow::OGLWindow(QWidget *parent) : QOpenGLWidget{parent} {}

void OGLWindow::mousePressEvent(QMouseEvent *m) { mPos = m->pos(); }

void OGLWindow::mouseMoveEvent(QMouseEvent *m) {}

void OGLWindow::initializeGL(void) {
    emit InitializeGLNeeded();
}

void OGLWindow::paintGL(void) {
    emit redraw();
}

void OGLWindow::resizeGL(int w, int h) {
}

void OGLWindow::pupdate() { update(); }