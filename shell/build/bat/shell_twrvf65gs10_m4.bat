@echo off

rem convert path to backslash format
set ROOTDIR=%1
set ROOTDIR=%ROOTDIR:/=\%
set ROOTDIR=%ROOTDIR:"=%
set OUTPUTDIR=%2
set OUTPUTDIR=%OUTPUTDIR:/=\%
set OUTPUTDIR=%OUTPUTDIR:"=%
set TOOL=%3

rem process one of label bellow
goto label_%TOOL%

:label_gcc_arm
IF NOT EXIST "%OUTPUTDIR%" mkdir "%OUTPUTDIR%"
IF NOT EXIST "%OUTPUTDIR%\." mkdir "%OUTPUTDIR%\."
copy "%ROOTDIR%\shell\source\include\sh_mfs.h" "%OUTPUTDIR%\sh_mfs.h" /Y
copy "%ROOTDIR%\shell\source\include\shell.h" "%OUTPUTDIR%\shell.h" /Y
copy "%ROOTDIR%\shell\source\include\sh_rtcs.h" "%OUTPUTDIR%\sh_rtcs.h" /Y
copy "%ROOTDIR%\shell\source\include\sh_enet.h" "%OUTPUTDIR%\sh_enet.h" /Y
goto end_script


:label_ds5
IF NOT EXIST "%OUTPUTDIR%" mkdir "%OUTPUTDIR%"
IF NOT EXIST "%OUTPUTDIR%\." mkdir "%OUTPUTDIR%\."
copy "%ROOTDIR%\shell\source\include\sh_mfs.h" "%OUTPUTDIR%\sh_mfs.h" /Y
copy "%ROOTDIR%\shell\source\include\shell.h" "%OUTPUTDIR%\shell.h" /Y
copy "%ROOTDIR%\shell\source\include\sh_rtcs.h" "%OUTPUTDIR%\sh_rtcs.h" /Y
copy "%ROOTDIR%\shell\source\include\sh_enet.h" "%OUTPUTDIR%\sh_enet.h" /Y
goto end_script


:label_iar
IF NOT EXIST "%OUTPUTDIR%" mkdir "%OUTPUTDIR%"
IF NOT EXIST "%OUTPUTDIR%\." mkdir "%OUTPUTDIR%\."
copy "%ROOTDIR%\shell\source\include\sh_mfs.h" "%OUTPUTDIR%\sh_mfs.h" /Y
copy "%ROOTDIR%\shell\source\include\shell.h" "%OUTPUTDIR%\shell.h" /Y
copy "%ROOTDIR%\shell\source\include\sh_rtcs.h" "%OUTPUTDIR%\sh_rtcs.h" /Y
copy "%ROOTDIR%\shell\source\include\sh_enet.h" "%OUTPUTDIR%\sh_enet.h" /Y
goto end_script



:end_script

