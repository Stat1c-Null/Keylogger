#ifndef TIMER_H
#define TIMER_H
#include <thread>
#include <chrono>

//Create a function to get our program to do certain activities in specific period of time
class Timer
{
    std::thread Thread;
    bool Alive = false;//See if timer is running or not
    long CallNumber = -1L;//Determine how many times we want to call a certain function.-1 default value L stands for long
    //Example: Attempts to send mail 5 times
    //The reason to create long is because this keylogger might run for over a year and we want it to store all numbers
    long repeat_count = -1L;//Count how many times we actually called a function(it worked)

};

#endif // TIMER_H
