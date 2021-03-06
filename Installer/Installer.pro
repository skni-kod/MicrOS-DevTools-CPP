TEMPLATE = aux

INSTALLER = MicrOS DevTools CPP Installer.exe

INPUT = $$PWD/config/config.xml $$PWD/packages
example.input = INPUT
example.output = $$INSTALLER
example.commands = ../../bin/binarycreator --online-only -c $$PWD/config/config.xml -p $$PWD/packages "${QMAKE_FILE_OUT}"
example.CONFIG += target_predeps no_link combine

QMAKE_EXTRA_COMPILERS += example

OTHER_FILES = README
