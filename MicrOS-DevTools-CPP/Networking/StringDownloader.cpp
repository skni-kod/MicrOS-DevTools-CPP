#include "StringDownloader.h"

StringDownloader::StringDownloader(QObject *parent) : Downloader(parent)
{

}

void StringDownloader::download(QUrl url, QString identifier)
{
    QUuid uuid = QUuid::createUuid();
    downloadMapData.insert(uuid, DownloadData{identifier});
    downloadEnqueue(uuid, url);
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
    downloadResult(DownloadResult::Success, getCurrentUrl().url, content, downloadMapData.find(uuid).value().identifier, elapsedTime);
    qDebug() << "Downloaded: " << content << " ,Url: " << getCurrentUrl().url << " ,Uuid: " << uuid << " ,Elapsed time: " << elapsedTime;

    downloadMapData.remove(uuid);
}

void StringDownloader::downloadFailed(QUuid uuid, qint64 elapsedTime)
{
    // Send signal that download failed
    downloadResult(DownloadResult::Failed, getCurrentUrl().url, "", downloadMapData.find(uuid).value().identifier, elapsedTime);
    content.clear();

    downloadMapData.remove(uuid);
}

void StringDownloader::downloadRedirected(QUuid uuid, qint64 elapsedTime)
{
    // Send signal that download has been redirected
    downloadResult(DownloadResult::Redirected, getCurrentUrl().url, "", downloadMapData.find(uuid).value().identifier, elapsedTime);
    content.clear();

    downloadMapData.remove(uuid);
}
