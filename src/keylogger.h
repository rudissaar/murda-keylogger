#ifndef KEYLOGGER_H
#define KEYLOGGER_H

#include <QDebug>
#include <QDir>
#include <QStandardPaths>
#include <QObject>
#include <QString>

class KeyLogger :
    public QObject
{
    Q_OBJECT

public:
    explicit KeyLogger(QObject *parent = nullptr);

    void setOutputHash(QString hash);
    QString getOutputHash();

private:
    QString outputHash;
};

#endif // KEYLOGGER_H
