#ifndef QPASTEBINCLIENT_H
#define QPASTEBINCLIENT_H

#include <QNetworkAccessManager>
#include <QNetworkReply>

/**
  * URL: http://pastebin.com/pastebin.php
  * parent_pid=""
  * format=text
  * code2={code}
  * poster={poster}
  * expiry=d|m|f
  */
class QPastebinClient : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager *m_nam;
private slots:
    void replyFinished(QNetworkReply *reply);
    void replyError(QNetworkReply::NetworkError code);
public:
    QPastebinClient(QObject *parent);
    void paste(QString text, QString poster = "", QString format = "text", QString expiry = "m");
signals:
    void finished(QString url);
    void failed(QString errorString);
};

#endif // PASTEBINCLIENT_H
