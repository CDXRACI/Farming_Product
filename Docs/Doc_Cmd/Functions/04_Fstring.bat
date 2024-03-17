@echo off
set Str=OUTSIDE
echo %str%
CALL :setmyString Str
echo %str%
EXIT /B %errorlevel%
:setmyString
setlocal
set str=inside
set "%~1=%str%"
echo %str%
endlocal
EXIT /B 0