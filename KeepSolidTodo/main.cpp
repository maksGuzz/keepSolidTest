#include "mainwindow.h"
#include "networkwrapper.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NetworkWrapper net;
    MainWindow w;

    QObject::connect(&net, SIGNAL(sigTextForStatusBar(QString)), &w, SLOT(slSetStausBarText(QString)));
    QObject::connect(&w, SIGNAL(sigLogin(QString, QString)), &net, SLOT(slAuthenticate(QString, QString)));
    QObject::connect(&net, SIGNAL(sigUserCredentialsRequired()), &w, SLOT(slGetCredentials()));
    w.show();
    net.slAuthenticate(QString(), QString());

    return a.exec();
}
