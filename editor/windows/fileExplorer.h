#pragma once

#include <imgui.h>
#include <string>
#include "../fileManager.h"

#include "textEditor.h"

namespace editor {
    class FileExplorer {
        public:
            FileExplorer(editor::FileManager* _fileManager, editor::Editor* _textEditor);
            ~FileExplorer();

            void show(bool* p_open);
            bool showExplorer;

            void openFile(std::string path);
            void saveFile(std::string path, std::string buffer);
        private:
            editor::FileManager* fileManager;
            editor::Editor* textEditor; // text editor
    };
}