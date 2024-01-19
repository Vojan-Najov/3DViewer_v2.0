#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>


#include "view.h"
#include "./ui_view.h"

namespace s21 {

View::View(Controller &controller, QWidget *parent)
    : controller_(controller)
    , QMainWindow(parent)
    , ui(new Ui::View)
{
    ui->setupUi(this);
    connect(ui->oglwidget, &OGLWindow::redraw, &controller_, &Controller::DrawScene);
    connect(ui->oglwidget, &OGLWindow::InitializeGLNeeded, &controller_, &Controller::InitializeGLHandler);
}

View::~View()
{
    delete ui;
}

void View::on_action_file_open_triggered(void) {
  QString filename = QFileDialog::getOpenFileName(nullptr, "Title", "../..", "*.obj");
  if (!filename.isEmpty()) {
      qDebug() << filename;
      //initializeTransmitions();
      //initializeCustomization();
      if (controller_.LoadObjFile(filename)) {
        ui->VertexCount->setText(QString::number(controller_.GetVerticesNumber()));
        ui->EdgesCount->setText(QString::number(controller_.GetEdgesNumber()));
        ui->PolygonsCount->setText(QString::number(controller_.GetFacesNumber()));
        ui->Filename->setText(filename.split("/").back());
        // updateScene
      } else {
          QMessageBox::information(nullptr, "Parse file error", controller_.GetErrorMessage());
      }
  }

}

}  // namespace s21
