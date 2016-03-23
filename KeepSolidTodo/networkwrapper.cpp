#include "networkwrapper.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSslError>
#include <QJsonDocument>
#include <QJsonObject>

NetworkWrapper::NetworkWrapper(QObject *parent) : QObject(parent)
{
    m_network = new QNetworkAccessManager(this);
    connect(m_network, SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError>&)),this, SLOT(slSslError(QNetworkReply*, const QList<QSslError>&)));
    connect(m_network, SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)),this, SLOT(authenticationRequired(QNetworkReply*, QAuthenticator*)));
    //connect(m_network, SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)),this, SLOT(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)));
    connect(m_network, SIGNAL(proxyAuthenticationRequired(const QNetworkProxy&, QAuthenticator*)),this, SLOT(proxyAuthenticationRequired(const QNetworkProxy&, QAuthenticator*)));
}

NetworkWrapper::~NetworkWrapper()
{
    disconnect();
    delete m_network;
}

void NetworkWrapper::authenticationRequired(QNetworkReply * reply, QAuthenticator * authenticator)
{
    qDebug() << "authenticationRequired";
}

/*void NetworkWrapper::networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility accessible)
{
    qDebug() << "networkAccessibleChanged";
}*/

void NetworkWrapper::proxyAuthenticationRequired(const QNetworkProxy & proxy, QAuthenticator * authenticator)
{
    qDebug() << "proxyAuthenticationRequired";
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

    //m_network->post(req, fields);
    slParseAuthReplay(NULL);
    //qDebug() << "{\n    \"cryptokeys\": {\n        \"active\": true,\n        \"id\": 4333780,\n        \"login\": \"kscheck002@mailinator.com\",\n        \"private_key\": \"-----BEGIN ENCRYPTED PRIVATE KEY-----\\nMIIFDjBABgkqhkiG9w0BBQ0wMzAbBgkqhkiG9w0BBQwwDgQI0/e9ypgWJvECAggA\\nMBQGCCqGSIb3DQMHBAjV+B1hbVekEQSCBMjXxeP9NiJzZreDQ0Lz4pPqr6jy67O6\\nVQDCg093aQjxFYoPNvnxpbXTM4D6m6OPNCZY4lQoJIceibNhhZ70+QAtXwkBkN9Q\\nDwC0GVU60D46Gm5GEDG8/YfKH9N+nX+5lM1bRvZvbL3Lm2TcMczQWnDN27mO0U45\\ntR0/qJz1r6l6Ws8A092MctWlnGG5GK0DM98JWOg2YDHH8Ku2S/hDYSVsavyV4h6t\\nDY2m009nDeRugZ4RK22qxcRh6OCIfJeLK1lwegK1e+dMmklgyaFPcf+dMmCZcCqa\\nBdaFdv5iiUppTkQOwLt5fM+bUC7IPUSZa9d/XJoxv93GNzj99wzxJ4x/jdq7SjD8\\n6ijnZkpGkHp3yPaPJSqiG/4EpO75yrd0i3P9d8DpBPsyMUq5NygdaiXNfo5ibp1I\\n2CMSRjhosuIb8YwyeCG8qM3EvavsmVHjJybsFT8foVyrI44WhWa36tF4yHueh4qx\\nIcg9bKEEYtMhkhqkv1suqy6hIfpkkg0109MZ+0sXeSVTtPKvEEzhluJUkO7Uuo/F\\nCstjyASAks78DBq/PuOoScmmPD0Gvr9KwaV7busEV9+hTH3kfSHg7o2haz+A3Cw1\\nddx8aBbCui6r3uIELJBxzHxaFZ2Nm/t34OYfNuMNki0kzNO9tU6V0uIbLuKO2O9t\\n9Jr3XTSTcewVpGyfvKR9py8e4fHaWhgKAWfdQIzUvQpH3BlD6oJc7lbyWe5zniT9\\nUB2ips4RLceBw4OGmkZprmuDbxrzgx8IOcfc69AzEUiDj0D+4pZ/JnDU/rRZjvxb\\nQvcpeAemIbz7iyO0/uhVZCVaziW2GrLC3zrwowOMv6QPEKn5VH9WMdYmZqsyzhJA\\nrNVJwqgfgW5vD/eTi7+U0UcdmbtMS7aoQ7lf8DtALrA2A82oNUg/GuKbnlVmH6NI\\n1ZvQ3Aktc8ozDi+C2ryinfJm7DHz6OE8iyIg8B28H2Ed8eLRLCRsHAMJXsKeqfQ5\\nj2aRFArS4nVbbSteXi1yTFp7l6tk3NAYum7A2EnlLX3sdh5GsRSKiN1N71pDcJlz\\nI9q4ukuDPHX7i3Jm2GXqmqe7oAWhcBbQqxl+lV55qUWSoVvh8GC37Pik6C0eIav2\\n47ujM8oaG7s7safMyHXRSMgvrKo4ZK98sD+4RWQi4pJq/O3t3dp1Xfa5Umq32VL2\\nA8E6GoGVL1Bba1/e6oUNCIbZ/p1sh9GPXwD3jx0VLQeG0PYg9jEE397rNka5YklL\\nPmNRZP+ZamSD3jLiIxGA40oxJao+C4ErHfBwYXS9ZFMFeh+WbFeao+Cant1dMDrD\\nX/4JJztTolycwRLMP96jAisuAih1+o1cHKaiT9xIMBkVjlQI8AWxdcFO2lyF0PUc\\nViQY5mHzAin256TR9C4KsDGIv1CPhGo1AOkM6EUZJc1vF1/N1oC3iStVwId3NYyf\\nScMPcxjRXap/BWwjJv+n6kYO/0E7W+Wjnrk6XhDegvS4ok+KZ8P1t+At+iNcty1r\\nQJSK4JJX2Cpp0UAYZ//ZuSqYKyZmwtQ8Nwcnixlm3d3N+6IozUD3oE/mzlK6YXLg\\nzbbS4Zebn4skF7loykZD4ffWwEhZ7werP6u5reQp2uPiYN988n49AGEq/0LG5NUY\\nxp8=\\n-----END ENCRYPTED PRIVATE KEY-----\\n\",\n        \"private_key_salt\": \"sha256$32768$zJsbUh9D4gOTJ+J988p0YsDrFLA+SThi/lFhDF5xMXY=\",\n        \"public_key\": \"-----BEGIN PUBLIC KEY-----\\nMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA24mEVZTZ57lckPcMhPQz\\nDoUE1F31Jjjk0Ysi6ZICfzcqA2R9TBUwB6s+StXJAoPhzunTT4D2ev7e2AEyoERG\\nJrHYuh6v2S0IxCIGMK6aX4gUZTKVZxJRa+J3CnJ05hQs0fHDeIttdNKuL++cNMkC\\nRMZMHNHbHLIMrdSz/+uMEGwvBdi4FN3wnGYj90kI4RT3UdVDxF3HPIz82Di2Yeb8\\naizGzwh8qDBVct95uRpN/Y62hnk3tS1n4PuASkgpLxARh8/xoSvO+dJqv7vYlGWd\\n7XG8RlSORnzYT92UrWCn6xM6ius9UJhEBskoHe0yT2JohxhJcpSmVbe8KGXA3RO4\\nOQIDAQAB\\n-----END PUBLIC KEY-----\\n\",\n        \"type\": \"native\",\n        \"username\": \"kscheck002@mailinator.com\"\n    },\n    \"eventsession\": \"cb6ee1a2-de0b-4aed-98fe-aaf3704ab1b5\",\n    \"response\": 200,\n    \"session\": \"86680bb5-a2fd-402b-a360-ea7e75b46390\",\n    \"userinfo\": {\n        \"autologin_url\": \"https://my.keepsolid.com/auth/86680bb5_a2fd_402b_a360_ea7e75b46390/2ed1597593869f578f1488e42f5e4fc65345af79dae830fcdd1a3b7303e18d56/ad85d420926a60a922c6ced9c1b89de2817886ba8b2fff137d757f5202e24ed9\",\n        \"avatar\": null,\n        \"balance_paid\": 0,\n        \"balance_rewards\": 0,\n        \"ban_reason\": null,\n        \"banned\": false,\n        \"confirmation_datetime\": null,\n        \"confirmed\": true,\n        \"extra_devices\": 0,\n        \"firstlogin\": false,\n        \"firstname\": \"\",\n        \"id\": 2444663,\n        \"invites_available\": true,\n        \"lastlogin\": \"1458727649.08838\",\n        \"lastname\": \"\",\n        \"login_type\": \"native\",\n        \"name\": \"kscheck002@mailinator.com\",\n        \"need_confirmation\": false,\n        \"registration_datetime\": \"1446107953.16882\",\n        \"subscription\": \"weekly\",\n        \"trial\": true,\n        \"username\": \"kscheck002@mailinator.com\"\n    },\n    \"ws_session\": \"6b74b27f-d269-45b4-8ae3-d4bcc5a98622\"\n}\n";
}

void NetworkWrapper::slParseAuthReplay(QNetworkReply* reply)
{
    /*QString resp = reply->readAll();
    QString err = reply->errorString();
    QNetworkReply::NetworkError netErr = reply->error();*/
    if(1)//netErr == QNetworkReply::NoError)
    {
        //QJsonDocument d = QJsonDocument::fromJson(resp.toUtf8());
        QJsonDocument d = QJsonDocument::fromJson("{\n    \"cryptokeys\": {\n        \"active\": true,\n        \"id\": 4333780,\n        \"login\": \"kscheck002@mailinator.com\",\n        \"private_key\": \"-----BEGIN ENCRYPTED PRIVATE KEY-----\\nMIIFDjBABgkqhkiG9w0BBQ0wMzAbBgkqhkiG9w0BBQwwDgQI0/e9ypgWJvECAggA\\nMBQGCCqGSIb3DQMHBAjV+B1hbVekEQSCBMjXxeP9NiJzZreDQ0Lz4pPqr6jy67O6\\nVQDCg093aQjxFYoPNvnxpbXTM4D6m6OPNCZY4lQoJIceibNhhZ70+QAtXwkBkN9Q\\nDwC0GVU60D46Gm5GEDG8/YfKH9N+nX+5lM1bRvZvbL3Lm2TcMczQWnDN27mO0U45\\ntR0/qJz1r6l6Ws8A092MctWlnGG5GK0DM98JWOg2YDHH8Ku2S/hDYSVsavyV4h6t\\nDY2m009nDeRugZ4RK22qxcRh6OCIfJeLK1lwegK1e+dMmklgyaFPcf+dMmCZcCqa\\nBdaFdv5iiUppTkQOwLt5fM+bUC7IPUSZa9d/XJoxv93GNzj99wzxJ4x/jdq7SjD8\\n6ijnZkpGkHp3yPaPJSqiG/4EpO75yrd0i3P9d8DpBPsyMUq5NygdaiXNfo5ibp1I\\n2CMSRjhosuIb8YwyeCG8qM3EvavsmVHjJybsFT8foVyrI44WhWa36tF4yHueh4qx\\nIcg9bKEEYtMhkhqkv1suqy6hIfpkkg0109MZ+0sXeSVTtPKvEEzhluJUkO7Uuo/F\\nCstjyASAks78DBq/PuOoScmmPD0Gvr9KwaV7busEV9+hTH3kfSHg7o2haz+A3Cw1\\nddx8aBbCui6r3uIELJBxzHxaFZ2Nm/t34OYfNuMNki0kzNO9tU6V0uIbLuKO2O9t\\n9Jr3XTSTcewVpGyfvKR9py8e4fHaWhgKAWfdQIzUvQpH3BlD6oJc7lbyWe5zniT9\\nUB2ips4RLceBw4OGmkZprmuDbxrzgx8IOcfc69AzEUiDj0D+4pZ/JnDU/rRZjvxb\\nQvcpeAemIbz7iyO0/uhVZCVaziW2GrLC3zrwowOMv6QPEKn5VH9WMdYmZqsyzhJA\\nrNVJwqgfgW5vD/eTi7+U0UcdmbtMS7aoQ7lf8DtALrA2A82oNUg/GuKbnlVmH6NI\\n1ZvQ3Aktc8ozDi+C2ryinfJm7DHz6OE8iyIg8B28H2Ed8eLRLCRsHAMJXsKeqfQ5\\nj2aRFArS4nVbbSteXi1yTFp7l6tk3NAYum7A2EnlLX3sdh5GsRSKiN1N71pDcJlz\\nI9q4ukuDPHX7i3Jm2GXqmqe7oAWhcBbQqxl+lV55qUWSoVvh8GC37Pik6C0eIav2\\n47ujM8oaG7s7safMyHXRSMgvrKo4ZK98sD+4RWQi4pJq/O3t3dp1Xfa5Umq32VL2\\nA8E6GoGVL1Bba1/e6oUNCIbZ/p1sh9GPXwD3jx0VLQeG0PYg9jEE397rNka5YklL\\nPmNRZP+ZamSD3jLiIxGA40oxJao+C4ErHfBwYXS9ZFMFeh+WbFeao+Cant1dMDrD\\nX/4JJztTolycwRLMP96jAisuAih1+o1cHKaiT9xIMBkVjlQI8AWxdcFO2lyF0PUc\\nViQY5mHzAin256TR9C4KsDGIv1CPhGo1AOkM6EUZJc1vF1/N1oC3iStVwId3NYyf\\nScMPcxjRXap/BWwjJv+n6kYO/0E7W+Wjnrk6XhDegvS4ok+KZ8P1t+At+iNcty1r\\nQJSK4JJX2Cpp0UAYZ//ZuSqYKyZmwtQ8Nwcnixlm3d3N+6IozUD3oE/mzlK6YXLg\\nzbbS4Zebn4skF7loykZD4ffWwEhZ7werP6u5reQp2uPiYN988n49AGEq/0LG5NUY\\nxp8=\\n-----END ENCRYPTED PRIVATE KEY-----\\n\",\n        \"private_key_salt\": \"sha256$32768$zJsbUh9D4gOTJ+J988p0YsDrFLA+SThi/lFhDF5xMXY=\",\n        \"public_key\": \"-----BEGIN PUBLIC KEY-----\\nMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA24mEVZTZ57lckPcMhPQz\\nDoUE1F31Jjjk0Ysi6ZICfzcqA2R9TBUwB6s+StXJAoPhzunTT4D2ev7e2AEyoERG\\nJrHYuh6v2S0IxCIGMK6aX4gUZTKVZxJRa+J3CnJ05hQs0fHDeIttdNKuL++cNMkC\\nRMZMHNHbHLIMrdSz/+uMEGwvBdi4FN3wnGYj90kI4RT3UdVDxF3HPIz82Di2Yeb8\\naizGzwh8qDBVct95uRpN/Y62hnk3tS1n4PuASkgpLxARh8/xoSvO+dJqv7vYlGWd\\n7XG8RlSORnzYT92UrWCn6xM6ius9UJhEBskoHe0yT2JohxhJcpSmVbe8KGXA3RO4\\nOQIDAQAB\\n-----END PUBLIC KEY-----\\n\",\n        \"type\": \"native\",\n        \"username\": \"kscheck002@mailinator.com\"\n    },\n    \"eventsession\": \"cb6ee1a2-de0b-4aed-98fe-aaf3704ab1b5\",\n    \"response\": 200,\n    \"session\": \"86680bb5-a2fd-402b-a360-ea7e75b46390\",\n    \"userinfo\": {\n        \"autologin_url\": \"https://my.keepsolid.com/auth/86680bb5_a2fd_402b_a360_ea7e75b46390/2ed1597593869f578f1488e42f5e4fc65345af79dae830fcdd1a3b7303e18d56/ad85d420926a60a922c6ced9c1b89de2817886ba8b2fff137d757f5202e24ed9\",\n        \"avatar\": null,\n        \"balance_paid\": 0,\n        \"balance_rewards\": 0,\n        \"ban_reason\": null,\n        \"banned\": false,\n        \"confirmation_datetime\": null,\n        \"confirmed\": true,\n        \"extra_devices\": 0,\n        \"firstlogin\": false,\n        \"firstname\": \"\",\n        \"id\": 2444663,\n        \"invites_available\": true,\n        \"lastlogin\": \"1458727649.08838\",\n        \"lastname\": \"\",\n        \"login_type\": \"native\",\n        \"name\": \"kscheck002@mailinator.com\",\n        \"need_confirmation\": false,\n        \"registration_datetime\": \"1446107953.16882\",\n        \"subscription\": \"weekly\",\n        \"trial\": true,\n        \"username\": \"kscheck002@mailinator.com\"\n    },\n    \"ws_session\": \"6b74b27f-d269-45b4-8ae3-d4bcc5a98622\"\n}\n");
        //qDebug() << "J:" << QString(d.toJson().constData());
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
    /*else
    {
        emit sigTextForStatusBar(err);
        qDebug() << "err: " << err;
        qDebug() << "resp:" << resp;
    }

    m_network->disconnect(this, SLOT(slParseAuthReplay(QNetworkReply*)));
    reply->deleteLater();*/
}

void NetworkWrapper::slSslError(QNetworkReply *reply, const QList<QSslError> &errors)
{
    qDebug() << "SSL err";
    reply->ignoreSslErrors(errors);
}

void NetworkWrapper::slParseReply(QNetworkReply *)
{

}

