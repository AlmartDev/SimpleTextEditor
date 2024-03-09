#include "App.h"
#include "fileManager.h"

#include <string>

int main(int argc, char *argv[])
{
    editor::Application app;
    std::string filePath;

    // arguments 
    if (argc > 1 && std::string(argv[1]) == "--path" || argc > 1 && std::string(argv[1]) == "-p")
    {
        if (argc > 2)
        {
            filePath = std::string(argv[2]);
            app.fileManager.setPath(filePath);

        // TODO: Use imgui file manager instead
        }
        else
        {
            printf("No file path provided\n");
        }
    }
    else if (argc > 1 && std::string(argv[1]) == "--style" || argc > 1 && std::string(argv[1]) == "-s")
    {
        if (argc > 2)
        {
            std::string style = std::string(argv[2]);
            app.setStyle(style);
        }
        else
        {
            printf("No style provided\n");
        }
    }

    // TODO: make arguments work together :)

    while (!app.shouldClose())
    {
        if (app.quit) { break; }
        app.Update();
    }

    app.ShutDown();

    return 0;   // yay! program finished!
}