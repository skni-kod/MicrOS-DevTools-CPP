#include "DatabaseCreator.h"

DatabaseCreator::DatabaseCreator(QObject *parent) : QObject(parent)
{

}

void DatabaseCreator::createDatabase(QSqlDatabase &database)
{
    QSqlQuery query(database);
    query.exec("CREATE TABLE SystemVersion (id INTEGER NOT NULL PRIMARY KEY, component TEXT NOT NULL, version TEXT NOT NULL)");
    query.prepare("INSERT INTO SystemVersion (component, version) VALUES (:component, :version)");
    query.bindValue(":component", "Application version");
    query.bindValue(":version", APPLICATION_VERSION);
    query.exec();
    query.prepare("INSERT INTO SystemVersion (component, version) VALUES (:component, :version)");
    query.bindValue(":component", "Database version");
    query.bindValue(":version", DATABASE_VERSION);
    query.exec();
}
