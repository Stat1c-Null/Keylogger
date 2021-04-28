#ifndef HELPER_H
#define HELPER_H
#include <ctime>//Get Time
#include <string>//Convert variables into text
#include <sstream>//Helper to convert into strings
#include <fstream>

namespace Helper
{
    template <class T>
    //Convert into string
    std::string ToString(const T &);//T is a data that we want to convert into string
    //In structs all the data is public and available to access
    struct DateTime//Record time of usage
    {
        DateTime()
        {
            time_t ms;//Record Time in Milliseconds
            time(&ms);
            //Info is a pointer to the struct tm and a type from ctime library
            //Pointers are variables that contain memory addresses in computer's RAM of another variable
            //Refered as pointy. And we can access the variable to which they are pointing
            //that will help local time function to receive a variable, and memory address in RAM
            struct tm * info = localtime(&ms);
            D = info->tm_mday;//Days
            m = info->tm_mon + 1;//Months.Add one because by default it's 0
            y = 1900 + info->tm_year;//Years. Count starts from 1900
            M = info->tm_min;//Minutes
            H = info->tm_hour;//Hours
            S = info->tm_sec;//Seconds
        }
        //Create DateTime instance and user will provide the parameters
        DateTime(int D, int m, int y, int H, int M, int S) : D(D), m(m),y(y), H(H), M(M), S(S) {}
        DateTime(int D, int m, int y) : D(D), m(m), y(y), H(0), M(0), S(0) {}

        //Method to get current DateTime
        DateTime Now() const
        {
            return DateTime();
        }

        int D, m, y, H, M, S;

        //Format Date into Human Readable form
        std::string GetDateString() const
        {
            //If number of days or months is less than 10 put 0 before the number, otherwise nothing
            return std::string( D < 10 ? "0" : "") + ToString(D) +
                   std::string( m < 10 ? ".0" : "") + ToString(m) + "." +
                   ToString(y);
        }
        //DD.mm.YYYY
        //Format Time into Human Readable form
        std::string GetTimeString(const std::string &sep = ":")
        {
            return std::string( H < 10 ? "0" : "") + ToString(H) + sep +
                   std::string( M < 10 ? "0" : "") + ToString(M) + sep +
                   std::string( S < 10 ? "0" : "") + ToString(S);
        }
        //Return combined Date and Time
        std::string GetDateTimeString( const std::string &sep = ":")
        {
            return GetDateString() + " " + GetTimeString(sep);
        }
    };

    //Receive anything that supports the insertion operator
    template <class T>
    std::string ToString(const T &e)
    {
        std::ostringstream s;//Output String Stream
        s << e;//Insertion operator is << sign
        return s.str();
    }

    //Function to create log file for debugging
    //CAN BE REMOVED AFTER DEVELOPMENT IS DONE
    void WriteAppLog( const std::string &s)
    {
        std::ofstream file("AppLog.txt", std::ios::app);//Save the Log and time of the recording
        file << "[" << Helper::DateTime().GetDateTimeString() << "]" <<
        "\n" << s << std::endl << "\n";
        file.close();
    }

}

#endif // HELPER_H
