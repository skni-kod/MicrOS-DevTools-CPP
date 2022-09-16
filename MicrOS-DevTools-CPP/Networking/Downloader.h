#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QElapsedTimer>
#include <QMutex>
#include <QObject>
#include <QPair>
#include <QtNetwork>
#include <QUrl>
#include <QUuid>
#include <QQueue>

class Downloader : public QObject
{
    Q_OBJECT

public:
    enum class DownloadResult
    {
        Success,
        Failed,
        Redirected
    };
    Q_ENUM(DownloadResult)

protected:
    struct UuidUrl
    {
        QUuid uuid;
        QUrl url;
    };

protected:
    QNetworkAccessManager manager;
    QQueue<UuidUrl> downloadQueue;
    QNetworkReply *currentDownload = nullptr;
    QElapsedTimer downloadTimer;

private:
    QMutex downloadingMutex;
    bool downloading = false;
    UuidUrl currentUrl;

public:
    explicit Downloader(QObject *parent = nullptr);

protected slots:
    void downloadEnqueue(QUuid uuid, QUrl url);
    void startNextDownload();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadFinished();
    void downloadReadyRead();

protected:
    virtual void downloadStart(QUuid uuid) = 0;
    virtual void downloadNewData(QUuid uuid, const QByteArray& byteArray) = 0;
    virtual void downloadEnded(QUuid uuid, qint64 elapsedTime) = 0;
    virtual void downloadFailed(QUuid uuid, qint64 elapsedTime) = 0;
    virtual void downloadRedirected(QUuid uuid, qint64 elapsedTime) = 0;
    UuidUrl getCurrentUrl() noexcept {return currentUrl;}

private:
    bool isHttpRedirect() const;

signals:

};

#endif // DOWNLOADER_H
