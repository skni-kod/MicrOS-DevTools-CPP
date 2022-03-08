#ifndef ENVIRONMENTTABWIDGET_H
#define ENVIRONMENTTABWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

/*!
 * \brief The EnvironmentTabWidget class.
 * \details Stores controls for environment tab.
 */
class EnvironmentTabWidget : public QWidget
{
    Q_OBJECT

private:
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
    explicit EnvironmentTabWidget(QWidget *parent = nullptr);
    /*!
     * \brief Default destructor.
     */
    ~EnvironmentTabWidget();

signals:

};

#endif // ENVIRONMENTTABWIDGET_H
