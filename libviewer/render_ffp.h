#ifndef LIBVIEWER_RENDER_FFP_H_
#define LIBVIEWER_RENDER_FFP_H_

#include <OpenGL/gl.h>

#include "render_base.h"

namespace s21 {

template <typename T, typename U>
class RenderFFP : public RenderBase<T, U> {
 public:
  void Initialize(void) override;
  void DrawEmptyScene(void) override;
  void DrawScene(Scene<T, U> &scene, int width, int height) override;
  void ResizeViewport(int width, int height) override;
  ~RenderFFP(void) {}

 private:
  void SetViewMatrix(Scene<T, U> &scene);
  void SetProjectionMatrix(Scene<T, U> &scene, int width, int height);
  void DrawVertices(Scene<T, U> &scene);
  void DrawFaces(Scene<T, U> &scene);
};

template <typename T, typename U>
void RenderFFP<T, U>::Initialize(void) {
  glEnable(GL_DEPTH_TEST);
  glEnableClientState(GL_VERTEX_ARRAY);
}

template <typename T, typename U>
void RenderFFP<T, U>::DrawEmptyScene(void) {
  float color[4] = {1., 1., 1., 0.};

  glClearColor((GLfloat)color[0], (GLfloat)color[1], (GLfloat)color[2],
               (GLfloat)color[3]);
  glClearDepth((GLdouble)1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

template <typename T, typename U>
void RenderFFP<T, U>::DrawScene(Scene<T, U> &scene, int width, int height) {
  DrawEmptyScene();

  if (!scene.IsEmpty()) {
    const Figure<T, U> &figure = scene.GetFigure();
    glLoadIdentity();
    glVertexPointer(4, GL_FLOAT, 0, figure.GetVertices().data());
    SetViewMatrix(scene);
    SetProjectionMatrix(scene, width, height);
    DrawVertices(scene);
    DrawFaces(scene);
  }

  glFlush();
}

template <typename T, typename U>
void RenderFFP<T, U>::SetViewMatrix(Scene<T, U> &scene) {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if (!scene.IsEmpty()) {
    Vertex<T> camera= scene.GetCamera();
    Figure<T, U> figure = scene.GetFigure();
    Vertex<T> centre = figure.GetCentre();

    glTranslatef(-camera.x(), -camera.y(), -camera.z());
    (void) centre;
    //glTranslatef(model->centre[0], model->centre[1], model->centre[2]);
    //glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    //glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    //glTranslatef(-model->centre[0], -model->centre[1], -model->centre[2]);
  }
}

template <typename T, typename U>
void RenderFFP<T, U>::SetProjectionMatrix(Scene<T, U> &scene, int width,
                                          int height) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();


  if (!scene.IsEmpty()) {
    T x_aspect = width > height ? (float)width / (float)height : 1.0;
    T y_aspect = height > width ? (float)height / (float)width : 1.0;
    
    Vertex<T> camera = scene.GetCamera();
    Figure<T, U> figure = scene.GetFigure();
    Vertex<T> centre = figure.GetCentre();
    T dim = figure.GetDimension();

    T ro = centre[2] - camera[2];
    T focal_ro = scene.GetCameraFocalRo();
    T near = focal_ro;
    T far = -ro + dim > near ? -ro + dim : 2.0f * near;
    ro = ro < 0 ? -ro : focal_ro;
    
    glOrtho(-ro * x_aspect, ro * x_aspect, -ro * y_aspect, ro * y_aspect,
            near, far);
  }
}

template <typename T, typename U>
void RenderFFP<T, U>::DrawVertices(Scene<T, U> &scene) {
  float color[4] = {0, 0, 0, 0};

  if (!scene.IsEmpty()) {
    const Figure<T, U> &figure = scene.GetFigure();
    glColor3f(color[0], color[1], color[2]);
    glPointSize(1.0);
    glDrawArrays(GL_POINTS, (GLint)0, (GLsizei)figure.VerticesNumber());
  }
}

template <typename T, typename U>
void RenderFFP<T, U>::DrawFaces(Scene<T, U> &scene) {
  float color[4] = {0, 0, 1, 0};

  if (!scene.IsEmpty()) {
    const Figure<T, U> &figure = scene.GetFigure();
    glColor3f(color[0], color[1], color[2]);
    glLineWidth(10);
    std::vector<Face<U>> faces = figure.GetFaces();
    using fit = typename std::vector<Face<U>>::const_iterator;

    for (fit it = faces.begin(), last = faces.end(); it != last; ++it) {
      glDrawElements(GL_LINE_LOOP, it->Size(), GL_UNSIGNED_INT, it->Data());
      // std::cout << "Error: " << glGetError() << '\n';
    }
  }
}

template <typename T, typename U>
void RenderFFP<T,U>::ResizeViewport(int width, int height) {
  glViewport(0, 0, width, height);
}


}  // namespace s21

#endif  // LIBVIEWER_RENDER_FFP_H_
