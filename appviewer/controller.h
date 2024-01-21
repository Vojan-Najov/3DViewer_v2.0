#ifndef APPVIEWER_CONTROLLER_H_
#define APPVIEWER_CONTROLLER_H_

#include <QString>
#include <QObject>

#include "viewer.h"

namespace s21 {

class Controller : public QObject
{
 Q_OBJECT

 public:
    Controller(Viewer &viewer);

 public:
  bool LoadObjFile(const QString &filename);

 public:
  size_t GetVerticesNumber(void);
  size_t GetEdgesNumber(void);
  size_t GetFacesNumber(void);
  QString GetErrorMessage(void);

  public slots:
    void InitializeGLHandler(void);
    void RedrawGLHandler(int width, int height);
    void ResizeGLHandler(int width, int height);

 private:
  Viewer &viewer_;
};

}  // namespace s21

#endif  // APPVIEWER_CONTROLLER_H_
