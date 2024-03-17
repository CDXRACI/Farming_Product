@echo off

set /A VAR = 10
set /A VAR_2 = 20
set /A SUM = %VAR_2% + %VAR%
if %SUM%==30 ( echo "The value is %SUM%") else ( echo "NONE" )
if %VAR%==10 (
	if %VAR_2%==20 (
	echo "Hello world")
) else ( echo "The dir" )

REM and or not in batch
set /A VAR_3 = 1
set /A VAR_4 = 2
REM AND
if %VAR_3%==1 if %VAR_4%==2 echo "Hi"
REM or
if %VAR_3%==1 set res=true
if %VAR_4%==2 set res=true
if defined res (
	echo true
)else ( echo False 
)
REM not
if not %VAR_3%==2 ( echo "corrected"
)

set /A a=100
if %a%==100 goto :labelOne

:labelOne
echo "The value of a is 50"
exit /b 0