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
                          "<p> - konfigurator skryptów służących uruchomieniu MicrOSa</p>"
                          "<p><b>Jeśli jesteś tu pierwszy raz zacznij od zakładki Przydatne linki.</b></p>"));
    mainLabel->setOpenExternalLinks(true);
    mainLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    mainLabel->setWordWrap(true);

    /// Layouts
    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(mainLabel);
    mainLayout->addStretch();
    this->setLayout(mainLayout);
}

StartTabWidget::~StartTabWidget()
{
}
