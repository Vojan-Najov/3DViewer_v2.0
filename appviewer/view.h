#ifndef APPVIEWER_VIEW_H_
#define APPVIEWER_VIEW_H_

#include <QMainWindow>

#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

namespace s21 {

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(Controller & controller, QWidget *parent = nullptr);
    ~View();

private slots:
    void on_action_file_open_triggered(void);

private:
    Ui::View *ui;
    Controller &controller_;
};

}  // namespace s21

#endif // APPVIEWER_VIEW_H_
