#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QStandardPaths>
#include <QString>
#include <QStringList>

#include <iostream>
#include <windows.h>

static HHOOK hHook = nullptr;

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationVersion("0.0.1");

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption setHashOption(
        QStringList() << "sh" << "set-hash",
        QCoreApplication::translate("main", "Set hash for the output directory."),
        QCoreApplication::translate("main", "hash")
    );

    parser.addOption(setHashOption);

    QCommandLineOption getHashOption(
        QStringList() << "gh" << "get-hash",
        QCoreApplication::translate("main", "Get hash of the output directory.")
    );

    parser.addOption(getHashOption);

    QCommandLineOption setIntervalOption(
        QStringList() << "si" << "set-interval",
        QCoreApplication::translate("main", "Set interval for the output writer."),
        QCoreApplication::translate("main", "ms")
    );

    parser.addOption(setIntervalOption);

    QCommandLineOption getIntervalOption(
        QStringList() << "gi" << "get-interval",
        QCoreApplication::translate("main", "Get interval of the output writer.")
    );

    parser.addOption(getIntervalOption);

    QCommandLineOption sendOption(
        QStringList() << "s" << "send",
        QCoreApplication::translate("main", "Send the information.")
    );

    parser.addOption(sendOption);

    QCommandLineOption disposeOption(
        QStringList() << "d" << "dispose",
        QCoreApplication::translate("main", "Dispose the application.")
    );

    parser.addOption(disposeOption);

    parser.process(app);

    QString outputPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir outputDir = QDir(outputPath);
    outputDir.cdUp();

    qDebug() << outputDir.absolutePath();

    if (hHook == nullptr) {
        return 1;
    }

    return app.exec();
}
