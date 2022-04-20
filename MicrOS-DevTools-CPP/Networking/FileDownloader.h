#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>

class FileDownloader : public QObject
{
    Q_OBJECT
public:
    explicit FileDownloader(QObject *parent = nullptr);

signals:

};

#endif // FILEDOWNLOADER_H
