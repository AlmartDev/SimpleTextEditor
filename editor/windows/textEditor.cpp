#include "textEditor.h"

namespace editor {
    void Editor::show(bool* p_open) {
        if (!*p_open) return;
        
        ImGui::SetNextWindowSize(ImVec2(800, 600));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f)); 

        ImGui::Begin("Text Editor", p_open);

        if (ImGui::BeginTabBar("Text Editor Tabs")) {
            for (int i = 0; i < filesBuf.size(); i++) {

                if (ImGui::BeginTabItem(filesNames[i].c_str(), showTabs[i])) {

                    if (ImGui::Button("+"))
                        fontSize += 1.0f;

                    ImGui::SameLine();
                    
                    if (ImGui::Button("-"))
                        fontSize -= 1.0f;

                    // super simple python script running
                    if (filesNames[i].substr(filesNames[i].find_last_of(".") + 1) == "py") {
                        ImGui::SameLine();
                        if (ImGui::Button("Run")) {
                            std::string command = "python " + filesPath[i];
                            system(command.c_str());
                        }
                    }

                    ImGui::PushFont(codeFont);
                    // Line number
                    unsigned int lineCount = std::count(filesBuf[i].begin(), filesBuf[i].end(), '\n');
                    //for (int i = 0; i < lineCount; i++) {
                    //    ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "%d", i + 1);
                    //}

                    // TODO: Colors for syntax highlighting

                    // filesBuf[i] is the buffer from the file when it was opened, but its size is not updated when the user types in the editor
                    // so we need to create a new buffer and update it with the new size of the file so we can edit it and save it
                    ImGui::InputTextMultiline("##source", const_cast<char*>(filesBuf[i].c_str()), sizeof(filesBuf[i]) + 1, ImVec2(-1.0f, -1.0f), ImGuiInputTextFlags_AllowTabInput);
                
                    this->buffer = const_cast<char*>(filesBuf[i].c_str());

                    ImGui::PopFont();

                    if (ImGui::IsItemVisible()) {
                        workingPath = filesPath[i];
                    }

                    ImGui::EndTabItem();
                }
                
                if (!*showTabs[i]) {
                    removeFile(filesPath[i]);
                    showEditor = true;
                }
            }
            ImGui::EndTabBar();
        }

        ImGui::PopStyleVar();


        if (filesBuf.size() == 0) {
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("  Open a file from File Explorer to start editing.").x) * 0.5f);
            ImGui::SetCursorPosY((ImGui::GetWindowSize().y * 0.5f));
            ImGui::Image((void*)0, ImVec2(16, 16));
            ImGui::SameLine();
            ImGui::Text("Open a file from File Explorer to start editing.");
        }

        ImGui::End();
    }

    void Editor::addFile(std::string name, std::string path, std::string buffer) {
        showEditor = true;

        for (int i = 0; i < filesNames.size(); i++) {
            if (filesNames[i] == name) {
                return;
            }
        }

        filesNames.push_back(name);
        filesPath.push_back(path);
        filesBuf.push_back(buffer);

        showTabs.push_back(&showEditor);
    }

    void Editor::removeFile(std::string path) {
        for (int i = 0; i < filesPath.size(); i++) {
            if (filesPath[i] == path) {
                filesNames.erase(filesNames.begin() + i);
                filesPath.erase(filesPath.begin() + i);
                filesBuf.erase(filesBuf.begin() + i);

                showTabs.erase(showTabs.begin() + i);
            }
        }
    }
}