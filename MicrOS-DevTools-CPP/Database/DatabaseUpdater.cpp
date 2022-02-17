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
        if(backupDatabaseFile(database, databaseFile))
        {

        }

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
