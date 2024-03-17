@echo off
CALL :ShowValue
EXIT /B %errorlevel%
:ShowValue
set /A age=30
echo the value of age is %age%
EXIT /B 0