#include "DatabaseCreator.h"

DatabaseCreator::DatabaseCreator(QObject *parent) : QObject(parent)
{

}

void DatabaseCreator::createDatabase(QSqlDatabase &database)
{
    QSqlQuery query(database);
    // Table SystemVersion
    query.exec("CREATE TABLE SystemVersion (id INTEGER NOT NULL PRIMARY KEY, component TEXT NOT NULL UNIQUE, version TEXT NOT NULL)");
    query.prepare("INSERT INTO SystemVersion (component, version) VALUES (:component, :version)");
    query.bindValue(":component", "Application version");
    query.bindValue(":version", APPLICATION_VERSION);
    query.exec();
    query.prepare("INSERT INTO SystemVersion (component, version) VALUES (:component, :version)");
    query.bindValue(":component", "Database version");
    query.bindValue(":version", QString::number(DATABASE_VERSION));
    query.exec();

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
}
