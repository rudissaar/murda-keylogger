#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QString>
#include <QStringList>

#include "constants.h"
#include "core.h"
#include "wrapper.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCommandLineParser parser;

    parser.addHelpOption();
    parser.addVersionOption();

    parser.process(app);
    Wrapper wrapper;

    return app.exec();
}
