#include "networkwrapper.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSslError>
#include <QJsonDocument>

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
    QByteArray fields;

    fields.append("action=").append(            QByteArray("login").toBase64()).append("&");
    fields.append("service=").append(           QByteArray("com.braininstock.ToDoChecklist").toBase64()).append("&");
    fields.append("login=").append(             QByteArray("kscheck001@mailinator.com").toBase64()).append("&");
    fields.append("password=").append(          QByteArray("123456").toBase64()).append("&");
    fields.append("deviceid=").append(          QByteArray("Ubuntu-x64-pc").toBase64()).append("&");
    fields.append("platform=").append(          QByteArray("Linux").toBase64()).append("&");
    fields.append("platformversion=").append(   QByteArray("14.04 LTS").toBase64()).append("&");
    fields.append("appversion=").append(        QByteArray("0.01").toBase64()).append("&");
    fields.append("locale=").append(            QByteArray("en_US").toBase64()).append("&");
    fields.append("timezone=").append(          QByteArray("+0200").toBase64());//.append("&");

    qDebug() << fields;

    QNetworkRequest req;
    req.setUrl(QUrl("https://dev-auth.simplexsolutionsinc.com/"));
    req.setRawHeader(QByteArray("Content-type"), QByteArray("application/x-www-form-urlencoded") );

    m_network->post(req, fields);
}

void NetworkWrapper::slParseAuthReplay(QNetworkReply* reply)
{
    QString resp = reply->readAll();
    QString err = reply->errorString();
    qDebug() << "err: " << err;
    qDebug() << "resp:" << resp;
    m_network->disconnect(this, SLOT(slParseAuthReplay(QNetworkReply*)));
    reply->deleteLater();
    QJsonDocument d = QJsonDocument::fromJson(resp.toUtf8());
    qDebug() << "J:" << d;
}

void NetworkWrapper::slSslError(QNetworkReply *reply, const QList<QSslError> &errors)
{
    qDebug() << "SSL err";
    reply->ignoreSslErrors(errors);
}

void NetworkWrapper::slParseReply(QNetworkReply *)
{

}

