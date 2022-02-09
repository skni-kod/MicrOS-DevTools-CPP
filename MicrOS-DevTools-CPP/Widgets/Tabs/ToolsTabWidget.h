#ifndef TOOLSTABWIDGET_H
#define TOOLSTABWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

class ToolsTabWidget : public QWidget
{
    Q_OBJECT

private:
    /**
     * @brief Main label.
     */
    QLabel *mainLabel = nullptr;

    /**
     * @brief Main layout of window.
     * @details Up menu, down tabs.
     */
    QVBoxLayout *mainLayout = nullptr;

public:
    explicit ToolsTabWidget(QWidget *parent = nullptr);
    ~ToolsTabWidget();

signals:

};

#endif // TOOLSTABWIDGET_H
