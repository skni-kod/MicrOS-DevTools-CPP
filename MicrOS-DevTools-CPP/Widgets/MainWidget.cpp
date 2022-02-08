#include "MainWidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    /// Menu bar
    menuBar = new QMenuBar();
    programMenu = new QMenu(tr("&Program"));
    menuBar->addMenu(programMenu);
    exitAction = new QAction(tr("&Wyjście"));
    exitAction->setShortcut(QKeySequence(tr("Ctrl+Q")));
    programMenu->addSeparator();
    programMenu->addAction(exitAction);
    helpMenu = new QMenu(tr("P&omoc"));
    menuBar->addMenu(helpMenu);
    aboutAction = new QAction(tr("&O programie"));
    aboutQtAction = new QAction(tr("O &Qt"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

    /// Layouts
    mainLayout = new QVBoxLayout();
    mainLayout->setMenuBar(menuBar);

    // Tab widget
    mainTabWidget = new QTabWidget();
    mainLayout->addWidget(mainTabWidget);
    mainTabWidget->setMinimumWidth(500);
    mainTabWidget->setMinimumHeight(400);

    startTabWidget = new StartTabWidget();
    toolsTabWidget = new ToolsTabWidget();

    mainTabWidget->addTab(startTabWidget, tr("Start"));
    mainTabWidget->addTab(toolsTabWidget, tr("Narzędzia"));
    mainTabWidget->addTab(new QWidget(), tr("Środowisko"));
    mainTabWidget->addTab(new QWidget(), tr("Konfiguracja budownia"));

    this->setLayout(mainLayout);

    // Connections
    connect(exitAction,SIGNAL(triggered()),qApp,SLOT(quit()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAboutMessage()));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

MainWidget::~MainWidget()
{
}

void MainWidget::showAboutMessage()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("O programie"));
    msgBox.setText(tr("<h3>O programie</h3>"
                      "<p>Program stanowi narzędzie developerskie przydatne programistom MicrOSa.</p>"
                      "<p>Wersja: 0.1</p>"
                      "<p>MicrOS to 32-bitowy system operacyjny, opracowany przez członków Sekcji Aplikacji Desktopowych Mobilnych i Webowych. "
                      "Naszym głównym celem było stworzenie od podstaw OS'a posiadającego możliwości podobne do systemu operacyjnego MS-DOS.</p>"
                      "<p>Repozytorium narzędzia MicrOS DevTools CPP (<a href=\"https://github.com/AzuxDario/MicrOS-DevTools-CPP\">www.github.com</a>)"
                      "<p>Repozytorium systemu MicrOS (<a href=\"https://github.com/skni-kod/MicrOS\">www.github.com</a>)"
                      "<p>W tworzeniu programu wykorzystano Qt 5.12 (<a href=\"https://www.qt.io/\">www.qt.io</a>)</p>"
                      "<p>Program objęty jest licencją GPL 3.0 (<a href=\"https://www.gnu.org/licenses/gpl-3.0.en.html\">www.gnu.org/licenses/gpl-3.0.en.html</a>)</p>"));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}
