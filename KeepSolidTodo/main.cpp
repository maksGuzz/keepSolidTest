#include "mainwindow.h"
#include "solidauth.h"
#include "networkmgr.h"
#include "treemodel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
    SolidAuth auth;
    MainWindow w;
    TreeModel m;

    NetworkMgr nmgr;
    //nmgr.setApiServer("rpc.v1.keepsolid.com", 443);
    nmgr.setApiServer("198.7.62.140",6668);

    QObject::connect(&auth, SIGNAL(sigTextForStatusBar(QString)), &w, SLOT(slSetStausBarText(QString)));
    QObject::connect(&w, SIGNAL(sigLogin(QString, QString)), &auth, SLOT(slAuthenticate(QString, QString)));
    QObject::connect(&auth, SIGNAL(sigUserCredentialsRequired()), &w, SLOT(slGetCredentials()));
    QObject::connect(&auth, SIGNAL(sigTokenReady(QString)), &m, SLOT(setAuthToken(QString)));
    QObject::connect(&m, SIGNAL(getData(SendRcvJob*)), &nmgr, SLOT(beginJob(SendRcvJob*)));
    QObject::connect(&nmgr, SIGNAL(sigJobFinished(SendRcvJob*)), &m, SLOT(slJobFinished(SendRcvJob*)));
    QObject::connect(&m, SIGNAL(sigGetToken()), &w, SLOT(slGetCredentials()));

    w.setModel(&m);
    w.show();

    //m.dataQuery();
    w.slGetCredentials();
    //auth.slAuthenticate(QString(), QString());
    //w.slSetStausBarText("start");

    //nmgr.setAuthToken("40649bcc-d828-456e-a3d4-1bf7af082ee8");
    //nmgr.setAuthToken("123");

    return a.exec();
}
