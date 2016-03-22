#ifndef NETWORKWRAPPER_H
#define NETWORKWRAPPER_H

#include <QObject>

class QString;
class QNetworkAccessManager;
class QNetworkReply;
class QSslError;

class NetworkWrapper : public QObject
{
    Q_OBJECT
public:
    explicit NetworkWrapper(QObject *parent = 0);
    ~NetworkWrapper();

signals:
    void sigUserCredentialsRequired();
    void sigTextForStatusBar(QString text);
    void sigTokenReady(QString token);


public slots:
    void slAuthenticate(QString login, QString pass);

private slots:
    void slParseReply(QNetworkReply*);
    void slParseAuthReplay(QNetworkReply*reply);
    void slSslError(QNetworkReply *reply, const QList<QSslError> &errors);
private:
    QNetworkAccessManager *m_network;
    QString m_login;
    QString m_pwd;
    QString m_authToken;
};

#endif // NETWORKWRAPPER_H
