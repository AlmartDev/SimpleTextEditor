#include "fileExplorer.h"
#include <filesystem>
#include <stdio.h>

//#include "../image.h"

namespace editor {
    FileExplorer::FileExplorer(editor::FileManager* _fileManager, editor::Editor* _textEditor) {
        fileManager = _fileManager;
        textEditor = _textEditor;
    }

    FileExplorer::~FileExplorer() {
    }

    void FileExplorer::show(bool* p_open) {
        ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
        if (!ImGui::Begin("File Explorer", p_open)) {
            ImGui::End();
            return;
        }

        //ImGui::Text("Current Path: %s", fileManager->getFullPath().c_str());
        std::vector<std::vector<std::string>> files = fileManager->listFiles(fileManager->getFullPath());

        // icons
        // create image from "icons/file.svg" with a size of 16x16


        static int selected = -1;        

        ImGui::BeginChild("left pane", ImVec2(250, 0), false);
        for (int i = 0; i < files[0].size(); i++) {

            char label[128];
            sprintf(label, files[0][i].c_str());
            if (files[0][i].find("/") == std::string::npos) {
                if (ImGui::Selectable(label, selected == i)) {
                    FileExplorer::openFile(files[1][i]);
                }
            }
            else {
                // open folder
                // instead of opening the file, we're gonna make a dropdown with the files inside the folder
                std::vector<std::vector<std::string>> folderFiles = fileManager->listFiles(files[1][i]);

                if (ImGui::TreeNode(label)) {
                    for (int j = 0; j < folderFiles[0].size(); j++) {
                        char label[128];
                        sprintf(label, folderFiles[0][j].c_str());

                        ImGui::Image((void*)0, ImVec2(16, 16)); // update this!
                        ImGui::SameLine(0, 10);

                        if (ImGui::Selectable(label, selected == i)) {
                            FileExplorer::openFile(folderFiles[1][j]);
                        }
                    }
                    ImGui::TreePop();
                }
            }
               
            selected = i;
            
            /*
               What is happening here: (Might be a better way to do this)
               listFiles gets the working directory and returns a list of files and their paths; every file is a list,
               the first element is the file name and the second element is the file path.
               The for loop iterates through the list of files and creates a selectable item for each file.
            */
        }   
        ImGui::EndChild();
        ImGui::End();
    }

    void FileExplorer::openFile(std::string path) {
        std::string buffer = fileManager->openFile(path);   // error here
        std::string name = fileManager->getFileName(path);

        textEditor->addFile(name, path, buffer); // would create a new tab with the file's content
    }

    void FileExplorer::saveFile(std::string path, std::string buffer) {
        fileManager->saveFile(path, buffer);
    }
} // namespace editor