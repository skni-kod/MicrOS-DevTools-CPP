#ifndef COMPILERTABWIDGET_H
#define COMPILERTABWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

/*!
 * \brief The CompilerTabWidget class.
 * \details Stores controls for compiler tab.
 */
class CompilerTabWidget : public QWidget
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
    explicit CompilerTabWidget(QWidget *parent = nullptr);
    /*!
     * \brief Default destructor.
     */
    ~CompilerTabWidget();

signals:

};

#endif // COMPILERTABWIDGET_H
