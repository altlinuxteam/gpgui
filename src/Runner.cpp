#include "config.h"

#include <QScopedPointer>
#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>

#include <QStringList>

#include "MainWindow.h"

#include "Runner.h"

Runner::Runner(int argc, char **argv, QString dispname, QString appname, QString appver, QString orgname, QString orgdomain) {
    Q_INIT_RESOURCE(gpgui); // Initialize gpgui.qrc metadata.

    /* Please ensure argc and argv lifetime is enough otherwise
     * the application will segfault on attempt to access
     * qApp->arguments() because of NULL pointer */
    this->argc = argc;
    this->argv = argv;

    this->app = new QApplication(this->argc, this->argv);
    this->app->setApplicationDisplayName(dispname);
    this->app->setApplicationName(appname);
    this->app->setApplicationVersion(appver);
    this->app->setOrganizationName(orgname);
    this->app->setOrganizationDomain(orgdomain);
}

void
Runner::arg_parser() {
    QCommandLineParser cli_parser;
    cli_parser.setApplicationDescription(QCoreApplication::applicationName());
    cli_parser.addHelpOption();
    cli_parser.addVersionOption();
    const QStringList arg_list = qApp->arguments();
    cli_parser.process(arg_list);
}

int
Runner::run() {
    this->arg_parser();

    qgui::MainWindow mainWin;
    mainWin.show();

    return app->exec();
}
