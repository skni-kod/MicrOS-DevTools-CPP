#ifndef DATABASEUPDATER_H
#define DATABASEUPDATER_H

#include <QDebug>
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
    bool checkForUpdate(QSqlDatabase &database);

private:
    bool isUpdateNeeded(QSqlDatabase &database);
};

#endif // DATABASEUPDATER_H
