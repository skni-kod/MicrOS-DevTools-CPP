#ifndef LINKSTABWIDGET_H
#define LINKSTABWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

/*!
 * \brief The LinksTabWidget class.
 * \details Stores controls for links tab.
 */
class LinksTabWidget : public QWidget
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
    explicit LinksTabWidget(QWidget *parent = nullptr);
    /*!
     * \brief Default destructor.
     */
    ~LinksTabWidget();

signals:

};

#endif // LINKSTABWIDGET_H
