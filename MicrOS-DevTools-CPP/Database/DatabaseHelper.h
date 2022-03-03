#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <QObject>
#include <QString>
#include <QSqlError>
#include <QSqlQuery>

#include "Utils/Logger.h"

/*!
 * \brief The DatabaseHelper class
 * \details Stores static functions that are helpful with database handling.
 */
class DatabaseHelper : public QObject
{
    Q_OBJECT

public:
    /*!
     * \brief DatabaseHelper
     * \param parent Pointer to parent object.
     */
    explicit DatabaseHelper(QObject *parent = nullptr);
    /*!
     * \brief Logs QSqlError to logger
     * \param error Error that occured.
     * \param logger Logger instance.
     */
    static void QSqlErrorToString(const QSqlError &error, Logger *logger);
    /*!
     * \brief Converts \a QSqlError::ErrorType to string
     * \param error Error value
     * \return Error as string
     */
    static QString QSqlErrorTypeToString(const QSqlError::ErrorType &error);
    /*!
     * \brief Wrapper that executes query and check result.
     * \param query Query instance to execute.
     * \param logger Logger instance.
     * \return True if success, false otherwise.
     */
    static bool QSqlQueryExec(QSqlQuery &query, Logger *logger);
    /*!
     * \brief Wrapper that executes given SQL query and check result.
     * \param query Query instance to execute.
     * \param sqlQuery SQL query, which will be executed.
     * \param logger Logger instance.
     * \return True if success, false otherwise.
     */
    static bool QSqlQueryExec(QSqlQuery &query, QString sqlQuery, Logger *logger);
    /*!
     * \brief Wrapper that prepares query and check result.
     * \param query Query instance to execute.
     * \param sqlQuery SQL query, which will be prepared.
     * \param logger Logger instance.
     * \return True if success, false otherwise.
     */
    static bool QSqlQueryPrepare(QSqlQuery &query, QString sqlQuery, Logger *logger);
};

#endif // DATABASEHELPER_H
