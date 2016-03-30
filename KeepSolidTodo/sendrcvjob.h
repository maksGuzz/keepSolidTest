#ifndef SENDRCVJOB_H
#define SENDRCVJOB_H

#include <QByteArray>

struct SendRcvJob // inherit from QObject ?...
{
    bool m_sent;
    bool m_received;

    bool m_hasSeqNumRcvd;
    bool m_hasSizeRcvd;

    quint64 m_seqSend;
    quint64 m_hdrSend;
    quint64 m_seqRcvd;
    quint64 m_hdrRcvd;

    QByteArray m_request;//pb serialized
    QByteArray m_response;

    QByteArray m_tmp;

    SendRcvJob();
    ~SendRcvJob();

    quint64 appendResponsePart(const QByteArray &resp); // ret: want more bytes. 0 mean done
    void createRequest(const QByteArray &req, int seqNum = 0);

};

#endif // SENDRCVJOB_H
