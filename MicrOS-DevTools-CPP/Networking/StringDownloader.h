#ifndef STRINGDOWNLOADER_H
#define STRINGDOWNLOADER_H

#include <QDebug>
#include <QMap>
#include <QString>
#include <QUuid>

#include "Downloader.h"

class StringDownloader : public Downloader
{
    Q_OBJECT

private:
    struct DownloadData
    {
        QString identifier;
    };

private:
    QString content;
    QMap<QUuid, DownloadData> downloadMapData;
public:
    StringDownloader(QObject *parent = nullptr);
    void download(QUrl url, QString identifier);

protected:
    virtual void downloadStart(QUuid uuid);
    virtual void downloadNewData(QUuid uuid, const QByteArray& byteArray);
    virtual void downloadEnded(QUuid uuid, qint64 elapsedTime);
    virtual void downloadFailed(QUuid uuid, qint64 elapsedTime);
    virtual void downloadRedirected(QUuid uuid, qint64 elapsedTime);

signals:
   void downloadResult(Downloader::DownloadResult result, QUrl url, QString identifier, QString content, quint64 elapsedTime);
};

#endif // STRINGDOWNLOADER_H
