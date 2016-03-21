#ifndef NETWORKWRAPPER_H
#define NETWORKWRAPPER_H

#include <QObject>

class QString;
class QNetworkAccessManager;
class QNetworkReply;

class NetworkWrapper : public QObject
{
    Q_OBJECT
public:
    explicit NetworkWrapper(QObject *parent = 0);
    ~NetworkWrapper();

signals:
    void sigAuthRequired();
    void sigTextForStatusBar(QString text);
    void sigTokenReady(QString token);

public slots:
    void slAuthenticate(QString login, QString pass);

private slots:
    void parseReply(QNetworkReply*);
private:
    QNetworkAccessManager *m_network;
};

#endif // NETWORKWRAPPER_H
