#include "config.h"

#include <memory>

#include <QScopedPointer>
#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>

#include "MainWindow.h"

#include "Runner.h"

Runner::Runner(int argc, char **argv, QString orgname, QString appname, QString appver) {
    //Q_INIT_RESOURCE(application);

    this->app = new QApplication(argc, argv);
    QCoreApplication::setOrganizationName(orgname);
    QCoreApplication::setApplicationName(appname);
    QCoreApplication::setApplicationVersion(appver);
}

void
Runner::arg_parser() {
    QCommandLineParser cli_parser;
    cli_parser.setApplicationDescription(QCoreApplication::applicationName());
    cli_parser.addHelpOption();
    cli_parser.addVersionOption();
    //cli_parser.process(this->app);
}

int
Runner::run() {
    this->arg_parser();

    QGUI::MainWindow mainWin;
    mainWin.show();

    return app->exec();
}
