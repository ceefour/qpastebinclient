#include "qpastebinclient.h"
#include <QNetworkRequest>
#include <QUrl>
#include <QByteArray>
#include <QNetworkReply>
#include <QtDebug>

QPastebinClient::QPastebinClient(QObject *parent)
    : QObject(parent), m_nam(new QNetworkAccessManager(this))
{
    connect(m_nam, SIGNAL( finished(QNetworkReply*) ),
                   this, SLOT( replyFinished(QNetworkReply*)) );
}

void QPastebinClient::paste(QString text, QString poster, QString format, QString expiry) {
    QNetworkRequest request;
    request.setUrl(QUrl("http://pastebin.com/pastebin.php"));
    //setReferer Referer	http://pastebin.com/pastebin.php
    QByteArray data = "parent_pid=&format=" + QUrl::toPercentEncoding(format) +
                      "&code2=" + QUrl::toPercentEncoding(text) +
                      "&poster=" + QUrl::toPercentEncoding(poster) +
                      "&paste=Send" +
                      "&expiry=" + QUrl::toPercentEncoding(expiry) +
                      "&email=";
    request.setRawHeader("Accept", "text/*");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QString::number(data.size()));
    qDebug() << "POST" << "http://pastebin.com/pastebin.php" << data;
    QNetworkReply *reply = m_nam->post(request, data);
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
        this, SLOT(replyError(QNetworkReply::NetworkError)));
}

void QPastebinClient::replyFinished(QNetworkReply *reply) {
    qDebug() << "Error code:" << reply->error();
    if (reply->header(QNetworkRequest::LocationHeader).isValid()) {
        QString location = reply->header(QNetworkRequest::LocationHeader).toString();
        qDebug() << "Location:" << location;
        finished(location);
    } else {
        qDebug() << "No location :(";
    }
    QByteArray data = reply->readAll();
    qDebug() << "Got reply" << data;
    reply->deleteLater();
}

void QPastebinClient::replyError(QNetworkReply::NetworkError code) {
    QString errorString = ((QNetworkReply *)sender())->errorString();
    qDebug() << "Premature Error:" << code << errorString;
    failed(errorString);
}
