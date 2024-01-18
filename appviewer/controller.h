#ifndef APPVIEWER_CONTROLLER_H_
#define APPVIEWER_CONTROLLER_H_

#include <QString>

#include "viewer.h"

namespace s21 {

class Controller
{
 public:
    Controller(Viewer &viewer);

 public:
  bool LoadObjFile(const QString &filename);

 public:
  size_t GetVerticesNumber(void);
  size_t GetEdgesNumber(void);
  size_t GetFacesNumber(void);
  QString GetErrorMessage(void);

 private:
  Viewer &viewer_;
};

}  // namespace s21

#endif  // APPVIEWER_CONTROLLER_H_
