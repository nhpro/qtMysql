#include "mainwindow.h"
#include "connsql.h"
#include <QApplication>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowIcon(QIcon(":/images/index.png"));
    w.show();

    return a.exec();
}
