#ifndef LIBVIEWER_RENDER_H_
#define LIBVIEWER_RENDER_H_

#ifndef GL_SILENCE_DEPRECATION
#define GL_SILENCE_DEPRECATION
#endif  // GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "scene.h"

namespace s21 {

template <typename T, typename U>
class Renderer {
 public:
  void Initialize(void);
  void DrawEmptyScene(void);
  void DrawScene(Scene<T, U> &scene, int width, int height);
  void ResizeViewport(int width, int height);
  void Reset(void);

 private:
  void SetViewMatrix(Scene<T, U> &scene);
  void SetProjectionMatrix(Scene<T, U> &scene, int width, int height);
  void DrawFaces(const Scene<T, U> &scene);
  void DrawVertices(const Scene<T, U> &scene);

 public:
  float xrot{0.0f};
  float yrot{0.0f};
  float scale{1.0f};

 private:
  bool vertex_array_{false};
};

template <typename T, typename U>
void Renderer<T, U>::Initialize(void) {
  glEnable(GL_DEPTH_TEST);
  glEnableClientState(GL_VERTEX_ARRAY);
}

template <typename T, typename U>
void Renderer<T, U>::Reset(void) {
  xrot = 0.0f;
  yrot = 0.0f;
  scale = 1.0f;
  vertex_array_ = false;
}

template <typename T, typename U>
void Renderer<T, U>::DrawEmptyScene(void) {
  float red, green, blue, alpha;

  SceneSettings::GetInstance().GetBackgroundColor(red, green, blue, alpha);
  glClearColor(red, green, blue, alpha);
  glClearDepth(1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

template <typename T, typename U>
void Renderer<T, U>::DrawScene(Scene<T, U> &scene, int width, int height) {
  DrawEmptyScene();

  if (!scene.IsEmpty()) {
    const Object<T, U> &object = scene.GetObject();
    if (!vertex_array_) {
      glLoadIdentity();
      glVertexPointer(4, GL_FLOAT, 0, object.GetVertices().data());
      vertex_array_ = true;
    }
    SetViewMatrix(scene);
    SetProjectionMatrix(scene, width, height);
    DrawFaces(scene);
    DrawVertices(scene);
  }
  glFlush();
}

template <typename T, typename U>
void Renderer<T, U>::DrawVertices(const Scene<T, U> &scene) {
  const Object<T, U> &object = scene.GetObject();
  SceneSettings &settings = SceneSettings::GetInstance();
  VertexType vertex_type = settings.GetVertexType();

  if (vertex_type != VertexType::kNone) {
    float red{0}, green{0}, blue{0}, alpha{0};
    settings.GetVertexColor(red, green, blue, alpha);

    Vertex<T> camera = scene.GetCamera();
    Vertex<T> centre = object.Centre();
    T size = settings.GetVertexSize();
    T dim = object.Dimension() * scale;
    T ro = (centre - camera).length();
    ro = ro < 2.0f * dim ? 2.0f * dim : ro;
    glPointSize(1.0f + size * dim / ro);

    if (vertex_type == VertexType::kCircle) {
      glEnable(GL_POINT_SMOOTH);
    } else {
      glDisable(GL_POINT_SMOOTH);
    }
    glColor3f(red, green, blue);
    glDrawArrays(GL_POINTS, (GLint)0, (GLsizei)object.VerticesNumber());
  }
}

template <typename T, typename U>
void Renderer<T, U>::DrawFaces(const Scene<T, U> &scene) {
  const Object<T, U> &object = scene.GetObject();
  float red{0}, green{0}, blue{0}, alpha{0};
  SceneSettings &settings = SceneSettings::GetInstance();
  settings.GetLineColor(red, green, blue, alpha);
  LineType line_type = settings.GetLineType();

  const Vertex<T> &camera = scene.GetCamera();
  Vertex<T> centre = object.Centre();
  T dim = object.Dimension() * scale;
  T size = settings.GetLineSize();
  T ro = (centre - camera).length();
  ro = ro < 2.0f * dim ? 2.0f * dim : ro;
  glLineWidth(1.0f + size * 2.0f * dim / (ro * 3));
  glEnable(GL_LINE_SMOOTH);

  if (line_type == LineType::kDashed) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  glColor3f(red, green, blue);
  const std::vector<U> &edges = object.GetEdges();
  glDrawElements(GL_LINES, edges.size(), GL_UNSIGNED_INT, edges.data());
}

template <typename T, typename U>
void Renderer<T, U>::SetViewMatrix(Scene<T, U> &scene) {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if (!scene.IsEmpty()) {
    Vertex<T> camera = scene.GetCamera();
    Object<T, U> &object = scene.GetObject();
    Vertex<T> centre = object.Centre();

    glTranslatef(-camera.x(), -camera.y(), -camera.z());
    glTranslatef(centre[0], centre[1], centre[2]);
    glScalef(scale, scale, scale);
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);
    glTranslatef(-centre[0], -centre[1], -centre[2]);
  }
}

template <typename T, typename U>
void Renderer<T, U>::SetProjectionMatrix(Scene<T, U> &scene, int width,
                                         int height) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (!scene.IsEmpty()) {
    T x_aspect = width > height ? (float)width / (float)height : 1.0;
    T y_aspect = height > width ? (float)height / (float)width : 1.0;

    Vertex<T> camera = scene.GetCamera();
    Object<T, U> &object = scene.GetObject();
    Vertex<T> centre = object.Centre();
    T dim = object.Dimension() * scale;

    T ro = centre[2] - camera[2];
    T focal_ro = scene.GetCameraFocalRo();
    if (SceneSettings::GetInstance().GetProjectionType() ==
        ProjectionType::kParallel) {
      T near = focal_ro;
      T far = -ro + dim > near ? -ro + 2 * dim : 2.0f * near;
      ro = ro < 0 ? -ro : focal_ro;
      glOrtho(-ro * x_aspect, ro * x_aspect, -ro * y_aspect, ro * y_aspect,
              near, far);
    } else {
      T near = focal_ro;
      T far = ro < 0.0f ? -ro + dim : dim;
      glFrustum(-focal_ro * x_aspect, focal_ro * x_aspect, -focal_ro * y_aspect,
                focal_ro * y_aspect, near, far);
    }
  }
}

template <typename T, typename U>
void Renderer<T, U>::ResizeViewport(int width, int height) {
  glViewport(0, 0, width, height);
}

}  // namespace s21

#endif  // LIBVIEWER_RENDER_H_
