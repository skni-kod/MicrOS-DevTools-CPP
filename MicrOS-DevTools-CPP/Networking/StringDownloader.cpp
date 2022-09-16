#include "StringDownloader.h"

StringDownloader::StringDownloader(QObject *parent) : Downloader(parent)
{
    connect(this, &Downloader::downloadProgression, this, &StringDownloader::downloadProgress);
}

void StringDownloader::download(QUrl url, QString identifier)
{
    QUuid uuid = QUuid::createUuid();
    downloadMapData.insert(uuid, DownloadData{identifier});
    downloadEnqueue(uuid, url);
}

void StringDownloader::downloadProgress(QUuid uuid, qint64 bytesReceived, qint64 bytesTotal)
{
    emit downloadProgression(downloadMapData.find(uuid).value().identifier, bytesReceived, bytesTotal);
}

void StringDownloader::downloadStart(QUuid)
{
    content.clear();
}

void StringDownloader::downloadNewData(QUuid, const QByteArray& byteArray)
{
    content.append(byteArray);
}

void StringDownloader::downloadEnded(QUuid uuid, qint64 elapsedTime)
{
    // Send signal with downloaded data
    emit downloadComplete(DownloadResult::Success, getCurrentUrl().url, content, downloadMapData.find(uuid).value().identifier, elapsedTime);

    downloadMapData.remove(uuid);
}

void StringDownloader::downloadFailed(QUuid uuid, qint64 elapsedTime)
{
    // Send signal that download failed
    emit downloadComplete(DownloadResult::Failed, getCurrentUrl().url, "", downloadMapData.find(uuid).value().identifier, elapsedTime);
    content.clear();

    downloadMapData.remove(uuid);
}

void StringDownloader::downloadRedirected(QUuid uuid, qint64 elapsedTime)
{
    // Send signal that download has been redirected
    emit downloadComplete(DownloadResult::Redirected, getCurrentUrl().url, "", downloadMapData.find(uuid).value().identifier, elapsedTime);
    content.clear();

    downloadMapData.remove(uuid);
}
