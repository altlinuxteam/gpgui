#include <QApplication>
#include <QCommandLineOptions>
#include <QCommandLineParser>

#include "config.h"

#include "MainWindow.h"

int main(int argc, char **argv) {
    Q_INIT_RESOURCE(application);

    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("BaseALT");
    QCoreApplication::setApplicationName("GPGUI");
    QCoreApplication::setApplicationVersion(GPGUI_VERSION);
}
