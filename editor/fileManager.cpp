#include "fileManager.h"

namespace editor {
    FileManager::~FileManager() {
        path = "";
        fullPath = "";
    }

    void FileManager::setPath(std::string _path) {
        path = _path;
        fullPath = std::filesystem::absolute(path).string();
    }

    std::string FileManager::getFileName(std::string path) {
        return std::filesystem::path(path).filename().string();
    }

    std::vector<std::vector<std::string>> FileManager::listFiles(std::string path) {
        std::vector<std::string> fileName;
        std::vector<std::string> filePath;

        for (const auto & entry : std::filesystem::directory_iterator(path)) {
            std::string entry_name = entry.path().filename().string();
            if (std::filesystem::is_directory(entry.path())) {
                entry_name = "./" + entry_name;
            }
            fileName.push_back(entry_name);
            filePath.push_back(entry.path().string());
        }
        
        // Order files alphabetically
        for (int i = 0; i < fileName.size(); i++) {
            for (int j = i + 1; j < fileName.size(); j++) {
                if (fileName[i] > fileName[j]) {
                    std::swap(fileName[i], fileName[j]);
                    std::swap(filePath[i], filePath[j]);
                }
            }
        }

        std::vector<std::vector<std::string>> files;
        files.push_back(fileName);
        files.push_back(filePath);

        return files;
    }
            
    std::string FileManager::openFile(std::string path) {
        std::string buffer = "";

        std::ifstream file; 
        file.open(path);

        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                buffer += line + "\n";
            }
        }
        // else: file not found!

        return buffer;
    }

    void FileManager::saveFile(std::string path, std::string buffer) {
        std::ofstream file;
        file.open(path);
        file << buffer;
        file.close();
    }

    void FileManager::newFile(std::string path) {
        std::ofstream file;
        file.open(path);    // Saving a file but without buffer
        file.close();
    }

    void FileManager::renameFile(std::string path, std::string newPath) {
        
        char oldname[path.length() + 1];
        strcpy(oldname, path.c_str());

        char newname[newPath.length() + 1];
        strcpy(newname, newPath.c_str());

        std::rename(oldname, newname);
    }

    void FileManager::deleteFile(std::string path) {
        char _path[path.length() + 1];
        strcpy(_path, path.c_str());
        
        std::remove(_path);
    }
}