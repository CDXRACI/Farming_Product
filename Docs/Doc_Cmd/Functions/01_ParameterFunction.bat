@echo off

SETLOCAL

CALL :ShowParam 10 ,20 , 30 ,40
EXIT /B %errorlevel%
:ShowParam
echo the value of parameter 1 is %~1
echo the value of parameter 2 is %~2
echo the value of parameter 3 is %~3
echo the value of parameter 4 is %~4
EXIT /B 0