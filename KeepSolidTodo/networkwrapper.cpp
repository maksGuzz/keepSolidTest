#include "networkwrapper.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSslError>

NetworkWrapper::NetworkWrapper(QObject *parent) : QObject(parent)
{
    m_network = new QNetworkAccessManager(this);
    connect(m_network, SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError>&)),this, SLOT(slSslError(QNetworkReply*, const QList<QSslError>&)));
}

NetworkWrapper::~NetworkWrapper()
{
    disconnect();
    delete m_network;
}

void NetworkWrapper::slAuthenticate(QString login, QString pass)
{
    //QNetworkRequest req;
    emit sigTextForStatusBar("Getting auth token...");
    connect(m_network, SIGNAL(finished(QNetworkReply*)), this, SLOT(slParseAuthReplay(QNetworkReply*)));
    m_network->get(QNetworkRequest(QUrl("https://dev-auth.simplexsolutionsinc.com/")));
}

void NetworkWrapper::slParseAuthReplay(QNetworkReply* reply)
{
    qDebug() << reply->errorString();
    qDebug() << reply->readAll();
    m_network->disconnect(this, SLOT(slParseAuthReplay(QNetworkReply*)));
    reply->deleteLater();
}

void NetworkWrapper::slSslError(QNetworkReply *reply, const QList<QSslError> &errors)
{
    qDebug() << "SSL err";
    reply->ignoreSslErrors(errors);
}

void NetworkWrapper::slParseReply(QNetworkReply *)
{

}

