#include "DatabaseCreator.h"

DatabaseCreator::DatabaseCreator(QObject *parent) : QObject(parent)
{

}

bool DatabaseCreator::createDatabase(QSqlDatabase &database)
{
    QSqlQuery query(database);
    // Table SystemVersion
    if(query.exec("CREATE TABLE SystemVersion (id INTEGER NOT NULL PRIMARY KEY, component TEXT NOT NULL UNIQUE, version TEXT NOT NULL)") == false)
    {
        QSqlError error = query.lastError();
        emit logMessage(DatabaseHelper::SqlErrorToString(error), ConsoleWidget::LogLevel::Error);
        return false;
    }
    query.prepare("INSERT INTO SystemVersion (component, version) VALUES (:component, :version)");
    query.bindValue(":component", "Application version");
    query.bindValue(":version", APPLICATION_VERSION);
    if(query.exec() == false)
    {
        QSqlError error = query.lastError();
        emit logMessage(DatabaseHelper::SqlErrorToString(error), ConsoleWidget::LogLevel::Error);
        return false;
    }
    if(query.prepare("INSERT INTO SystemVersion (component, version) VALUES (:component, :version)") == false)
    {
        QSqlError error = query.lastError();
        emit logMessage(DatabaseHelper::SqlErrorToString(error), ConsoleWidget::LogLevel::Error);
        return false;
    }
    query.bindValue(":component", "Database version");
    query.bindValue(":version", QString::number(DATABASE_VERSION));
    if(query.exec() == false)
    {
        QSqlError error = query.lastError();
        emit logMessage(DatabaseHelper::SqlErrorToString(error), ConsoleWidget::LogLevel::Error);
        return false;
    }

    // Table SystemSettings
    query.exec("CREATE TABLE SystemSettings (id INTEGER NOT NULL PRIMARY KEY, setting TEXT NOT NULL UNIQUE, value TEXT, type TEXT NOT NULL)");
    query.prepare("INSERT INTO SystemSettings (setting, type) VALUES (:setting, :type)");
    query.bindValue(":setting", "Repository location");
    query.bindValue(":type", "S");
    query.exec();
    query.prepare("INSERT INTO SystemSettings (setting, type) VALUES (:setting, :type)");
    query.bindValue(":setting", "MSYS location");
    query.bindValue(":type", "S");
    query.exec();
    query.prepare("INSERT INTO SystemSettings (setting, type) VALUES (:setting, :type)");
    query.bindValue(":setting", "QEMU location");
    query.bindValue(":type", "S");
    query.exec();
    query.prepare("INSERT INTO SystemSettings (setting, type) VALUES (:setting, :type)");
    query.bindValue(":setting", "Floppy letter");
    query.bindValue(":type", "S");
    query.exec();
    query.prepare("INSERT INTO SystemSettings (setting, type) VALUES (:setting, :type)");
    query.bindValue(":setting", "Compilation threads");
    query.bindValue(":type", "I");
    query.exec();
    query.prepare("INSERT INTO SystemSettings (setting, type) VALUES (:setting, :type)");
    query.bindValue(":setting", "Debugger target");
    query.bindValue(":type", "S");
    query.exec();
    query.prepare("INSERT INTO SystemSettings (setting, type) VALUES (:setting, :type)");
    query.bindValue(":setting", "Windows version");
    query.bindValue(":type", "S");
    query.exec();

    return true;
}
