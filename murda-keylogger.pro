QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    src/constants.h \
    src/keylogger.h \
    src/wrapper.h

SOURCES += \
    src/main.cpp \
    src/keylogger.cpp \
    src/wrapper.cpp

OTHER_FILES += \
    .gitignore
