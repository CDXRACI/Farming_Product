@echo off

echo %1
echo %2

REM set /A variableName=value
set hello=hello world!!
echo %hello%

set /A first =10
set /A second = 30
set /A add = %first + %second 
echo sum = %add%

SETLOCAL
set /A l_var = 1
set /A l_var2 = 2
set /A  sum  = %l_var% + %l_var2%
echo sum = %sum%
ENDLOCAL
echo sum = %sum%