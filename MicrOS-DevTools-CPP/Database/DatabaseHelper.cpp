#include "DatabaseHelper.h"

DatabaseHelper::DatabaseHelper(QObject *parent) : QObject(parent)
{

}

QString DatabaseHelper::SqlErrorToString(const QSqlError &error)
{
    QString message;
    message.append(tr("Błąd przy otwieraniu bazy danych: "));
    message.append(DatabaseHelper::SqlErrorToString(error.type()));
    message.append(", ");
    message.append(tr("Błąd sterownika: ") + error.driverText());
    message.append(", ");
    message.append(tr("Błąd bazy danych: ") + error.databaseText());
    message.append(", ");
    message.append(tr("Kod błędu: ") + error.nativeErrorCode());
    return message;
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
