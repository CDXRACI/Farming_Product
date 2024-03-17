@echo off
set myArray= 1 2 3 4 5 6
(for %%i in (%myArray%) do (
	echo %%i 
))

set arr[0]=10
set arr[1]=20
echo hi %arr[0]%