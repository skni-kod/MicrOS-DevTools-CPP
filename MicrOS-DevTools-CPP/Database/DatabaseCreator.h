#ifndef DATABASECREATOR_H
#define DATABASECREATOR_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

#include "Database/DatabaseFields.h"
#include "Database/DatabaseHelper.h"
#include "Utils/Logger.h"
#include "Widgets/ConsoleWidget.h"
#include "Version.h"

/*!
 * \brief Class that creates database.
 */
class DatabaseCreator : public QObject
{
    Q_OBJECT

    /*!
     * \brief Logger instance.
     */
    Logger *logger = nullptr;

public:
    /*!
     * \brief Default constructor.
     * \param logger Pointer to logger.
     * \param parent Pointer to parent object.
     */
    explicit DatabaseCreator(Logger *logger, QObject *parent = nullptr);

public:
    /*!
     * \brief Created database.
     * \param database Reference to database object.
     * \return True if success, false otherwise.
     */
    bool createDatabase(QSqlDatabase &database);
};

#endif // DATABASECREATOR_H
