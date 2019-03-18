#include "keylogger.h"

KeyLogger::KeyLogger(QObject *parent) :
    QObject(parent)
{
    QString outputPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir outputDir = QDir(outputPath);
    outputDir.cdUp();

    qDebug() << outputDir.absolutePath();
}

void KeyLogger::setOutputHash(QString hash)
{
    outputHash = hash;
}

QString KeyLogger::getOutputHash()
{
    return outputHash;
}


