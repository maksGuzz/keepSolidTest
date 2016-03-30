#include "sendrcvjob.h"

#include <QDebug>
#include <QtEndian>

SendRcvJob::SendRcvJob()
    : m_sent(false)
    , m_received(false)
    , m_hasSeqNumRcvd(false)
    , m_hasSizeRcvd(false)
    , m_seqSend(0)
    , m_hdrSend(0)
    , m_seqRcvd(0)
    , m_hdrRcvd(0)
{

}


SendRcvJob::~SendRcvJob()
{

}


quint64 SendRcvJob::appendResponsePart(const QByteArray &resp) // ret: want more bytes. 0 mean done
{
    m_tmp.append(resp);
    if(!m_hasSeqNumRcvd)
    {
        if(m_tmp.size() < 8)
        {
            qDebug() << "too few bytes for SEQ";
            return 8 - m_tmp.size();
        }
        m_seqRcvd = qFromLittleEndian(*((quint64*)m_tmp.data()));//[0];
        qDebug() <<"SEQ:"<<m_seqRcvd;
        m_hasSeqNumRcvd = true;
        m_tmp.remove(0,8);
        qDebug() << "SEQ done";
    }
    if(!m_hasSizeRcvd)
    {
        if(m_tmp.size() < 8)
        {
            qDebug() << "too few bytes for HDR";
            return 8 - m_tmp.size();
        }
        m_hdrRcvd = qFromLittleEndian(*((quint64*)m_tmp.data()));//[0];
        qDebug() <<"HDR:"<<m_hdrRcvd;
        m_hasSizeRcvd = true;
        m_tmp.remove(0,8);
        qDebug() << "HDR done";
    }
    m_response.append(m_tmp);
    m_tmp.clear();

    return m_hdrRcvd - m_response.size();
}

void SendRcvJob::createRequest(const QByteArray &req, int seqNum)
{
    m_seqSend = seqNum;
    m_hdrSend = req.size();

    m_request = req;
}

