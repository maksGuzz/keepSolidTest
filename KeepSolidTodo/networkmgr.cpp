#include "networkmgr.h"

#include "sendrcvjob.h"

#include <QSslConfiguration>
#include <QtEndian>



NetworkMgr::NetworkMgr(QObject *parent)
    : QObject(parent)
    , m_seqNumber(0)
    , m_connected(false)
    , m_job(NULL)
{
    m_socket = new QSslSocket(this);

    connect(m_socket, SIGNAL(encrypted()), this, SLOT(connectionReady()));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(dataFromSocket()));
    connect(m_socket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslErrors(QList<QSslError>)));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

}


void NetworkMgr::setApiServer(const QString &host, qint16 port)
{
    m_host = host;
    m_port = port;
}


void NetworkMgr::doSend()
{
    qDebug() << "doSend";
    quint64 num = qToLittleEndian(m_job->m_seqSend);
    quint64 sz = qToLittleEndian(m_job->m_hdrSend);

    m_socket->write((const char*)&num,8);
    m_socket->write((const char*)&sz ,8);
    m_socket->write(m_job->m_request);
}


void NetworkMgr::beginJob(SendRcvJob* job)
{
    qDebug() << "beginJob";
    if(m_job!=NULL)
    {
        //job in progress
        emit sigJobFinished(job);
        return;
    }
    m_job = job;

    doConnect();
    doSend();
}


void NetworkMgr::connectionReady()
{
    qDebug() << "connected";
    if(m_job)
    {
        doSend();
    }
}

void NetworkMgr::reset()
{
    m_socket->close();
}


void NetworkMgr::dataFromSocket()
{

    qDebug() << "dataFromSocket";
    qDebug() << "SZ from sock" << m_socket->bytesAvailable();
    QByteArray in;

    in = m_socket->readAll();
    quint64 left = m_job->appendResponsePart(in);
    qDebug()<<"BYTES LEFT:"<<left;
    if(left==0)
    {
        qDebug() << "All data in place";
        m_seqNumber = m_job->m_seqRcvd + 1;
        qDebug() << "job:"<<m_job;
        emit sigJobFinished(m_job);
        m_job=NULL;
    }
    else
    {
        qDebug() <<"waiting more data";
    }
}

void NetworkMgr::sslErrors(QList<QSslError> err)
{
    qDebug() << "qSslError";
    foreach (QSslError e, err)
    {
       qDebug() << e.errorString();
    }

    m_socket->ignoreSslErrors();
}

void NetworkMgr::displayError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "SOCKET ERR:";
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        qDebug() << "Conn closed";
        m_connected = false;
        qDebug() << "job:"<<m_job;
        emit sigJobFinished(m_job); //remove job ?
        m_job=NULL;
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "Host not found";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "refused";
        break;
    default:
        qDebug() <<  m_socket->errorString();
    }
}

void NetworkMgr::doConnect()
{
    qDebug() << "doConnect";
    if(!m_connected)
    {
        qDebug() << "!connected, connecting...";
        m_socket->connectToHostEncrypted(m_host, m_port);
    }
}



