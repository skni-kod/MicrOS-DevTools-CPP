#ifndef DATABASECREATOR_H
#define DATABASECREATOR_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

#include "ConsoleWidget.h"
#include "DatabaseHelper.h"
#include "Version.h"
#include "Utils/Logger.h"

class DatabaseCreator : public QObject
{
    Q_OBJECT

    Logger *logger = nullptr;

public:
    explicit DatabaseCreator(Logger *logger, QObject *parent = nullptr);

public:
    bool createDatabase(QSqlDatabase &database);
};

#endif // DATABASECREATOR_H
