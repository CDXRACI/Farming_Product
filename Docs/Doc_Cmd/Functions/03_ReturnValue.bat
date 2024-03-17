@ECHO OFF

setlocal
call :Setmyval first, second, third
echo %first%
echo %second%
echo %third%
EXIT /B %errorlevel%
:Setmyval
SET "%~1=50"
SET "%~2=100"
SET "%~3=150"
EXIT /B 0