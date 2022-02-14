#include "DatabaseHelper.h"

DatabaseHelper::DatabaseHelper(QObject *parent) : QObject(parent)
{

}

QString DatabaseHelper::SqlErrorToString(const QSqlError::ErrorType &error)
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
            return tr("Bieznany błąd");
    }
}
