QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    src/constants.h \
    src/wrapper.h \
    src/core.h

SOURCES += \
    src/main.cpp \
    src/wrapper.cpp \
    src/core.cpp

OTHER_FILES += \
    .gitignore
