/*
Copyright 2010 Soluvas <http://www.soluvas.com>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

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
