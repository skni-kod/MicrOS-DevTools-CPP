#include "main.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setAppPallete();

    MainWidget w;
    w.show();
    return a.exec();
}

void setAppPallete()
{
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette p = qApp->palette();
    p.setColor(QPalette::Window, QColor(53,53,53));
    p.setColor(QPalette::WindowText, Qt::white);
    p.setColor(QPalette::Base, QColor(35,35,35));
    p.setColor(QPalette::AlternateBase, QColor(53,53,53));
    p.setColor(QPalette::ToolTipBase, Qt::white);
    p.setColor(QPalette::ToolTipText, Qt::white);
    p.setColor(QPalette::Text, Qt::white);
    p.setColor(QPalette::Button, QColor(53,53,53));
    p.setColor(QPalette::ButtonText, Qt::white);
    p.setColor(QPalette::BrightText, Qt::red);
    p.setColor(QPalette::Highlight, QColor(00,102,204).lighter());
    p.setColor(QPalette::HighlightedText, Qt::black);
    p.setColor(QPalette::Link, QColor(Qt::blue).lighter());
    p.setColor(QPalette::LinkVisited, QColor(Qt::blue).lighter());

    p.setColor(QPalette::Disabled, QPalette::Base, QColor(25,25,25));
    p.setColor(QPalette::Disabled, QPalette::Text, Qt::darkGray);
    p.setColor(QPalette::Disabled, QPalette::Button, QColor(43,43,43));
    p.setColor(QPalette::Disabled, QPalette::ButtonText, Qt::darkGray);
    qApp->setPalette(p);
}
