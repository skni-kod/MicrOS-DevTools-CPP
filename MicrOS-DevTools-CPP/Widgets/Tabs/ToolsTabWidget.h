#ifndef TOOLSTABWIDGET_H
#define TOOLSTABWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

/*!
 * \brief The ToolsTabWidget class.
 * \details Stores controls for tools tab.
 */
class ToolsTabWidget : public QWidget
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
    explicit ToolsTabWidget(QWidget *parent = nullptr);
    /*!
     * \brief Default destructor.
     */
    ~ToolsTabWidget();

signals:

};

#endif // TOOLSTABWIDGET_H
