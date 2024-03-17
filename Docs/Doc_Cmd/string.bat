@echo off
SET first=Hello
SET second=World
SET /A NUM=20
SET finalString=%first% %second% %NUM%
echo %finalString%
set str=hello_from_cdp
echo.%str%
set str=%str:~0,5%
echo.%str%
set str=hello_from_cdp
echo.%str%
set str=%str:~-5%
echo %str%

set str1= My name is CD Phuc abc. It's easy to learn my name.
echo %str1%

set str1=%str1:CD= %
echo %str1%

set str1= My name is CD Phuc abc. It's easy to learn my name.
echo %str1%

set str1=%str1:~2,-1%
echo %str1%
REM ~ truoc - sau