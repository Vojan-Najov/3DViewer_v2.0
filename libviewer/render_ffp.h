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
    // SetViewMatrix(scene);
    SetProjectionMatrix(scene, width, height);
    DrawVertices(scene);
    // DrawFaces(scene);
  }

  glFlush();
}

template <typename T, typename U>
void RenderFFP<T, U>::SetViewMatrix(Scene<T, U> &scene) {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if (!scene.IsEmpty()) {
    // Vertex<T> = scene.GetCamera();
    Figure<T, U> figure = scene.GetFigure();
    T dim = figure.GetDimension();
    Vertex<T> centre = figure.GetCentre();
    Vertex<T> camera{centre.x(), centre.y(), centre.z() + 2 * dim};
    // glTranslatef(-camera.x(), -camera.y(), -camera.z());
    // glTranslatef(centre.x(), centre.y(), centre.z());
  }
}

template <typename T, typename U>
void RenderFFP<T, U>::SetProjectionMatrix(Scene<T, U> &scene, int width,
                                          int height) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  T x_aspect = width > height ? (float)width / (float)height : 1.0;
  T y_aspect = height > width ? (float)height / (float)width : 1.0;

  if (!scene.IsEmpty()) {
    // Vertex<T> = scene.GetCamera();
    Figure<T, U> figure = scene.GetFigure();
    T dim = figure.GetDimension();
    Vertex<T> centre = figure.GetCentre();
    Vertex<T> camera{centre.x(), centre.y(), centre.z() + 2 * dim};
    // glTranslatef(-camera.x(), -camera.y(), -camera.z());
    // glTranslatef(centre.x(), centre.y(), centre.z());

    T ro = centre[2] - camera[2];
    T focal_ro = dim > 1.0e-6 ? dim / 10 : 1;

    T near = focal_ro;
    near = -10;
    T far = -100;
    // T far = -ro + dim > near ? -ro + dim : 2 * near;
    ro = ro < 0 ? -ro : focal_ro;

    std::cout << "centre " << centre[0] << " " << centre[1] << " " << centre[2]
              << '\n';
    std::cout << "left: " << -ro * x_aspect << '\n';
    std::cout << "right: " << ro * x_aspect << '\n';
    std::cout << "bottom: " << -ro * y_aspect << '\n';
    std::cout << "up: " << ro * y_aspect << '\n';
    std::cout << "near: " << near << '\n';
    std::cout << "far: " << far << '\n';

    // glOrtho(-ro * x_aspect, ro * x_aspect, -ro * y_aspect, ro * y_aspect,
    //         near, far);
    glOrtho(-100., 100., -100., 100., -100., 100.);
  }
}

/*
static void set_projection_matrix(int width, int height) {
  vw_model_t *model;
  vw_point_t camera;
  int projection_type;
  float focal_ro, ro, near, far;
  float x_aspect, y_aspect;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  x_aspect = width > height ? (float)width / (float)height : 1.0;
  y_aspect = height > width ? (float)height / (float)width : 1.0;

  vw_scene_get_camera(&camera[0], &camera[1], &camera[2]);
  model = vw_scene_get_model();
  if (model != NULL) {
    ro = model->centre[2] - camera[2];
    projection_type = vw_scene_get_projection_type();
    focal_ro = vw_scene_get_focal_distance();
    if (projection_type == VW_PARALLEL_PROJECTION) {
      near = focal_ro;
      far = -ro + model->dim > near ? -ro + model->dim : 2.0f * near;
      ro = ro < 0.0f ? -ro : focal_ro;

      glOrtho(-ro * x_aspect, ro * x_aspect, -ro * y_aspect, ro * y_aspect,
              near, 10000000);
    } else if (projection_type == VW_CENTRAL_PROJECTION) {
      near = focal_ro;
      far = ro < 0.0f ? -ro + model->dim : model->dim;
      glFrustum(-focal_ro * x_aspect, focal_ro * x_aspect, -focal_ro * y_aspect,
                focal_ro * y_aspect, near, far);
    }
  }
}
*/

template <typename T, typename U>
void RenderFFP<T, U>::DrawVertices(Scene<T, U> &scene) {
  float color[4] = {0, 0, 0, 0};

  if (!scene.IsEmpty()) {
    const Figure<T, U> &figure = scene.GetFigure();
    glColor3f(color[0], color[1], color[2]);
    glPointSize(5.0);
    std::cout << "vn = " << (GLsizei)figure.VerticesNumber() << '\n';
    glDrawArrays(GL_POINTS, (GLint)0, (GLsizei)figure.VerticesNumber());
    std::cout << "Error: " << glGetError() << '\n';
  }
}

/*
static void draw_vertices(vw_model_t *model) {
  float size, ro;
  vw_point_t centre;
  float color[4];
  int vertex_type;

  vertex_type = vw_scene_get_vertex_type();
  if (vertex_type != VW_NONE_VERTEX) {
    vw_scene_get_vertex_color(&color[0], &color[1], &color[2]);
    glColor3f(color[0], color[1], color[2]);
    vw_scene_get_camera(&centre[0], &centre[1], &centre[2]);
    ro = sqrtf(powf(model->centre[0] - centre[0], 2.0) +
               powf(model->centre[1] - centre[1], 2.0) +
               powf(model->centre[2] - centre[2], 2.0));
    ro = ro < 2.0f * model->dim ? 2.0f * model->dim : ro;
    size = vw_scene_get_vertex_size();
    glPointSize(1.0f + size * model->dim / ro);
    if (vertex_type == VW_CIRCLE_VERTEX) {
      glEnable(GL_POINT_SMOOTH);
    } else {
      glDisable(GL_POINT_SMOOTH);
    }
    glDrawArrays(GL_POINTS, (GLint)0, (GLsizei)model->number_of_vertices);
  }
}
*/

template <typename T, typename U>
void RenderFFP<T, U>::DrawFaces(Scene<T, U> &scene) {
  float color[4] = {0, 0, 0, 0};

  if (!scene.IsEmpty()) {
    const Figure<T, U> &figure = scene.GetFigure();
    glColor3f(color[0], color[1], color[2]);
    glLineWidth(10);
    std::vector<Face<U>> faces = figure.GetFaces();
    using fit = typename std::vector<Face<U>>::const_iterator;

    for (fit it = faces.begin(), last = faces.end(); it != last; ++it) {
      glDrawElements(GL_LINE_LOOP, it->Size(), GL_UNSIGNED_INT, it->data());
      // std::cout << "Error: " << glGetError() << '\n';
    }
  }
}

/*
static void draw_faces(vw_model_t *model) {
  float size, ro;
  vw_point_t centre;
  float color[4];

  vw_scene_get_line_color(&color[0], &color[1], &color[2]);
  glColor3f(color[0], color[1], color[2]);
  size = vw_scene_get_line_size();
  vw_scene_get_camera(&centre[0], &centre[1], &centre[2]);
  ro = sqrtf(powf(model->centre[0] - centre[0], 2.0) +
             powf(model->centre[1] - centre[1], 2.0) +
             powf(model->centre[2] - centre[2], 2.0));
  ro = ro < 2.0f * model->dim ? 2.0f * model->dim : ro;
  glLineWidth(1.0f + size * 2.0f * model->dim / ro);
  glEnable(GL_LINE_SMOOTH);
  if (vw_scene_get_line_type() == VW_DASHED_LINE) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  for (size_t i = 0; i < model->number_of_faces; ++i) {
    glDrawElements(GL_LINE_LOOP, model->faces[i].number_of_idx, GL_UNSIGNED_INT,
                   model->faces[i].idx);
  }
}

*/

template <typename T, typename U>
void RenderFFP<T,U>::ResizeViewport(int width, int height) {
  glViewport(0, 0, width, height);
}


}  // namespace s21

#endif  // LIBVIEWER_RENDER_FFP_H_
