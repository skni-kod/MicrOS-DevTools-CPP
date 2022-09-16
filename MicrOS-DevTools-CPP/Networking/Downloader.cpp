#include "Downloader.h"

Downloader::Downloader(QObject *parent) : QObject(parent)
{

}

void Downloader::downloadEnqueue(QUuid uuid, QUrl url)
{
    downloadQueue.enqueue(UuidUrl{uuid, url});

    downloadingMutex.lock();
    if(downloading == false)
    {
        QTimer::singleShot(0, this, &Downloader::startNextDownload);
    }
    downloadingMutex.unlock();
}

void Downloader::startNextDownload()
{
    if(downloadQueue.isEmpty())
    {
        return;
    }

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
    downloadStart(currentUrl.uuid);
    QNetworkRequest request(currentUrl.url);
    currentDownload = manager.get(request);
    connect(currentDownload, &QNetworkReply::downloadProgress, this, &Downloader::downloadProgress);
    connect(currentDownload, &QNetworkReply::finished, this, &Downloader::downloadFinished);
    connect(currentDownload, &QNetworkReply::readyRead, this, &Downloader::downloadReadyRead);

    downloadTimer.start();
}

void Downloader::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    // calculate the download speed
    double speed = bytesReceived * 1000.0 / downloadTimer.elapsed();
    QString unit;
    if (speed < 1024)
    {
        unit = "bytes/sec";
    }
    else if (speed < 1024*1024)
    {
        speed /= 1024;
        unit = "kB/s";
    }
    else
    {
        speed /= 1024*1024;
        unit = "MB/s";
    }
}

void Downloader::downloadReadyRead()
{
    // pass all data to virtual function, derived class will handle it
    downloadNewData(currentUrl.uuid, currentDownload->readAll());
}

void Downloader::downloadFinished()
{
    qint64 elapsedTime = downloadTimer.elapsed();

    if (currentDownload->error())
    {
        downloadFailed(currentUrl.uuid, elapsedTime);
    }
    else
    {
        // let's check if it was actually a redirect
        if (isHttpRedirect())
        {
            downloadRedirected(currentUrl.uuid, elapsedTime);
        }
        else
        {
            downloadEnded(currentUrl.uuid, elapsedTime);
        }
    }

    // Tell currentDowlnoad to delete itself later. It isn't safe to delete it in finished slot
    currentDownload->deleteLater();

    downloadingMutex.lock();
    downloading = false;
    downloadingMutex.unlock();

    startNextDownload();
}

bool Downloader::isHttpRedirect() const
{
    int statusCode = currentDownload->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    return statusCode == 301 || statusCode == 302 || statusCode == 303
           || statusCode == 305 || statusCode == 307 || statusCode == 308;
}
