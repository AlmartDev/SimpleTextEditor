#include "App.h"
#include "fileManager.h"
#include "inputParser.h"

#include <string>

int main(int argc, char *argv[])
{
    editor::Application app;
    std::string filePath;

    InputParser input(argc, argv);

    if (input.cmdOptionExists("-p"))
    {
        filePath = input.getCmdOption("-f");
        app.fileManager.setPath(filePath);
    }

    if (input.cmdOptionExists("-s"))
    {
        std::string style = input.getCmdOption("-s");
        app.setStyle(style);
    }

    while (!app.shouldClose())
    {
        if (app.quit) { break; }
        app.Update();
    }

    app.ShutDown();

    return 0;   // yay! program finished!
}