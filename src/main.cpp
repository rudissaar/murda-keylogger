#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QStandardPaths>
#include <QString>

#include <iostream>
#include <windows.h>

static HHOOK hHook = nullptr;

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QString outputPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir outputDir = QDir(outputPath);
    outputDir.cdUp();

    qDebug() << outputDir.absolutePath();

    if (hHook == nullptr) {
        return 1;
    }

    return app.exec();
}
