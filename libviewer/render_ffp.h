#ifndef LIBVIEWER_RENDER_FFP_H_
#define LIBVIEWER_RENDER_FFP_H_

#include <OpenGL/gl.h>

#include "render_base.h"

namespace s21 {

template <typename T, typename U>
class RenderFFP : public RenderBase<T, U> {
 public:
  void Initialize(void) override;
  void DrawScene(Scene<T, U> &scene) override;
  ~RenderFFP(void) {}

 private:
  
};

template <typename T, typename U>
void RenderFFP<T, U>::Initialize(void) {
  glEnable(GL_DEPTH_TEST);
  glEnableClientState(GL_VERTEX_ARRAY);
}

template <typename T, typename U>
void RenderFFP<T, U>::DrawScene(Scene<T, U> &scene) {
	(void) scene;
	float color[4] = {0., 0., 0. ,0.};
    for (int i = 0; i < 4; ++i) {
        color[i] = (std::rand() % 256 ) / 256.0f;

    }
    glClearColor((GLfloat)color[0], (GLfloat)color[1], (GLfloat)color[2],
                 (GLfloat)color[3]);
    glClearDepth((GLdouble)1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 //   return;

  std::cout << "1\n";
  if (!scene.IsEmpty()) {
	std::cout << "1\n";
	const Figure<T, U> &figure = scene.GetFigure();
	std::cout << "2\n";
	glLoadIdentity();
	std::cout << "1\n";
	glVertexPointer(4, GL_FLOAT, 0, figure.GetVertices().data());
  }
}

}  // namespace s21

#endif  // LIBVIEWER_RENDER_FFP_H_
