#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <QStringList>

#include <windows.h>

#include "constants.h"
#include "core.h"
#include "wrapper.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName(ORGANIZATION_DOMAIN);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(APPLICATION_NAME);
    QCoreApplication::setApplicationVersion(APPLICATION_VERSION);

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
