#include "solidauth.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSslError>
#include <QJsonDocument>
#include <QJsonObject>

SolidAuth::SolidAuth(QObject *parent) : QObject(parent)
{
    m_network = new QNetworkAccessManager(this);
    connect(m_network, SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError>&)),this, SLOT(slSslError(QNetworkReply*, const QList<QSslError>&)));
    connect(m_network, SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)),this, SLOT(authenticationRequired(QNetworkReply*, QAuthenticator*)));
    //connect(m_network, SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)),this, SLOT(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)));
    connect(m_network, SIGNAL(proxyAuthenticationRequired(const QNetworkProxy&, QAuthenticator*)),this, SLOT(proxyAuthenticationRequired(const QNetworkProxy&, QAuthenticator*)));
}

SolidAuth::~SolidAuth()
{
    disconnect();
    delete m_network;
}

void SolidAuth::authenticationRequired(QNetworkReply * reply, QAuthenticator * authenticator)
{
    qDebug() << "authenticationRequired";
}

/*void NetworkWrapper::networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility accessible)
{
    qDebug() << "networkAccessibleChanged";
}*/

void SolidAuth::proxyAuthenticationRequired(const QNetworkProxy & proxy, QAuthenticator * authenticator)
{
    qDebug() << "proxyAuthenticationRequired";
}

void SolidAuth::slAuthenticate(QString login, QString pass)
{
    if(login.isEmpty() || pass.isEmpty())
    {
        qDebug()<<"Login/Pass required";
        emit sigUserCredentialsRequired();
    }
    //QNetworkRequest req;
    emit sigTextForStatusBar("Getting auth token...");
    connect(m_network, SIGNAL(finished(QNetworkReply*)), this, SLOT(slParseAuthReplay(QNetworkReply*)));
    QByteArray fields;

    fields.append("action=").append(            QByteArray("login").toBase64()).append("&");
    fields.append("service=").append(           QByteArray("com.braininstock.ToDoChecklist").toBase64()).append("&");
    fields.append("login=").append(             QByteArray(login.toStdString().c_str()).toBase64()).append("&");
    fields.append("password=").append(          QByteArray::fromRawData(pass.toStdString().c_str(), pass.size()).toBase64()).append("&");
    fields.append("device=").append(            QByteArray("Mega secure Device").toBase64()).append("&");
    fields.append("deviceid=").append(          QByteArray("Ubuntu-x64-pc").toBase64()).append("&");
    fields.append("platform=").append(          QByteArray("Linux").toBase64()).append("&");
    fields.append("platformversion=").append(   QByteArray("14.04 LTS").toBase64()).append("&");
    fields.append("appversion=").append(        QByteArray("0.01").toBase64()).append("&");
    fields.append("locale=").append(            QByteArray("en_US").toBase64()).append("&");
    fields.append("timezone=").append(          QByteArray("+0200").toBase64());//.append("&");

    qDebug() << fields;
    qDebug() << "l:" << fields.size();

    QNetworkRequest req;
    req.setUrl(QUrl("https://auth.simplexsolutionsinc.com/"));
    req.setRawHeader(QByteArray("Content-type"), QByteArray("application/x-www-form-urlencoded") );

    QSslConfiguration config = req.sslConfiguration();
    config.setProtocol(QSsl::TlsV1_2OrLater);
    req.setSslConfiguration(config);

    m_network->post(req, fields);
}

void SolidAuth::slParseAuthReplay(QNetworkReply* reply)
{
    QString resp = reply->readAll();
    QString err = reply->errorString();
    QNetworkReply::NetworkError netErr = reply->error();
    if(netErr == QNetworkReply::NoError)
    {
        QJsonDocument d = QJsonDocument::fromJson(resp.toUtf8());
        if(d.isObject())
        {
            QVariantMap respmap = d.object().toVariantMap();
            int respcode = respmap.value("response", int(0)).toInt();
            if(respcode == 200)
            {
                QString token = respmap.value("session", QString("")).toString();
                qDebug() << "Token: " << token;
                emit sigTextForStatusBar(token);
                emit sigTokenReady(token);
            }
            else
            {
                qDebug() << "Error code: " << respcode;
            }
        }
    }
    else
    {
        emit sigTextForStatusBar(err);
        qDebug() << "err: " << err;
        qDebug() << "resp:" << resp;
    }

    m_network->disconnect(this, SLOT(slParseAuthReplay(QNetworkReply*)));
    reply->deleteLater();
}

void SolidAuth::slSslError(QNetworkReply *reply, const QList<QSslError> &errors)
{
    qDebug() << "SSL err";
    reply->ignoreSslErrors(errors);
}
