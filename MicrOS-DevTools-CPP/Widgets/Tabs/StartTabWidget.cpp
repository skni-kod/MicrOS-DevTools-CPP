#include "StartTabWidget.h"
#include <QDebug>
StartTabWidget::StartTabWidget(QWidget *parent) : QWidget(parent)
{
    mainLabel = new QLabel();
    mainLabel->setText(tr("<h3>MicrOS DevTools CPP</h3>"
                          "<p>Program stanowi narzędzie developerskie przydatne programistom MicrOSa.</p>"
                          "<p>Na kolejnych zakładkach znajdziesz:</p>"
                          "<p> - narzędzia potrzebne do rozpoczącia pracy</p>"
                          "<p> - konfigurację środowiska</p>"
                          "<p> - konfigurator skryptów służących uruchomieniu MicrOSa</p>"));
    mainLabel->setOpenExternalLinks(true);
    mainLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    mainLabel->setWordWrap(true);

    nextTabLabel = new QLabel();
    nextTabLabel->setText(tr("<p><b>Jeśli jesteś tu pierwszy raz zacznij od zakładki Przydatne linki.</b></p>"));
    nextTabLabel->setOpenExternalLinks(true);
    nextTabLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    nextTabLabel->setWordWrap(true);

    /// Layouts
    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(mainLabel);
    mainLayout->addStretch();
    mainLayout->addWidget(nextTabLabel);
    this->setLayout(mainLayout);
}

StartTabWidget::~StartTabWidget()
{
}
