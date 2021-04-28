#include <iostream>
#include <windows.h>//Header to hide output window from showing up
#include "Helper.h"
#include "KeyConstants.h"
using namespace std;

int main()
{
    MSG Msg; //Message to be processed but it will never be processed

    while(GetMessage(&Msg, NULL, 0, 0))//Get a message from user with address of that message
    {
        TranslateMessage(&Msg);//Take message and modify to pass to the system
        DispatchMessage(&Msg);//Forward message to the system invisible
    }
    return 0;
}
