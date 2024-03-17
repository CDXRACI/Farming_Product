@echo off 
FOR /L %%i IN (1,2,10) DO (
	ECHO %%i
)
FOR /L %%i IN (10,-1,1) DO (
	ECHO %%i)