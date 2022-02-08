#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QTabWidget>
#include <QWidget>
#include <QVBoxLayout>

#include "Tabs/LinksTabWidget.h"
#include "Tabs/StartTabWidget.h"
#include "Tabs/ToolsTabWidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT

private:
    /**
     * @brief Pointer to main menu.
     */
    QMenuBar *menuBar = nullptr;
    /**
     * @brief Pointer to program menu.
     */
    QMenu *programMenu = nullptr;
    /**
     * @brief Action for exit.
     */
    QAction *exitAction = nullptr;

    QMenu *tabsMenu = nullptr;
    QAction *startTabAction = nullptr;
    QAction *liknsTabAction = nullptr;
    QAction *toolsTabAction = nullptr;
    QAction *environmentTabAction = nullptr;
    QAction *buildingTabAction = nullptr;
    /**
     * @brief Pointer to help menu.
     */
    QMenu *helpMenu = nullptr;
    /**
     * @brief Action for about.
     */
    QAction *aboutAction = nullptr;
    /**
     * @brief Action for about Qt.
     */
    QAction *aboutQtAction = nullptr;

    /**
     * @brief Main layout of window.
     * @details Up menu, down tabs.
     */
    QVBoxLayout *mainLayout = nullptr;

    /**
     * @brief Main tab wiget.
     */
    QTabWidget *mainTabWidget = nullptr;

    LinksTabWidget *linksTabWidget = nullptr;
    StartTabWidget *startTabWidget = nullptr;
    ToolsTabWidget *toolsTabWidget = nullptr;

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    /**
     * @brief Function that shows message box about program.
     */
    void showAboutMessage();
};
#endif // MAINWIDGET_H
