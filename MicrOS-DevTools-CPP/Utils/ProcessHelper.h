#ifndef PROCESSHELPER_H
#define PROCESSHELPER_H

#include <QObject>
#include <QProcess>
#include <QString>

/*!
 * \brief The ProcessHelper class
 * \details Stores static functions that are helpful with process handling.
 */
class ProcessHelper : public QObject
{
    Q_OBJECT

public:
    /*!
     * \brief ProcessHelper
     * \param parent Pointer to parent object.
     */
    explicit ProcessHelper(QObject *parent = nullptr);

    /*!
     * \brief Converts \a QProcess::ExitStatus to string.
     * \param status Status value.
     * \return Status as string.
     */
    static QString QProcessExitSatusToString(const QProcess::ExitStatus &status);
    /*!
     * \brief Converts \a QProcess::ProcessError to string.
     * \param error Error value.
     * \return Error as string.
     */
    static QString QProcessErrorToString(const QProcess::ProcessError &error);
};

#endif // PROCESSHELPER_H
