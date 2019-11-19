#if !defined(__GPGUI_RUNNER_H)
#   define __GPGUI_RUNNER_H 1

#include "config.h"

#include <QString>
#include <QApplication>

class Runner
{
    QCoreApplication *app;

public:
    Runner(int argc, char **argv, QString orgname, QString appname, QString appver);
    void arg_parser();
    int run();
};

#endif /* __GPGUI_RUNNER_H */

