@echo off
set s_title=Learn c 
echo %s_title%
set s_sub_title=---------------------------------$
echo %s_sub_title%
del output.exe
set s_clear=Delete output file
echo %s_clear%
echo %s_sub_title%
gcc main.c -o output.exe
set s_gen=Generated file from source code
echo %s_gen%
echo %s_sub_title%
set s_exc=executing file
echo %s_exc%
echo %s_sub_title%
echo off
.\output.exe
