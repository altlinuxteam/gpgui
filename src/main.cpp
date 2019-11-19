#include "config.h"

#include <memory>

#include "Runner.h"

int main(int argc, char **argv) {
    std::unique_ptr<Runner> app(new Runner(argc, argv, GPGUI_ORGANIZATION, GPGUI_APPLICATION_NAME, GPGUI_VERSION));
    return app->run();
}

