#include "DatabaseUpdater.h"

DatabaseUpdater::DatabaseUpdater(Logger *logger, QObject *parent) : QObject(parent)
{
    this->logger = logger;
}

bool DatabaseUpdater::checkForUpdate(QSqlDatabase &database, QFile &databaseFile)
{
    if(isUpdateNeeded(database))
    {
        logger->logMessage(tr("Rozpoczęcie procedury aktualizacji bazy danych"), Logger::LogLevel::Info);
        backupDatabaseFile(database, databaseFile);
        if(updateDatabase(database) == false)
        {
            logger->logMessage(tr("Aktualizacja bazy danych nie powiodła się"), Logger::LogLevel::Error);
            return false;
        }
    }
    logger->logMessage(tr("Baza danych zaktualizowana"), Logger::LogLevel::Ok);
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
    databaseVersion = databaseVersionStr.toUInt(&conversionOk);
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

bool DatabaseUpdater::backupDatabaseFile(QSqlDatabase &database, QFile &databaseFile)
{
    database.close();
    QFileInfo fileInfo = databaseFile;
    QString oldFilePath = fileInfo.absolutePath() + "/" + fileInfo.fileName();
    QString newFilePath = fileInfo.absolutePath() + "/" + "backup_" + QDateTime::currentDateTime().toString("yyyyMMddThhmmsszzz") + "_" + fileInfo.fileName();
    if(QFile::copy(oldFilePath, newFilePath) == false)
    {
        database.open();
        logger->logMessage(tr("Nie można utworzyć kopii zapasowej bazy danych") + QDir::toNativeSeparators(newFilePath), Logger::LogLevel::Warning);
        return false;
    }
    database.open();
    logger->logMessage(tr("Utworzono kopie zapasową bazy danych: ") + QDir::toNativeSeparators(newFilePath), Logger::LogLevel::Info);
    return true;
}

bool DatabaseUpdater::updateDatabase(QSqlDatabase &database)
{
    switch(databaseVersion)
    {
        case 1:
        {
            if(updateToVersion2(database) == false)
            {
                return false;
            }
        }
        default:
        {
            if(updateDatabaseVersionField(database) == false)
            {
                return false;
            }
            break;
        }
    }
    return true;
}

bool DatabaseUpdater::updateDatabaseVersionField(QSqlDatabase &database)
{
    QSqlQuery query(database);
    // Table SystemVersion
    if(DatabaseHelper::QSqlQueryPrepare(query, "UPDATE SystemVersion SET version = :version WHERE component = :component", logger) == false)
    {
        return false;
    }
    query.bindValue(":component", "Application version");
    query.bindValue(":version", DATABASE_VERSION);
    if(DatabaseHelper::QSqlQueryExec(query, logger) == false)
    {
        return false;
    }
    return true;
}

bool DatabaseUpdater::updateToVersion2(QSqlDatabase &database)
{
    QSqlQuery query(database);
    // Table SystemVersion
    if(DatabaseHelper::QSqlQueryPrepare(query, "UPDATE SystemVersion SET version = :version WHERE component = :component", logger) == false)
    {
        return false;
    }
    query.bindValue(":component", "Application version");
    query.bindValue(":version", "Shuka");
    if(DatabaseHelper::QSqlQueryExec(query, logger) == false)
    {
        return false;
    }
    return true;
}
