#include <QApplication>

#include "view.h"
#include "controller.h"
#include "viewer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    s21::Viewer model;
    s21::Controller controller{model};
    s21::View view{controller};

    view.show();

    return app.exec();
}
