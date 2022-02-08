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

    tabsMenu = new QMenu(tr("&Zakładki"));
    menuBar->addMenu(tabsMenu);
    startTabAction = new QAction(tr("&Start"));
    startTabAction->setShortcut(QKeySequence(tr("Ctrl+1")));
    liknsTabAction = new QAction(tr("&Przydatne linki"));
    liknsTabAction->setShortcut(QKeySequence(tr("Ctrl+2")));
    toolsTabAction = new QAction(tr("&Narzędzia"));
    toolsTabAction->setShortcut(QKeySequence(tr("Ctrl+3")));
    environmentTabAction = new QAction(tr("Ś&rodowisko"));
    environmentTabAction->setShortcut(QKeySequence(tr("Ctrl+4")));
    buildingTabAction = new QAction(tr("&Konfiguracja budownia"));
    buildingTabAction->setShortcut(QKeySequence(tr("Ctrl+5")));
    tabsMenu->addAction(startTabAction);
    tabsMenu->addAction(liknsTabAction);
    tabsMenu->addAction(toolsTabAction);
    tabsMenu->addAction(environmentTabAction);
    tabsMenu->addAction(buildingTabAction);

    helpMenu = new QMenu(tr("P&omoc"));
    menuBar->addMenu(helpMenu);
    aboutAction = new QAction(tr("&O programie"));
    aboutAction->setShortcut(QKeySequence(tr("Ctrl+A")));
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

    linksTabWidget = new LinksTabWidget();
    startTabWidget = new StartTabWidget();
    toolsTabWidget = new ToolsTabWidget();

    mainTabWidget->addTab(startTabWidget, tr("Start"));
    mainTabWidget->addTab(linksTabWidget, tr("Przydatne linki"));
    mainTabWidget->addTab(toolsTabWidget, tr("Narzędzia"));
    mainTabWidget->addTab(new QWidget(), tr("Środowisko"));
    mainTabWidget->addTab(new QWidget(), tr("Konfiguracja budownia"));

    this->setLayout(mainLayout);

    // Connections
    connect(exitAction,SIGNAL(triggered()),qApp,SLOT(quit()));
    connect(startTabAction, &QAction::triggered, this, [&]{mainTabWidget->setCurrentIndex(0);});
    connect(liknsTabAction, &QAction::triggered, this, [&]{mainTabWidget->setCurrentIndex(1);});
    connect(toolsTabAction, &QAction::triggered, this, [&]{mainTabWidget->setCurrentIndex(2);});
    connect(environmentTabAction, &QAction::triggered, this, [&]{mainTabWidget->setCurrentIndex(3);});
    connect(buildingTabAction, &QAction::triggered, this, [&]{mainTabWidget->setCurrentIndex(4);});
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
