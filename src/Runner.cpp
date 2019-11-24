/*
Copyright (c) 2019 Igor Chudov <nir@sarfsc.ru>

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. Neither the name of the Igor Chudov nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "config.h"

#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QScopedPointer>

#include <QStringList>

#include "MainWindow.h"

#include "Runner.h"

Runner::Runner(int argc, char **argv, QString dispname, QString appname,
               QString appver, QString orgname, QString orgdomain) {
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

void Runner::arg_parser() {
    QCommandLineParser cli_parser;
    cli_parser.setApplicationDescription(QCoreApplication::applicationName());
    cli_parser.addHelpOption();
    cli_parser.addVersionOption();
    const QStringList arg_list = qApp->arguments();
    cli_parser.process(arg_list);
}

int Runner::run() {
    this->arg_parser();

    qgui::MainWindow mainWin;
    mainWin.show();

    return app->exec();
}
