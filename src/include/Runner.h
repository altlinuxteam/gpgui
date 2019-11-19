#if !defined(__GPGUI_RUNNER_H)
#   define __GPGUI_RUNNER_H 1

#include "config.h"

#include <QString>
#include <QApplication>

class Runner
{
    QApplication *app;
    int argc;
    char **argv;

public:
    Runner(int argc, char **argv, QString dispname, QString appname, QString appver, QString orgname, QString orgdomain);
    void arg_parser();
    int run();
};

#endif /* __GPGUI_RUNNER_H */

