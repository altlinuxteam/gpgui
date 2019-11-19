#include "config.h"

#include <memory>

#include "Runner.h"

int main(int argc, char **argv) {
    std::unique_ptr<Runner> app(new Runner(argc, argv, GPGUI_APPLICATION_DISPLAY_NAME, GPGUI_APPLICATION_NAME, GPGUI_VERSION, GPGUI_ORGANIZATION, GPGUI_ORGANIZATION_DOMAIN));
    return app->run();
}

