#include "networkwrapper.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

NetworkWrapper::NetworkWrapper(QObject *parent) : QObject(parent)
{
    m_network = new QNetworkAccessManager(this);
    //connect(m_network, SIGNAL(finished(QNetworkReply*)),this, SLOT(parseReply(QNetworkReply*)));
}

NetworkWrapper::~NetworkWrapper()
{
    disconnect();
    delete m_network;
}

void NetworkWrapper::slAuthenticate(QString login, QString pass)
{
    //QNetworkRequest req;
    // connect request to slParseAuthRply()
}

void NetworkWrapper::parseReply(QNetworkReply *)
{

}

