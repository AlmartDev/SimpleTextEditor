#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

#include <algorithm>

#include <string>
#include <cstring>

namespace editor {
    class FileManager {
        public:
            ~FileManager();

            std::string openFile(std::string path);
            void saveFile(std::string path, std::string buffer);

            std::vector<std::vector<std::string>> listFiles(std::string path);

            void newFile(std::string path);

            void renameFile(std::string path, std::string newPath);
            void deleteFile(std::string path);

            std::string getPath() { return path; }
            std::string getFullPath() { return fullPath; }
            std::string getFileName(std::string path);

            void setPath(std::string _path);
        private:
            std::string path = "";
            std::string fullPath = "";
    };
}