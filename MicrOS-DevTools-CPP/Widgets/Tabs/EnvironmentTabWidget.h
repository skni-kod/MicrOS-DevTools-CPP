#ifndef ENVIRONMENTTABWIDGET_H
#define ENVIRONMENTTABWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

class EnvironmentTabWidget : public QWidget
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
    explicit EnvironmentTabWidget(QWidget *parent = nullptr);
    ~EnvironmentTabWidget();

signals:

};

#endif // ENVIRONMENTTABWIDGET_H
