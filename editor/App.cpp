#include "App.h"
#include <string>

//testing
#include <iostream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define SystemOpenURL(url) system("start " url);
#elif __APPLE__
#define SystemOpenURL(url) system("open " url);
#elif __linux__
#define SystemOpenURL(url) system("xdg-open " url);
#else
#error "Unknown compiler"
#endif


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
        codeFont = io.Fonts->AddFontFromFileTTF("/home/almartan/dev/simpletexteditor/editor/fonts/CascadiaCodePL-Regular.ttf", 15);   // TODO: Change before release (This is my favourite font for code!)

        io.Fonts->Build();
        io.FontDefault = defaultFont;

        fileDialog.SetTitle("Open Directory");
        fileDialog.SetInputName("Open");
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

            if (showRenameDialog && textEditor.getWorkingPath() != "") {
                // Open popup to rename file
                ImGui::OpenPopup("Rename file");
                ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_FirstUseEver);
                if (ImGui::BeginPopupModal("Rename file", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                    static char newName[128];
                    ImGui::InputText("New name", newName, IM_ARRAYSIZE(newName));
                    if (ImGui::Button("Rename")) {
                        textEditor.removeFile(textEditor.getWorkingPath());
                        fileManager.renameFile(textEditor.getWorkingPath(), fileManager.getFullPath() + "/" + newName);
                        showRenameDialog = false;
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Cancel")) {
                        showRenameDialog = false;
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::EndPopup();
                }
            }
            if (showSaveAsDialog && textEditor.getWorkingPath() != "") {
                fileDialogFiles.Open();
                fileDialogFiles.Display();
                fileDialogFiles.SetTitle("Save As");
                std::string workingFileName = textEditor.getWorkingPath().substr(textEditor.getWorkingPath().find_last_of("/") + 1);
                if (fileDialog.HasSelected()) {
                    fileManager.saveFile(fileDialog.GetSelected().string() + workingFileName, textEditor.getBuffer());
                    fileDialogFiles.ClearSelected();
                    showSaveAsDialog = false;
                }
            }
            if (showOpenFileDialog) {
                fileDialogFiles.Open();
                fileDialogFiles.Display();
                fileDialogFiles.SetTitle("Open File");
                if (fileDialogFiles.HasSelected()) {
                    std::string name = fileDialogFiles.GetSelected().string().substr(fileDialogFiles.GetSelected().string().find_last_of("/") + 1);
                    std::string buf = fileManager.openFile(fileDialogFiles.GetSelected().string());

                    textEditor.addFile(fileDialogFiles.GetSelected().string(), name, buf);
                    fileDialogFiles.ClearSelected();
                    showOpenFileDialog = false;
                }
            }
        }
        else {
            fileDialog.Open();
            fileDialog.Display();
            if (fileDialog.HasSelected()) {
                fileManager.setPath(fileDialog.GetSelected().string());
                fileDialog.ClearSelected();
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
                if (ImGui::MenuItem("New")) {
                    textEditor.addFile("Untitled", fileManager.getFullPath(), "");
                }
                if (ImGui::MenuItem("Open")) {
                    showOpenFileDialog = true;
                }
                if (ImGui::MenuItem("Open Directory")) {
                    fileManager.setPath("");
                }
                if (ImGui::MenuItem("Save")) {
                    fileManager.saveFile(textEditor.getWorkingPath(), textEditor.getBuffer());
                }
                if (ImGui::MenuItem("Save As")) {
                    showSaveAsDialog = true;
                }
                if (ImGui::MenuItem("Delete")) {
                    // Delete file
                    fileManager.deleteFile(textEditor.getWorkingPath());
                    // Close tab
                    textEditor.removeFile(textEditor.getWorkingPath());
                }
                if (ImGui::MenuItem("Rename")) {
                    showRenameDialog = true;
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
            if (ImGui::BeginMenu("Help")) {
                if (ImGui::MenuItem("About")) {
                    about.showAbout = true;
                }
                if (ImGui::MenuItem("GitHub")) {
                    // Open GitHub page
                    SystemOpenURL("https://github.com/almartdev/simpletexteditor");
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
