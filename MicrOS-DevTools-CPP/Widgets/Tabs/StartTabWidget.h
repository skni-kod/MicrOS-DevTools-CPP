#ifndef STARTTABWIDGET_H
#define STARTTABWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

/*!
 * \brief The StartTabWidget class.
 * \details Stores controls for start tab.
 */
class StartTabWidget : public QWidget
{
    Q_OBJECT

private:
    /*!
     *  \brief Logo label with program logo.
     */
    QLabel *logoLabel = nullptr;
    /*!
     *  \brief Main label with tab description.
     */
    QLabel *mainLabel = nullptr;
    /*!
     *  \brief Label about next tab.
     */
    QLabel *nextTabLabel = nullptr;

    /*!
     *  \brief Main layout of tab.
     */
    QVBoxLayout *mainLayout = nullptr;

public:
    /*!
     * \brief Default constructor.
     * \param parent Pointer to parent widget.
     */
    explicit StartTabWidget(QWidget *parent = nullptr);
    /*!
     * \brief Default destructor.
     */
    ~StartTabWidget();

signals:

};

#endif // STARTTABWIDGET_H
