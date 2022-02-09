#include "EnvironmentTabWidget.h"

EnvironmentTabWidget::EnvironmentTabWidget(QWidget *parent) : QWidget(parent)
{
    mainLabel = new QLabel();
    mainLabel->setText(tr("<h3>Konfiguracja środowiska MSYS</h3>"));
    mainLabel->setOpenExternalLinks(true);
    mainLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    mainLabel->setWordWrap(true);

    nextTabLabel = new QLabel();
    nextTabLabel->setText(tr("<p><b>Po skonfigurowniu środowiska możesz przejść do zakładki Kompilator.</b></p>"));
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

EnvironmentTabWidget::~EnvironmentTabWidget()
{

}
