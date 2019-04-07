#include <QApplication>
#include <QCommandLineOption>
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

    QCommandLineOption initOption(
        QStringList() << "init",
        QCoreApplication::translate("main", "Initialise the application.")
    );

    parser.addOption(initOption);

    QCommandLineOption sendOption(
        QStringList() << "send",
        QCoreApplication::translate("main", "Send the information.")
    );

    parser.addOption(sendOption);

    QCommandLineOption disposeOption(
        QStringList() << "dispose",
        QCoreApplication::translate("main", "Dispose the application.")
    );

    parser.addOption(disposeOption);

    parser.process(app);
    Wrapper wrapper;

    return app.exec();
}
