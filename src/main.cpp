#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>

#include "config.h"

#include "MainWindow.h"

int main(int argc, char **argv) {
    Q_INIT_RESOURCE(application);

    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("BaseALT");
    QCoreApplication::setApplicationName("GPGUI");
    QCoreApplication::setApplicationVersion(GPGUI_VERSION);

    QCommandLineParser cli_parser;
    cli_parser.setApplicationDescription(QCoreApplication::applicationName());
    cli_parser.addHelpOption();
    cli_parser.addVersionOption();
    cli_parser.process(app);

    return app.exec();
}

