#ifndef NETWORKWRAPPER_H
#define NETWORKWRAPPER_H

#include <QObject>

class QString;
class QNetworkAccessManager;
class QNetworkReply;
class QSslError;
class QNetworkProxy;
class QAuthenticator;

class SolidAuth : public QObject
{
    Q_OBJECT
public:
    explicit SolidAuth(QObject *parent = 0);
    ~SolidAuth();

signals:
    void sigUserCredentialsRequired();
    void sigTextForStatusBar(QString text);
    void sigTokenReady(QString token);


public slots:
    void slAuthenticate(QString login, QString pass);


private slots:
    void slParseAuthReplay(QNetworkReply*reply);
    void slSslError(QNetworkReply *reply, const QList<QSslError> &errors);
    void authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    //void networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility accessible);
    void proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator);
private:
    QNetworkAccessManager *m_network;
    QString m_login;
    QString m_pwd;
    QString m_authToken;
};

#endif // NETWORKWRAPPER_H
