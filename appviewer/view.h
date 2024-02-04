#ifndef APPVIEWER_VIEW_H_
#define APPVIEWER_VIEW_H_

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QtMath>

#include "controller.h"
#include "gifLib/qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(Controller &controller, QWidget *parent = nullptr);
  ~View();

 private:
  void DoConnection(void);
  void initialize_base_settings(void);
  void get_frame();

 private slots:
  void on_action_file_open_triggered(void);

  void chooseColorVertex(void);
  void chooseColorBackground(void);
  void chooseColorLine(void);

  void positiveScale(void);
  void negativeScale(void);

  void positiveTranslateForX(void);
  void negativeTranslateForX(void);
  void positiveTranslateForY(void);
  void negativeTranslateForY(void);
  void positiveTranslateForZ(void);
  void negativeTranslateForZ(void);

  void positiveRotateForX(void);
  void negativeRotateForX(void);
  void positiveRotateForY(void);
  void negativeRotateForY(void);
  void positiveRotateForZ(void);
  void negativeRotateForZ(void);

  void on_XvalueForTranslate_valueChanged(double arg1);
  void on_YvalueForTranslate_valueChanged(double arg1);
  void on_ZvalueForTranslate_valueChanged(double arg1);

  void on_XvalueForRotate_valueChanged(double arg1);
  void on_YvalueForRotate_valueChanged(double arg1);
  void on_ZvalueForRotate_valueChanged(double arg1);

  void on_valueForScale_valueChanged(double arg1);

  void on_lineTypeBox_currentTextChanged(const QString &arg1);
  void on_vertexTypeBox_currentTextChanged(const QString &arg1);
  void on_projectionTypeBox_currentTextChanged(const QString &arg1);
  void on_LineSlider_valueChanged(int value);
  void on_VertexSlider_valueChanged(int value);

  void on_makeGifButton_clicked();
  void on_setFrameButton_clicked();
  void on_cancelGifButton_clicked();

  void on_saveImageButton_clicked();

  void on_resetCamera_clicked();

 private:
  Ui::View *ui;
  Controller &controller_;
  QGifImage *movie;
};

}  // namespace s21

#endif  // APPVIEWER_VIEW_H_
