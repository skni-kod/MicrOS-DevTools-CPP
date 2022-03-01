#include "DatabaseHelper.h"

DatabaseHelper::DatabaseHelper(QObject *parent) : QObject(parent)
{

}

void DatabaseHelper::QSqlErrorToString(const QSqlError &error, Logger *logger)
{
    logger->logMessage(tr("Błąd bazy danych: ") + DatabaseHelper::QSqlErrorTypeToString(error.type()), Logger::LogLevel::Error);
    logger->logMessage(tr("Błąd sterownika: ") +  error.driverText(), Logger::LogLevel::Error);
    logger->logMessage(tr("Błąd bazy danych: ") + error.databaseText(), Logger::LogLevel::Error);
    logger->logMessage(tr("Kod błędu: ") + error.nativeErrorCode(), Logger::LogLevel::Error);
}

QString DatabaseHelper::QSqlErrorTypeToString(const QSqlError::ErrorType &error)
{
    switch(error)
    {
        case QSqlError::ErrorType::NoError:
            return tr("Brak błędu");
        case QSqlError::ErrorType::ConnectionError:
            return tr("Błąd połączenia");
        case QSqlError::ErrorType::StatementError:
            return tr("Błąd zapytania");
        case QSqlError::ErrorType::TransactionError:
            return tr("Błąd transakcji");
        case QSqlError::ErrorType::UnknownError:
        default:
            return tr("Nieznany błąd");
    }
}

bool DatabaseHelper::QSqlQueryExec(QSqlQuery &query, Logger *logger)
{
    if(query.exec() == false)
    {
        DatabaseHelper::QSqlErrorToString(query.lastError(), logger);
        logger->logMessage(tr("Zapytanie: ") + query.lastQuery(), Logger::LogLevel::Error);
        return false;
    }
    return true;
}

bool DatabaseHelper::QSqlQueryExec(QSqlQuery &query, QString sqlQuery, Logger *logger)
{
    if(query.exec(sqlQuery) == false)
    {
        logger->logMessage(tr("Błąd podczas wykonywnia zapytania"), Logger::LogLevel::Error);
        DatabaseHelper::QSqlErrorToString(query.lastError(), logger);
        logger->logMessage(tr("Zapytanie: ") + query.lastQuery(), Logger::LogLevel::Error);
        return false;
    }
    return true;
}

bool DatabaseHelper::QSqlQueryPrepare(QSqlQuery &query, QString sqlQuery, Logger *logger)
{
    if(query.prepare(sqlQuery) == false)
    {
        logger->logMessage(tr("Błąd podczas przygotowywania zapytania"), Logger::LogLevel::Error);
        DatabaseHelper::QSqlErrorToString(query.lastError(), logger);
        logger->logMessage(tr("Zapytanie: ") + query.lastQuery(), Logger::LogLevel::Error);
        return false;
    }
    return true;
}
