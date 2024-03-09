#include "App.h"
#include <string>

//testing
#include <iostream>

namespace editor
{
    // Function prototypes
    void glfwErrorCallback(int error, const char* description);

    Application::Application() {
        
        // Initialize GLFW
        glfwInit();

        // Create a windowed mode window and its OpenGL context
        GLFWwindow* window = glfwCreateWindow(Application::width, Application::height, "Simple Text Editor", NULL, NULL);

        Application::window = window;

        if (!window) {
            glfwTerminate();
        }

        // Make the window's context current
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Enable vsync

        // Setup ImGui binding
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        // enable docking
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        const char* glsl_version = "#version 130";
        ImGui_ImplOpenGL3_Init(glsl_version);

        // Setup style (default dark)
        editor::style::setStyleDark();

        //ImGui::StyleColorsDark();
        defaultFont = io.Fonts->AddFontFromFileTTF("/home/almartan/dev/TextEditor/editor/fonts/Roboto-Medium.ttf", 15);   // TODO: Change before release
        defaultFontBold = io.Fonts->AddFontFromFileTTF("/home/almartan/dev/TextEditor/editor/fonts/Roboto-Bold.ttf", 18);   // TODO: Change before release
        codeFont = io.Fonts->AddFontFromFileTTF("/home/almartan/dev/TextEditor/build/bin/debug/fonts/NotoSansMono-Regular.ttf", 15);   // TODO: Change before release

        io.Fonts->Build();
        io.FontDefault = defaultFont;
    }

    Application::~Application() {
        ShutDown();
    }

    void Application::ShutDown() {
        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Application::Update() {        
        glfwPollEvents();

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        
        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // If theres no path selected, do not render any window 
        if (fileManager.getPath() != "") {
            // Update window title
            std::string title = "Simple Text Editor  1.0  -  ";

            if (textEditor.getWorkingPath() == "") {
                title += fileManager.getFullPath();
            }
            else
                title += textEditor.getWorkingPath();
            glfwSetWindowTitle(window, title.c_str());

            Application::showMenuBar();
            Application::showDockspace();
            Application::showBottomBar();

            // Render windows
            
            codeFont->Scale = textEditor.getFontSize() / 15.0f;
            textEditor.codeFont = codeFont;

            if (textEditor.showEditor) {
                textEditor.show(&textEditor.showEditor);
            }
            
            if (fileExplorer.showExplorer) {
                fileExplorer.show(&fileExplorer.showExplorer);
            }

            if (about.showAbout) {
                about.show(&about.showAbout);
            }
        }
        else {
            // Open a full size popup that asks for a file path
            // TODO: Maybe use imgui file manager repo instead

            ImGui::OpenPopup("Open File");
            if (ImGui::BeginPopupModal("Open File", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                static char path[1024] = "";
                ImGui::InputText("Path", path, IM_ARRAYSIZE(path));
                if (ImGui::Button("Open")) {
                    fileManager.setPath(std::string(path));
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
        }

        ImGui::Render();    
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    void Application::setStyle(std::string style) {
        if (style == "dark") {
            editor::style::setStyleDark();
        }
        else if (style == "classic") {
            editor::style::setStyleClassic();
        }
        else if (style == "light") {
            editor::style::setStyleLight();
        }
    }

    // Private functions

    void Application::showMenuBar() {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New*")) {
                    // New file
                }
                if (ImGui::MenuItem("Open*")) {
                    // Open file
                }
                if (ImGui::MenuItem("Open directory*")) {
                    // Open dir
                }
                if (ImGui::MenuItem("Save*")) {
                    // Save file
                }
                if (ImGui::MenuItem("Save As*")) {
                    // Save file as
                }
                if (ImGui::BeginMenu("Working File")) {
                    if (ImGui::MenuItem("Delete")) {
                        // Delete file
                        fileManager.deleteFile(textEditor.getWorkingPath());
                        // Close tab
                        textEditor.removeFile(textEditor.getWorkingPath());
                    }
                    if (ImGui::MenuItem("Rename*")) {
                        // Rename file
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::MenuItem("Exit")) {
                    quitApp();         
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("View")) {
                if (ImGui::MenuItem("File Explorer")) {
                    fileExplorer.showExplorer = true;
                }
                if (ImGui::MenuItem("Text Editor")) {
                    textEditor.showEditor = true;
                }
                if (ImGui::MenuItem("About")) {
                    about.showAbout = true;
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Preferences")) {
                if (ImGui::BeginMenu("Change theme")) {
                    if (ImGui::MenuItem("Dark theme")) 
                        editor::style::setStyleDark();
                    if (ImGui::MenuItem("Classic theme")) 
                        editor::style::setStyleClassic();
                    if (ImGui::MenuItem("Light theme")) 
                        editor::style::setStyleLight();

                    ImGui::Text("* Moddify theme in 'style.h'");
                    
                    ImGui::EndMenu();
                }
                    
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void Application::showDockspace() {
        ImGui::DockSpaceOverViewport();
    }

    void Application::showBottomBar() {
        /*
        if (ImGui::BeginMainMenuBar()) {
            ImGui::Text("Simple Text Editor  1.0  -  ");
            ImGui::SameLine();
            ImGui::Text("Made by Almartan");
            ImGui::EndMainMenuBar();
        }
        */
    }
} // namespace editor
