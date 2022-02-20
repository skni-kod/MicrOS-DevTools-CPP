#include "DatabaseCreator.h"

DatabaseCreator::DatabaseCreator(Logger *logger, QObject *parent) : QObject(parent)
{
    this->logger = logger;
}

bool DatabaseCreator::createDatabase(QSqlDatabase &database)
{
    QSqlQuery query(database);
    // Table SystemVersion
    if(DatabaseHelper::QSqlQueryExec(query, "CREATE TABLE SystemVersion (id INTEGER NOT NULL PRIMARY KEY, component TEXT NOT NULL UNIQUE, version TEXT NOT NULL)", logger) == false)
    {
        return false;
    }
    if(DatabaseHelper::QSqlQueryPrepare(query, "INSERT INTO SystemVersion (component, version) VALUES (:component, :version)", logger) == false)
    {
        return false;
    }
    query.bindValue(":component", "Application version");
    query.bindValue(":version", APPLICATION_VERSION);
    if(DatabaseHelper::QSqlQueryExec(query, logger) == false)
    {
        return false;
    }

    if(DatabaseHelper::QSqlQueryPrepare(query, "INSERT INTO SystemVersion (component, version) VALUES (:component, :version)", logger) == false)
    {
        return false;
    }
    query.bindValue(":component", "Database version");
    query.bindValue(":version", QString::number(DATABASE_VERSION));
    if(DatabaseHelper::QSqlQueryExec(query, logger) == false)
    {
        return false;
    }

    // Table SystemSettings
    if(DatabaseHelper::QSqlQueryExec(query, "CREATE TABLE SystemSettings (id INTEGER NOT NULL PRIMARY KEY, setting TEXT NOT NULL UNIQUE, value TEXT, type TEXT NOT NULL)", logger) == false)
    {
        return false;
    }

    if(DatabaseHelper::QSqlQueryPrepare(query, "INSERT INTO SystemSettings (setting, type) VALUES (:setting, :type)", logger) == false)
    {
        return false;
    }
    query.bindValue(":setting", "Repository location");
    query.bindValue(":type", "S");
    if(DatabaseHelper::QSqlQueryExec(query, logger) == false)
    {
        return false;
    }

    if(DatabaseHelper::QSqlQueryPrepare(query, "INSERT INTO SystemSettings (setting, type) VALUES (:setting, :type)", logger) == false)
    {
        return false;
    }
    query.bindValue(":setting", "MSYS location");
    query.bindValue(":type", "S");
    if(DatabaseHelper::QSqlQueryExec(query, logger) == false)
    {
        return false;
    }

    if(DatabaseHelper::QSqlQueryPrepare(query, "INSERT INTO SystemSettings (setting, type) VALUES (:setting, :type)", logger) == false)
    {
        return false;
    }
    query.bindValue(":setting", "QEMU location");
    query.bindValue(":type", "S");
    if(DatabaseHelper::QSqlQueryExec(query, logger) == false)
    {
        return false;
    }

    if(DatabaseHelper::QSqlQueryPrepare(query, "INSERT INTO SystemSettings (setting, type) VALUES (:setting, :type)", logger) == false)
    {
        return false;
    }
    query.bindValue(":setting", "Floppy letter");
    query.bindValue(":type", "S");
    if(DatabaseHelper::QSqlQueryExec(query, logger) == false)
    {
        return false;
    }

    if(DatabaseHelper::QSqlQueryPrepare(query, "INSERT INTO SystemSettings (setting, type) VALUES (:setting, :type)", logger) == false)
    {
        return false;
    }
    query.bindValue(":setting", "Compilation threads");
    query.bindValue(":type", "I");
    if(DatabaseHelper::QSqlQueryExec(query, logger) == false)
    {
        return false;
    }

    if(DatabaseHelper::QSqlQueryPrepare(query, "INSERT INTO SystemSettings (setting, type) VALUES (:setting, :type)", logger) == false)
    {
        return false;
    }
    query.bindValue(":setting", "Debugger target");
    query.bindValue(":type", "S");
    if(DatabaseHelper::QSqlQueryExec(query, logger) == false)
    {
        return false;
    }

    if(DatabaseHelper::QSqlQueryPrepare(query, "INSERT INTO SystemSettings (setting, type) VALUES (:setting, :type)", logger) == false)
    {
        return false;
    }
    query.bindValue(":setting", "Windows version");
    query.bindValue(":type", "S");
    if(DatabaseHelper::QSqlQueryExec(query, logger) == false)
    {
        return false;
    }

    return true;
}
