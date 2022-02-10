INCLUDEPATH += Widgets
DEPENDPATH += Widgets
SOURCES += \
    $$PWD/ConsoleWidget.cpp \
    $$PWD/MainWidget.cpp 
HEADERS += \
    $$PWD/ConsoleWidget.h \
    $$PWD/MainWidget.h 
	
include(Tabs/Tabs.pri)

RESOURCES +=
