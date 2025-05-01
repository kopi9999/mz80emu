#include "MainFrame.h"
#include "FileOperations.hpp"
#include <iostream>
#include <windows.h>


std::string ReturnDirectory() 
{
    char buffer[MAX_PATH];

    GetModuleFileNameA(NULL, buffer, MAX_PATH);

    std::string path(buffer);

    std::cout<<buffer<<std::endl;

    size_t lastSlash = path.find_last_of("\\/");

    std::cout<<lastSlash<<std::endl;

    path.resize(lastSlash+1);
    
    std::cout<<path<<std::endl;

    path += "*.*";

    std::cout<<path<<std::endl;

    WIN32_FIND_DATA file;
    HANDLE file_handle = NULL;
    //std::string path = "E:\\projekt\\mz80emu\\build\\Debug\\*.*";
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