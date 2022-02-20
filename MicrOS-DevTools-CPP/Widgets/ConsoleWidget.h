#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QApplication>
#include <QColor>
#include <QDateTime>
#include <QString>
#include <QTextEdit>
#include <QWidget>
#include <QVBoxLayout>

#include "Utils/Logger.h"

/*!
 * \brief The ConsoleWidget class.
 * \details Defines widget that can act as console.
 * Prints messages with 4 different colored levels.
 */
class ConsoleWidget : public QWidget
{
    Q_OBJECT

private:
    /*!
     *  \brief Main layout of widget.
     */
    QVBoxLayout *mainLayout = nullptr;
    /*!
     *  \brief Main text edit which plays console role.
     */
    QTextEdit *consoleTextEdit = nullptr;

public:
    /*!
     * \brief Default constructor.
     * \param parent Pointer to parent widget.
     */
    explicit ConsoleWidget(QWidget *parent = nullptr);
    /*!
     * \brief Default destructor.
     */
    ~ConsoleWidget();
    /*!
     * \brief Provides recommended size for the widget.
     * \return Recommended size for the widget.
     */
    QSize sizeHint() const override;

signals:

public slots:
    /*!
     * \brief Print line of text to log.
     * \param message Message to print to log console.
     * \param level Level of logged message.
     */
    void printMessage(QString message, Logger::LogLevel level);
    /*!
     * \brief Clears log console.
     */
    void clear();

public:
    /*!
     * \brief Getter for content of log console
     * \return Whole log stored by console.
     */
    QString getLog() {return consoleTextEdit->toPlainText();}

private:
    /*!
     * \brief Prints message to log console.
     * \param text Message to log.
     * \param color Color of message.
     */
    void printLog(QString text, QColor color);
};

#endif // CONSOLEWIDGET_H
