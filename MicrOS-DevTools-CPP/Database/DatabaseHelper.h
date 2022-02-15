#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <QObject>
#include <QString>
#include <QSqlError>

class DatabaseHelper : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseHelper(QObject *parent = nullptr);
    static QString SqlErrorToString(const QSqlError &error);
    static QString SqlErrorToString(const QSqlError::ErrorType &error);
};

#endif // DATABASEHELPER_H
