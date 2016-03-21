#include "mainwindow.h"
#include "networkwrapper.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    NetworkWrapper net;

    QObject::connect(&net, SIGNAL(sigTextForStatusBar(QString)), &w, SLOT(slSetStausBarText(QString)));
    w.show();

    return a.exec();
}
