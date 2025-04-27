#include "MainFrame.h"
#include "FileOperations.hpp"
#include <iostream>
#include <windows.h>


std::string ReturnDirectory() 
{
    WIN32_FIND_DATA file;
    HANDLE file_handle = NULL;
    std::string path = "E:\\projekt\\mz80emu\\build\\Debug\\*.*";
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