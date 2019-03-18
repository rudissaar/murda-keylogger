QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    src/constants.h \
    src/keylogger.h

SOURCES += \
    src/main.cpp \
    src/keylogger.cpp

OTHER_FILES += \
    .gitignore
