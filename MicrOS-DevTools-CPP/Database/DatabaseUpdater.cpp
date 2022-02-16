#include "DatabaseUpdater.h"

DatabaseUpdater::DatabaseUpdater(Logger *logger, QObject *parent) : QObject(parent)
{
    this->logger = logger;
}

bool DatabaseUpdater::checkForUpdate(QSqlDatabase &database)
{
    if(isUpdateNeeded(database))
    {
        logger->logMessage(tr("Aktualizowanie bazy danych"), Logger::LogLevel::Info);
    }
    return true;
}

bool DatabaseUpdater::isUpdateNeeded(QSqlDatabase &database)
{
    QSqlQuery query(database);
    // Table SystemVersion
    if(DatabaseHelper::QSqlQueryExec(query, "SELECT version FROM SystemVersion WHERE component = 'Database version'", logger) == false)
    {
        return false;
    }
    query.next();
    QString databaseVersionStr = query.value(0).toString();
    bool conversionOk;
    int databaseVersion = databaseVersionStr.toUInt(&conversionOk);
    if(conversionOk == false)
    {
        logger->logMessage(tr("Wersja bazy danych nie jest liczbą: ") + databaseVersionStr, Logger::LogLevel::Error);
        return false;
    }
    if(DATABASE_VERSION > databaseVersion)
    {
        logger->logMessage(tr("Aktualna wersja bazy danych: ") + databaseVersionStr +
                           tr(", nowa wersja bazy danych: ") + QString::number(DATABASE_VERSION) +
                           tr(" Wymagana aktualizacja"),
                           Logger::LogLevel::Info);
        return true;
    }
    return false;
}
