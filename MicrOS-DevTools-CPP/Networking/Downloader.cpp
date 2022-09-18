#include "Downloader.h"

Downloader::Downloader(Logger *logger, QObject *parent) : QObject(parent)
{
    this->logger = logger;
}

void Downloader::downloadEnqueue(QUuid uuid, QUrl url)
{
    downloadQueue.enqueue(UuidUrl{uuid, url});

    // If download already is in progress, calling startNextDownload is not needed.
    // It will be called at the end of downloadFinished().
    downloadingMutex.lock();
    if(downloading == false)
    {
        QTimer::singleShot(0, this, &Downloader::startNextDownload);
    }
    downloadingMutex.unlock();
}

void Downloader::startNextDownload()
{
    // If nothing to download, return
    if(downloadQueue.isEmpty())
    {
        return;
    }

    // Set downloading flag to true, to avoid multiple downloads at the same time.
    downloadingMutex.lock();
    if(downloading == true)
    {
        downloadingMutex.unlock();
        return;
    }
    else
    {
        downloading = true;
    }
    downloadingMutex.unlock();

    currentUrl = downloadQueue.dequeue();
    // Inform derived class about dowlnoad start.
    downloadStart(currentUrl.uuid);
    // Prepare request.
    QNetworkRequest request(currentUrl.url);
    currentDownload = manager.get(request);
    // Launch download timer.
    downloadTimer.start();
    // Connect signals with slots.
    connect(currentDownload, &QNetworkReply::downloadProgress, this, &Downloader::downloadProgress);
    connect(currentDownload, &QNetworkReply::finished, this, &Downloader::downloadFinished);
    connect(currentDownload, &QNetworkReply::readyRead, this, &Downloader::downloadReadyRead);
}

void Downloader::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    emit downloadProgression(currentUrl.uuid, bytesReceived, bytesTotal);
}

void Downloader::downloadReadyRead()
{
    // Pass all data to virtual function, derived class will handle it
    downloadNewData(currentUrl.uuid, currentDownload->readAll());
}

void Downloader::downloadFinished()
{
    // Get download time.
    qint64 elapsedTime = downloadTimer.elapsed();

    // Check for result and pass taht info to derived class.
    if (currentDownload->error())
    {
        downloadFailed(currentUrl.uuid, elapsedTime);
    }
    else
    {
        // Check if it was actually a redirect
        if (isHttpRedirect())
        {
            downloadRedirected(currentUrl.uuid, elapsedTime);
        }
        else
        {
            downloadEnded(currentUrl.uuid, elapsedTime);
        }
    }

    // Tell currentDowlnoad to delete itself later. It isn't safe to delete it in finished slot.
    currentDownload->deleteLater();

    // Set downloading to false.
    downloadingMutex.lock();
    downloading = false;
    downloadingMutex.unlock();

    // Proceed with next download
    startNextDownload();
}

bool Downloader::isHttpRedirect() const
{
    int statusCode = currentDownload->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    return statusCode == 301 || statusCode == 302 || statusCode == 303
           || statusCode == 305 || statusCode == 307 || statusCode == 308;
}
