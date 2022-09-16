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

/*!
 * \brief The Downloader class
 * \details Provides queue for sequential file download.
 * Class has pure virtual function for derived classes to handle
 * data saving eg. on disk or in memory.
 */
class Downloader : public QObject
{
    Q_OBJECT

public:
    /*!
     * \brief Defines result of download.
     */
    enum class DownloadResult
    {
        Success,     /*!< Download succeded. */
        Failed,      /*!< Download failed. */
        Redirected   /*!< Redirect occured during download. */
    };
    // Register DownloadResult in Qt meta-object system
    Q_ENUM(DownloadResult)

protected:
    /*!
     * \brief The UuidUrl struct.
     * \details Holds uuid of download alongside with url.
     */
    struct UuidUrl
    {
        /*!
         * \brief Uuid of dowlnload.
         */
        QUuid uuid;
        /*!
         * \brief Url of file.
         */
        QUrl url;
    };

protected:
    /*!
     * \brief Manager for network access. Allows to send network requests.
     */
    QNetworkAccessManager manager;
    /*!
     * \brief Queue with files to download.
     */
    QQueue<UuidUrl> downloadQueue;
    /*!
     * \brief Contains data and headers for current download.
     */
    QNetworkReply *currentDownload = nullptr;
    /*!
     * \brief Timer to track download time.
     */
    QElapsedTimer downloadTimer;

private:
    /*!
     * \brief Mutex to protect \a downloading variable.
     */
    QMutex downloadingMutex;
    /*!
     * \brief Defines if any download is currently going.
     */
    bool downloading = false;
    /*!
     * \brief Holds uuid and url for currently downloading file.
     */
    UuidUrl currentUrl;

public:
    /*!
     * \brief Default constructor.
     * \param parent Pointer to parent object.
     */
    explicit Downloader(QObject *parent = nullptr);

protected slots:
    /*!
     * \brief Adds url to download queue.
     * \param uuid Unique id for download request.
     * \param url Url pointing to file.
     */
    void downloadEnqueue(QUuid uuid, QUrl url);

protected:
    /*!
     * \brief Called when download starts.
     * \details Allows derived class do operations when download starts.
     * \param uuid Uuid of dowlnload.
     */
    virtual void downloadStart(QUuid uuid) = 0;
    /*!
     * \brief Called when new data arrives.
     * \details Allows derived class do operations when new data is downloaded.
     * \param uuid Uuid of dowlnload.
     * \param byteArray Downlaoded data.
     */
    virtual void downloadNewData(QUuid uuid, const QByteArray& byteArray) = 0;
    /*!
     * \brief Called when download ends with success.
     * \details Allows derived class do operations when download ends.
     * \param uuid Uuid of dowlnload.
     * \param elapsedTime Time duration of download.
     */
    virtual void downloadEnded(QUuid uuid, qint64 elapsedTime) = 0;
    /*!
     * \brief Called when download ends with fail.
     * \details Allows derived class do operations when download fails.
     * \param uuid Uuid of dowlnload.
     * \param elapsedTime Time duration of download.
     */
    virtual void downloadFailed(QUuid uuid, qint64 elapsedTime) = 0;
    /*!
     * \brief Called when download has been redirected.
     * \details Allows derived class do operations when download redirects.
     * \param uuid Uuid of dowlnload.
     * \param elapsedTime Time duration of download.
     */
    virtual void downloadRedirected(QUuid uuid, qint64 elapsedTime) = 0;
    /*!
     * \brief Returns current url and uuid.
     * \return Struct with uuid and url of current download.
     */
    UuidUrl getCurrentUrl() noexcept {return currentUrl;}

private slots:
    /*!
     * \brief Used to start a new download. Called in \a downloadStart() or \a downloadFinished().
     */
    void startNextDownload();
    /*!
     * \brief Calculates current download speed.
     * \details Slot for receive \a downloadProgress signal from \a QNetworkRequest.
     * \param bytesReceived Bytes already received.
     * \param bytesTotal Total bytes to receive.
     */
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    /*!
     * \brief Called whan download finishes.
     * \details Slot for receive \a finished signal from \a QNetworkRequest.
     */
    void downloadFinished();
    /*!
     * \brief Called when new data arrives.
     * \details Slot for receive \a readyRead signal from \a QNetworkRequest.
     */
    void downloadReadyRead();

private:
    /*!
     * \brief Check if redirect occured based on status code.
     * \return True when redirect occured false otherwise.
     */
    bool isHttpRedirect() const;

};

#endif // DOWNLOADER_H
