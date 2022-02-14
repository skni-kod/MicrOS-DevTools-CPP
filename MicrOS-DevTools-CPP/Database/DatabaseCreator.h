#ifndef DATABASECREATOR_H
#define DATABASECREATOR_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

#include "Version.h"

class DatabaseCreator : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseCreator(QObject *parent = nullptr);

signals:

public:
    bool createDatabase(QSqlDatabase &database);
};

#endif // DATABASECREATOR_H
