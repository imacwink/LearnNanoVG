#include "application.h"

int main(int argc, char *argv[])
{
    STAPP::Application app;
    return app.RunLoop(argc, argv);
}
