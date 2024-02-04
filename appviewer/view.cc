#include "view.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

#include "./ui_view.h"

namespace s21 {

double calculateMove(double value, double prevValue) {
  double result;
  if (value > prevValue) {
    result = fabs(value - prevValue);
  } else {
    result = -fabs(value - prevValue);
  }
  return result;
}

double caclculateScale(double prevScale, double scale) {
  return scale / prevScale;
}

View::View(Controller &controller, QWidget *parent)
    : controller_(controller), QMainWindow(parent), ui(new Ui::View) {
  ui->setupUi(this);
  setWindowTitle("3DViewer-v2.0");
  DoConnection();

  ui->XvalueForRotate->setMinimum(-360);
  ui->YvalueForRotate->setMinimum(-360);
  ui->ZvalueForRotate->setMinimum(-360);
  ui->XvalueForRotate->setMaximum(360);
  ui->YvalueForRotate->setMaximum(360);
  ui->ZvalueForRotate->setMaximum(360);
  ui->XvalueForTranslate->setMinimum(-999999.99);
  ui->YvalueForTranslate->setMinimum(-999999.99);
  ui->ZvalueForTranslate->setMinimum(-999999.99);
  ui->XvalueForTranslate->setMaximum(999999.99);
  ui->YvalueForTranslate->setMaximum(999999.99);
  ui->ZvalueForTranslate->setMaximum(999999.99);
  ui->valueForScale->setMinimum(0.01);
  ui->valueForScale->setMaximum(999999.99);
  ui->LineSlider->setMaximum(14);
  ui->VertexSlider->setMaximum(14);
}

View::~View() { delete ui; }

void View::DoConnection(void) {
  connect(ui->oglwidget, &OGLWindow::InitializeGLNeeded, &controller_,
          &Controller::InitializeGLHandler);
  connect(ui->oglwidget, &OGLWindow::RedrawNeeded, &controller_,
          &Controller::RedrawGLHandler);
  connect(ui->oglwidget, &OGLWindow::ResizeNeeded, &controller_,
          &Controller::ResizeGLHandler);
  connect(ui->oglwidget, &OGLWindow::ChangeCameraNeeded, &controller_,
          &Controller::ChangeCamera);
  connect(ui->oglwidget, &OGLWindow::GetFrame, this, &s21::View::get_frame);
  connect(ui->plusButtonScale, &QPushButton::clicked, this,
          &View::positiveScale);
  connect(ui->minusButtonScale, &QPushButton::clicked, this,
          &View::negativeScale);
  connect(ui->minusButtonXTranslate, &QPushButton::clicked, this,
          &View::negativeTranslateForX);
  connect(ui->plusButtonXTranslate, &QPushButton::clicked, this,
          &View::positiveTranslateForX);
  connect(ui->plusButtonYTranslate, &QPushButton::clicked, this,
          &View::positiveTranslateForY);
  connect(ui->minusButtonYTranslate, &QPushButton::clicked, this,
          &View::negativeTranslateForY);
  connect(ui->plusButtonZTranslate, &QPushButton::clicked, this,
          &View::positiveTranslateForZ);
  connect(ui->minusButtonZTranslate, &QPushButton::clicked, this,
          &View::negativeTranslateForZ);
  connect(ui->plusButtonXRotate, &QPushButton::clicked, this,
          &View::positiveRotateForX);
  connect(ui->minusButtonXRotate, &QPushButton::clicked, this,
          &View::negativeRotateForX);
  connect(ui->plusButtonYRotate, &QPushButton::clicked, this,
          &View::positiveRotateForY);
  connect(ui->minusButtonYRotate, &QPushButton::clicked, this,
          &View::negativeRotateForY);
  connect(ui->plusButtonZRotate, &QPushButton::clicked, this,
          &View::positiveRotateForZ);
  connect(ui->minusButtonZRotate, &QPushButton::clicked, this,
          &View::negativeRotateForZ);
  connect(ui->colorBackgroundButton, &QPushButton::clicked, this,
          &View::chooseColorBackground);
  connect(ui->colorFaceButton, &QPushButton::clicked, this,
          &View::chooseColorLine);
  connect(ui->colorVertexButton, &QPushButton::clicked, this,
          &View::chooseColorVertex);
}

void View::initialize_base_settings(void) {
  ui->oglwidget->ResetMouseData();
  ui->XvalueForRotate->setValue(0);
  ui->YvalueForRotate->setValue(0);
  ui->ZvalueForRotate->setValue(0);
  ui->XvalueForTranslate->setValue(0);
  ui->YvalueForTranslate->setValue(0);
  ui->ZvalueForTranslate->setValue(0);
  ui->valueForScale->setValue(1);
  ui->LineSlider->setValue((int)SceneSettings::GetInstance().GetLineSize());
  ui->VertexSlider->setValue((int)SceneSettings::GetInstance().GetVertexSize());
  ui->projectionTypeBox->setCurrentIndex(
      static_cast<int>(SceneSettings::GetInstance().GetProjectionType()));
  ui->lineTypeBox->setCurrentIndex(
      static_cast<int>(SceneSettings::GetInstance().GetLineType()));
  ui->vertexTypeBox->setCurrentIndex(
      static_cast<int>(SceneSettings::GetInstance().GetVertexType()));
}

void View::on_action_file_open_triggered(void) {
  QString filename =
      QFileDialog::getOpenFileName(nullptr, "Title", "../..", "*.obj");
  if (!filename.isEmpty()) {
    qDebug() << filename;
    initialize_base_settings();
    if (controller_.LoadObjFile(filename)) {
      ui->oglwidget->ResetMouseData();
      ui->VertexCount->setText(
          QString::number(controller_.GetVerticesNumber()));
      ui->EdgesCount->setText(QString::number(controller_.GetEdgesNumber()));
      ui->PolygonsCount->setText(QString::number(controller_.GetFacesNumber()));
      ui->Filename->setText(filename.split("/").back());
      initialize_base_settings();
      ui->oglwidget->pupdate();
    } else {
      QMessageBox::information(nullptr, "Parse file error",
                               controller_.GetErrorMessage());
    }
  }
}
void View::chooseColorLine() {
  if (controller_.CheckScene()) {
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
    if (color.isValid()) {
      controller_.ColorSettingsLine(color.redF(), color.greenF(),
                                    color.blueF());
      ui->oglwidget->pupdate();
    }
  }
}

void View::chooseColorVertex() {
  if (controller_.CheckScene()) {
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
    if (color.isValid()) {
      controller_.ColorSettingsVertex(color.redF(), color.greenF(),
                                      color.blueF());
      ui->oglwidget->pupdate();
    }
  }
}

void View::chooseColorBackground(void) {
  if (controller_.CheckScene()) {
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
    if (color.isValid()) {
      controller_.ColorSettingsBackground(color.redF(), color.greenF(),
                                          color.blueF());
      ui->oglwidget->pupdate();
    }
  }
}

void View::positiveScale(void) {
  if (controller_.CheckScene()) {
    ui->valueForScale->setValue(ui->valueForScale->value() + 0.15f);
  }
}

void View::negativeScale(void) {
  if (controller_.CheckScene()) {
    ui->valueForScale->setValue(ui->valueForScale->value() - 0.15f);
  }
}

void View::positiveTranslateForX(void) {
  if (controller_.CheckScene()) {
    ui->XvalueForTranslate->setValue(ui->XvalueForTranslate->value() +
                                     controller_.GetDimension() / 10);
  }
}

void View::negativeTranslateForX(void) {
  if (controller_.CheckScene()) {
    ui->XvalueForTranslate->setValue(ui->XvalueForTranslate->value() -
                                     controller_.GetDimension() / 10);
  }
}

void View::positiveTranslateForY(void) {
  if (controller_.CheckScene()) {
    ui->YvalueForTranslate->setValue(ui->YvalueForTranslate->value() +
                                     controller_.GetDimension() / 10);
  }
}

void View::negativeTranslateForY(void) {
  if (controller_.CheckScene()) {
    ui->YvalueForTranslate->setValue(ui->YvalueForTranslate->value() -
                                     controller_.GetDimension() / 10);
  }
}

void View::positiveTranslateForZ(void) {
  if (controller_.CheckScene()) {
    ui->ZvalueForTranslate->setValue(ui->ZvalueForTranslate->value() +
                                     controller_.GetDimension() / 10);
  }
}

void View::negativeTranslateForZ(void) {
  if (controller_.CheckScene()) {
    ui->ZvalueForTranslate->setValue(ui->ZvalueForTranslate->value() -
                                     controller_.GetDimension() / 10);
  }
}

void View::negativeRotateForX(void) {
  if (controller_.CheckScene()) {
    ui->XvalueForRotate->setValue(
        (double)((int)(ui->XvalueForRotate->value() - 5) % (int)(360.)));
  }
}

void View::positiveRotateForX(void) {
  if (controller_.CheckScene()) {
    ui->XvalueForRotate->setValue(
        (double)((int)(ui->XvalueForRotate->value() + 5) % (int)(360.)));
  }
}

void View::negativeRotateForY(void) {
  if (controller_.CheckScene()) {
    ui->YvalueForRotate->setValue(
        (double)((int)(ui->YvalueForRotate->value() - 5) % (int)(360.)));
  }
}

void View::positiveRotateForY(void) {
  if (controller_.CheckScene()) {
    ui->YvalueForRotate->setValue(
        (double)((int)(ui->YvalueForRotate->value() + 5) % (int)(360.)));
  }
}

void View::negativeRotateForZ(void) {
  if (controller_.CheckScene()) {
    ui->ZvalueForRotate->setValue(
        (double)((int)(ui->ZvalueForRotate->value() - 5) % (int)(360.)));
  }
}

void View::positiveRotateForZ(void) {
  if (controller_.CheckScene()) {
    ui->ZvalueForRotate->setValue(
        (double)((int)(ui->ZvalueForRotate->value() + 5) % (int)(360.)));
  }
}

void View::on_XvalueForTranslate_valueChanged(double arg1) {
  if (!controller_.CheckScene()) return;
  static double prevValue = 0;
  double move = calculateMove(arg1, prevValue);
  prevValue = arg1;
  controller_.MoveTranslate(move, 0, 0);
  ui->oglwidget->pupdate();
}

void View::on_YvalueForTranslate_valueChanged(double arg1) {
  if (!controller_.CheckScene()) return;
  static double prevValue = 0;
  double move = calculateMove(arg1, prevValue);
  prevValue = arg1;
  controller_.MoveTranslate(0, move, 0);
  ui->oglwidget->pupdate();
}

void View::on_ZvalueForTranslate_valueChanged(double arg1) {
  if (!controller_.CheckScene()) return;
  static double prevValue = 0;
  double move = calculateMove(arg1, prevValue);
  prevValue = arg1;
  controller_.MoveTranslate(0, 0, move);
  ui->oglwidget->pupdate();
}

void View::on_XvalueForRotate_valueChanged(double arg1) {
  if (!controller_.CheckScene()) return;
  static double prevValue = 0;
  double move = calculateMove(arg1, prevValue);
  prevValue = arg1;
  controller_.MoveRotation(move, 0, 0);
  ui->oglwidget->pupdate();
}

void View::on_YvalueForRotate_valueChanged(double arg1) {
  if (!controller_.CheckScene()) return;
  static double prevValue = 0;
  double move = calculateMove(arg1, prevValue);
  prevValue = arg1;
  controller_.MoveRotation(0, move, 0);
  ui->oglwidget->pupdate();
}

void View::on_ZvalueForRotate_valueChanged(double arg1) {
  if (!controller_.CheckScene()) return;
  static double prevValue = 0;
  double move = calculateMove(arg1, prevValue);
  prevValue = arg1;
  controller_.MoveRotation(0, 0, move);
  ui->oglwidget->pupdate();
}

void View::on_valueForScale_valueChanged(double arg1) {
  if (!controller_.CheckScene()) return;
  static double prevValue = 1.0;
  double scale = caclculateScale(prevValue, arg1);
  prevValue = arg1;
  controller_.MoveScale(scale, scale, scale);
  ui->oglwidget->pupdate();
}

void View::on_lineTypeBox_currentTextChanged(const QString &arg1) {
  size_t option;
  if (arg1 == "Solid")
    option = 0;
  else
    option = 1;
  controller_.LineType(option);
  ui->oglwidget->pupdate();
}

void View::on_vertexTypeBox_currentTextChanged(const QString &arg1) {
  size_t option;
  if (arg1 == "Circle")
    option = 1;
  else if (arg1 == "Square")
    option = 2;
  else
    option = 0;
  controller_.VertexType(option);
  ui->oglwidget->pupdate();
}

void View::on_projectionTypeBox_currentTextChanged(const QString &arg1) {
  size_t option;
  if (arg1 == "Parallel")
    option = 0;
  else
    option = 1;
  controller_.ProjectionType(option);
  ui->oglwidget->pupdate();
}

void View::on_LineSlider_valueChanged(int value) {
  controller_.LineSlider(value);
  ui->oglwidget->pupdate();
}

void View::on_VertexSlider_valueChanged(int value) {
  controller_.VertexSlider(value);
  ui->oglwidget->pupdate();
}

void View::on_makeGifButton_clicked() {
  if (movie) {
    QMessageBox::information(0, "ERROR", "Gif is recording");
    return;
  }
  ui->countFrame->setDisabled(true);
  QMessageBox::information(0, "INFO", "Gif recording started");
  movie = new QGifImage;
  movie->setDefaultDelay(100);
}

void View::on_setFrameButton_clicked() {
  if (!movie) {
    QMessageBox::information(0, "ERROR", "Gif is not recording");
    return;
  }
  get_frame();
}

void View::on_cancelGifButton_clicked() {
  if (movie) delete movie;
  movie = nullptr;
  ui->curFrame->setText(QString::number(0));
  ui->countFrame->setEnabled(true);
}

void View::get_frame() {
  if (movie) {
    int count_frame = ui->countFrame->currentText().toInt();
    ui->curFrame->setText(QString::number(ui->curFrame->text().toInt() + 1));
    if (movie && ui->curFrame->text().toInt() < count_frame) {
      movie->addFrame(ui->oglwidget->grabFramebuffer());
    } else if (movie && ui->curFrame->text().toInt() == count_frame) {
      movie->addFrame(ui->oglwidget->grabFramebuffer());
      QString file_name =
          QFileDialog ::getSaveFileName(NULL, "Title", "../..", "*.gif");
      if (file_name != "") movie->save(file_name);
      ui->curFrame->setText(QString::number(0));
      delete movie;
      movie = nullptr;
      ui->countFrame->setEnabled(true);
    }
  }
}

void View::on_saveImageButton_clicked() {
  QImage image = ui->oglwidget->grabFramebuffer();
  QString file_name = QFileDialog ::getSaveFileName(
      NULL, "Title", "../..", "Images (*.bmp *.jpeg *.png *.xpm *.jpg)");
  if (file_name != "") image.save(file_name);
}

void View::on_resetCamera_clicked() {
  ui->oglwidget->ResetMouseData();
  ui->oglwidget->pupdate();
}

}  // namespace s21
