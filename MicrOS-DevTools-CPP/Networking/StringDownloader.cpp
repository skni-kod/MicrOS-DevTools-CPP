#include "StringDownloader.h"

StringDownloader::StringDownloader(Logger *logger, QObject *parent) : Downloader(logger, parent)
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
    logger->logMessage(tr("Rozpoczęto pobieranie pliku: ") + getCurrentUrl().url.toString(), Logger::LogLevel::Info);
    content.clear();
}

void StringDownloader::downloadNewData(QUuid, const QByteArray& byteArray)
{
    content.append(byteArray);
}

void StringDownloader::downloadEnded(QUuid uuid, qint64 elapsedTime)
{
    // Send signal with downloaded data
    logger->logMessage(tr("Zakończono pobieranie pliku: ") + getCurrentUrl().url.toString() +
                       tr(" , czas pobierania: ") + QString::number(static_cast<double>(elapsedTime)/ 1000) + tr(" s"), Logger::LogLevel::Info);
    emit downloadComplete(DownloadResult::Success, getCurrentUrl().url, content, downloadMapData.find(uuid).value().identifier, elapsedTime);

    downloadMapData.remove(uuid);
}

void StringDownloader::downloadFailed(QUuid uuid, qint64 elapsedTime)
{
    // Send signal that download failed
    logger->logMessage(tr("Niepowodzenie pobierania pliku: ") + getCurrentUrl().url.toString() +
                       tr(" , czas pobierania: ") + QString::number(static_cast<double>(elapsedTime)/ 1000) + tr(" s"), Logger::LogLevel::Info);
    emit downloadComplete(DownloadResult::Failed, getCurrentUrl().url, "", downloadMapData.find(uuid).value().identifier, elapsedTime);
    content.clear();

    downloadMapData.remove(uuid);
}

void StringDownloader::downloadRedirected(QUuid uuid, qint64 elapsedTime)
{
    // Send signal that download has been redirected
    logger->logMessage(tr("Przekierowanie podczas pobierania pliku: ") + getCurrentUrl().url.toString() +
                       tr(" , czas pobierania: ") + QString::number(static_cast<double>(elapsedTime)/ 1000) + tr(" s"), Logger::LogLevel::Info);
    emit downloadComplete(DownloadResult::Redirected, getCurrentUrl().url, "", downloadMapData.find(uuid).value().identifier, elapsedTime);
    content.clear();

    downloadMapData.remove(uuid);
}
