#ifndef NWTWORKMGR_H
#define NWTWORKMGR_H

#include <QObject>
#include <QSslSocket>


struct SendRcvJob;

class NetworkMgr : public QObject
{
    Q_OBJECT
public:
    explicit NetworkMgr(QObject *parent = 0);
    void setApiServer(const QString &host, qint16 port);
    void doSend();

signals:
    void sigRequestAuthToken();
    void sigJobFinished(SendRcvJob* job);

public slots:
    void beginJob(SendRcvJob* job);
    void connectionReady();
    void reset();

    void dataFromSocket();
    void sslErrors(QList<QSslError> err);


    void displayError(QAbstractSocket::SocketError socketError);
    void doConnect();
private:
    QSslSocket *m_socket;

    QString m_host;
    quint16 m_port;
    quint64 m_seqNumber;
    bool m_connected;
    SendRcvJob *m_job;
};

#endif // NWTWORKMGR_H
