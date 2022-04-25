#include "widget.h"

#include <QApplication>
#include"dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow* mw = new MainWindow();
//    QPaintWidget w(mw);
//    w.show();
    Dialog dial;
    dial.show();
    return a.exec();
}
