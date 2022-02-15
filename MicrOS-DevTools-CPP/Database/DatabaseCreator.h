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

class DatabaseCreator : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseCreator(QObject *parent = nullptr);

signals:
    void logMessage(QString message, ConsoleWidget::LogLevel logLevel);

public:
    bool createDatabase(QSqlDatabase &database);
};

#endif // DATABASECREATOR_H
