#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QFont f2("microsoft yahei");

    a.setFont(f2);

    MainWindow w;
    w.show();
 w.setStyleSheet("font-size:12px;");
    return a.exec();
}
