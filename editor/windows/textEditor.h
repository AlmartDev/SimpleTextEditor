#pragma once

#include <imgui.h>
#include <string>
#include <vector>
#include <algorithm>

namespace editor {
    class Editor {
        public:
            void show(bool* p_open);
            bool showEditor;

            void addFile(std::string name, std::string path, std::string buffer);
            void removeFile(std::string name);

            std::string getWorkingPath() { return workingPath; }
            const char* getBuffer() { return buffer; }
            float getFontSize() { return fontSize; }

            ImFont* codeFont;
        private:
            std::vector<std::string> filesBuf;
            std::vector<std::string> filesNames;
            std::vector<std::string> filesPath;

            std::vector<bool*> showTabs;

            std::string workingPath = "";

            float fontSize = 15.0f;

            const char* buffer;
    };
} // namespace editor