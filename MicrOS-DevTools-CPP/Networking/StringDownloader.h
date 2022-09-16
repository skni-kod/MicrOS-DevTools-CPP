#ifndef STRINGDOWNLOADER_H
#define STRINGDOWNLOADER_H

#include <QMap>
#include <QString>
#include <QUuid>

#include "Downloader.h"

/*!
 * \brief Allows to downlaod file and store it as string.
 * \details To download file provide it's url and identifier choosen by you and call \a download().
 * When download finishes \a downloadComplete signal will be sent.
 * Signal will give you identifier to allow you distinguish what has been downloaded.
 */
class StringDownloader : public Downloader
{
    Q_OBJECT

private:
    /*!
     * \brief Struct that keep additional data realted to download.
     */
    struct DownloadData
    {
        /*!
         * \brief Identifier for download.
         */
        QString identifier;
    };

private:
    /*!
     * \brief Holds downloaded data of current download.
     */
    QString content;
    /*!
     * \brief Map with uuid of downloads and other useful data.
     * \details Allow to keep additional data for downloads like ideitifier.
     * Different downloads are distinguished by uuid.
     */
    QMap<QUuid, DownloadData> downloadMapData;
public:
    /*!
     * \brief Default constructor.
     * \param parent Pointer to parent object.
     */
    StringDownloader(QObject *parent = nullptr);


signals:
    /*!
     * \brief Called when download finishes.
     * \param result Result of download, allow to check status.
     * \param url Url which was provided to download file.
     * \param identifier Identifier provided by user when dalled \a download().
     * \param content Data that was downloaded.
     * \param elapsedTime Time duration of download.
     */
    void downloadComplete(Downloader::DownloadResult result, QUrl url, QString identifier, QString content, quint64 elapsedTime);

public:
    /*!
     * \brief Adds url to download queue with identifier.
     * \param url Url poiting to file to download.
     * \param identifier String which will allow to distinguish different downloads.
     */
    void download(QUrl url, QString identifier);

protected:
    /*!
     * \brief Called when download starts.
     * \details Allows derived class do operations when download starts.
     * \param uuid Uuid of dowlnload.
     */
    virtual void downloadStart(QUuid uuid);
    /*!
     * \brief Called when new data arrives.
     * \details Allows derived class do operations when new data is downloaded.
     * \param uuid Uuid of dowlnload.
     * \param byteArray Downlaoded data.
     */
    virtual void downloadNewData(QUuid uuid, const QByteArray& byteArray);
    /*!
     * \brief Called when download ends with success.
     * \details Allows derived class do operations when download ends.
     * \param uuid Uuid of dowlnload.
     * \param elapsedTime Time duration of download.
     */
    virtual void downloadEnded(QUuid uuid, qint64 elapsedTime);
    /*!
     * \brief Called when download ends with fail.
     * \details Allows derived class do operations when download fails.
     * \param uuid Uuid of dowlnload.
     * \param elapsedTime Time duration of download.
     */
    virtual void downloadFailed(QUuid uuid, qint64 elapsedTime);
    /*!
     * \brief Called when download has been redirected.
     * \details Allows derived class do operations when download redirects.
     * \param uuid Uuid of dowlnload.
     * \param elapsedTime Time duration of download.
     */
    virtual void downloadRedirected(QUuid uuid, qint64 elapsedTime);

};

#endif // STRINGDOWNLOADER_H
