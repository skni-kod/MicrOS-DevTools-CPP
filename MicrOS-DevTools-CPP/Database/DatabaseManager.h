#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

#include "ConsoleWidget.h"

class DatabaseManager : public QObject
{
    Q_OBJECT

private:
    QSqlDatabase database;
    QString checkFileName = ".database.txt";

public:
    DatabaseManager(QObject *parent = nullptr);
    void init(QString path);

signals:
    void logMessage(QString message, ConsoleWidget::LogLevel logLevel);

private:
    void rebuildDatabase(QString path);
    void createCheckfile(QString path);
};

#endif // DATABASEMANAGER_H
