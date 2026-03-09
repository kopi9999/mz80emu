#include "MainFrame.h"
#include "FileOperations.hpp"
#include <iostream>
#include <windows.h>
#include <fstream>

std::string ReturnDirectory() 
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string path(buffer);
    size_t lastSlash = path.find_last_of("\\/");
    path.resize(lastSlash+1);
    path += "*.*";
    WIN32_FIND_DATA file;
    HANDLE file_handle = NULL;
    std::wstring path2(path.begin(), path.end());
    file_handle = FindFirstFile(path2.c_str() , &file);
    std::string output;
    std::wstring temp;
    do{
        temp = file.cFileName;
        output += std::string(temp.begin() , temp.end()) + " \n";
    }while(FindNextFile(file_handle, &file));
    FindClose(file_handle);
    return output;
}

void createTextFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename); // opens the file (creates if not exists)
    
    if (file.is_open()) {
        file << content;           // write content to the file
        file.close();              // always close the file
        std::cout << "File created: " << filename << std::endl;
    } else {
        std::cerr << "Failed to create file: " << filename << std::endl;
    }
}