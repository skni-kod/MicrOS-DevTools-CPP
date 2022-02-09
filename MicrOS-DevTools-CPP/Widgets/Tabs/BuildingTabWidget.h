#ifndef BUILDINGTABWIDGET_H
#define BUILDINGTABWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

class BuildingTabWidget : public QWidget
{
    Q_OBJECT

private:
    /**
     * @brief Main label.
     */
    QLabel *mainLabel = nullptr;
    /**
     * @brief Holds information about going to next tab.
     */
    QLabel *nextTabLabel = nullptr;

    /**
     * @brief Main layout of window.
     * @details Up menu, down tabs.
     */
    QVBoxLayout *mainLayout = nullptr;

public:
    explicit BuildingTabWidget(QWidget *parent = nullptr);
    ~BuildingTabWidget();

signals:

};

#endif // BUILDINGTABWIDGET_H
