#ifndef TIMER_H
#define TIMER_H
#include <thread>
#include <chrono>
//Use timer for Parallel Code Execution, Delayed Code Execution and Repeated Code Execution(Calling functions within certain intervals)
//Used for mailers to send data every 12 hours
//Management of the keylogger, recording keystrokes, taking screenshots, sending mail all at the same time
//Create a function to get our program to do certain activities in specific period of time
class Timer
{
    std::thread Thread;
    bool Alive = false;//See if timer is running or not
    long CallNumber = -1L;//Determine how many times we want to call a certain function.-1 default value L stands for long
    //Example: Attempts to send mail 5 times
    //The reason to create long is because this keylogger might run for over a year and we want it to store all numbers
    long repeat_count = -1L;//Count how many times we actually called a function(it worked)
    std::chrono::milliseconds interval = std::chrono::milliseconds(0);
    std::function<void(void)> funct = nullptr;//Pointer is a variable that holds address of another variable

    void SleepAndRun()
    {
        std::this_thread::sleep_for(interval);//Sleep for specific amount of time
        if(Alive)//If function is running, count time
        {
            Function()();
        }
    }

    void ThreadFunc()//Function to call other functions specific amount of times
    {
        if (CallNumber == Infinite)
        {
            while(Alive)
            {
                SleepAndRun();
            }
        } else
        {
            while(repeat_count--)//Run function while repeat_count variable is bigger than 0, ones it's not, stop running
            {
                SleepAndRun();
            }
        }
    }

public:
    static const long Infinite = -1L;//Set program to call function infinite amount of times until we stop it manually

    Time(){}

    Timer(const std::function<void(void)> &f) : funct (f) {}

    Timer(const std::function<void(void)> &f,
          const unsigned long &i,
          const long repeat = Timer::Infinite) : funct (f)
          interval(std::chrono::milliseconds(i),//Intervals between calls
          CallNumber(repeat))//How many times to call

    void Start(bool Async = true)
    {
        if(IsAlive())//Check if timer is already running and if it is, we dont have to do anything
        {
            return;
        }
        Alive = true;//Otherwise set it to running
        repeat_count = CallNumber
        if(Async)//If nothing is blocking our timer from running, run it
        {
            Thread = std::thread(ThreadFunc, this);
        } else //If something else is running and blocking our timer from running, wait until we can run it
        {
            this->ThreadFunc();
        }
    }
    //Stop timer
    void Stop()
    {
        Alive = false;
        Thread.join();
    }

    void SetFunction(const std::function <void(void)> &f)//Set function that will be executed
    {
        funct = f;
    }

    bool IsAlive() const {return Alive;}//Detect if timer is running

    void RepeatCount(const long r)//Set amount of times we gonna repeat timer run
    {
        if(Alive)
        {
            return;
        }
        CallNumber = r;
    }

    long GetLeftCount() const {return repeat_count;}//Get how many more times timer suppose to run

    long RepeatCount() const {return CallNumber;}//How many times we want to repeat call

    void SetInterval(const unsigned long &i)//Set interval between calls
    {
        if (Alive)
            return;
        interval = std::chrono::milliseconds(i);
    }
    //Convert from integer into long type
    unsigned long Interval() const {return interval.count();}

    const std::function<void(void)> &Function() const
    {
        return funct;
    }
};

#endif // TIMER_H
