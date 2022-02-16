#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <QObject>
#include <QString>
#include <QSqlError>
#include <QSqlQuery>

#include "Utils/Logger.h"

class DatabaseHelper : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseHelper(QObject *parent = nullptr);
    static void QSqlErrorToString(const QSqlError &error, Logger *logger);
    static QString QSqlErrorTypeToString(const QSqlError::ErrorType &error);
    static bool QSqlQueryExec(QSqlQuery &query, Logger *logger);
    static bool QSqlQueryExec(QSqlQuery &query, QString sqlQuery, Logger *logger);
    static bool QSqlQueryPrepare(QSqlQuery &query, QString sqlQuery, Logger *logger);
};

#endif // DATABASEHELPER_H
