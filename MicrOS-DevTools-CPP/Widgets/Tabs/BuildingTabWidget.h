#ifndef BUILDINGTABWIDGET_H
#define BUILDINGTABWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

/*!
 * \brief The BuildingTabWidget class.
 * \details Stores controls for building tab.
 */
class BuildingTabWidget : public QWidget
{
    Q_OBJECT

private:
    /*!
     * \brief Main label with tab description.
     */
    QLabel *mainLabel = nullptr;
    /*!
     * \brief Label about next tab.
     */
    QLabel *nextTabLabel = nullptr;

    /*!
     * \brief Main layout of tab.
     */
    QVBoxLayout *mainLayout = nullptr;

public:
    /*!
     * \brief Default constructor.
     * \param parent Pointer to parent widget.
     */
    explicit BuildingTabWidget(QWidget *parent = nullptr);
    /*!
     * \brief Default destructor.
     */
    ~BuildingTabWidget();

signals:

};

#endif // BUILDINGTABWIDGET_H
