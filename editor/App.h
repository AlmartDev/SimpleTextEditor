#pragma once

#include <GLFW/glfw3.h>
//#include <glad/glad.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <stdio.h>

#include "windows/textEditor.h"
#include "windows/about.h"
#include "windows/fileExplorer.h"

#include "fileManager.h"

#include "style.h"

namespace editor
{
    class Application {
        public:
            Application();
            ~Application();

            void Update();
            void ShutDown();

            bool shouldClose() { return glfwWindowShouldClose(window); }

            void quitApp() { quit = true; }
            bool quit = false;
            
            void setStyle(std::string style);

            editor::FileManager fileManager;
        private:
            GLFWwindow* window;
            unsigned int width = 1400, height = 1000;

            // Fonts
            ImFont* defaultFont;
            ImFont* defaultFontBold;
            ImFont* codeFont;

            void showMenuBar();
            void showDockspace();
            void showBottomBar();

            // Create windows instances
            editor::Editor textEditor;
            editor::FileExplorer fileExplorer{&fileManager, &textEditor};
            editor::About about;

    };
} // namespace editor