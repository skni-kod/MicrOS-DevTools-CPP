#ifndef DATABASEUPDATER_H
#define DATABASEUPDATER_H

#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QObject>
#include <QSqlDatabase>
#include <QVariant>

#include "DatabaseHelper.h"
#include "Version.h"
#include "Utils/Logger.h"

class DatabaseUpdater : public QObject
{
    Q_OBJECT

    Logger *logger = nullptr;

public:
    explicit DatabaseUpdater(Logger *logger, QObject *parent = nullptr);

signals:

public:
    bool checkForUpdate(QSqlDatabase &database, QFile &databaseFile);

private:
    bool isUpdateNeeded(QSqlDatabase &database);
    bool backupDatabaseFile(QSqlDatabase &database, QFile &databaseFile);
};

#endif // DATABASEUPDATER_H
