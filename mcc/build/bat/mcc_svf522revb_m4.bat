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
copy "%ROOTDIR%\mcc\source\include\mcc_vf600.h" "%OUTPUTDIR%\mcc_vf600.h" /Y
copy "%ROOTDIR%\mcc\source\include\mcc_api.h" "%OUTPUTDIR%\mcc_api.h" /Y
copy "%ROOTDIR%\mcc\source\include\mcc_common.h" "%OUTPUTDIR%\mcc_common.h" /Y
copy "%ROOTDIR%\mcc\source\include\mqx\mcc_config.h" "%OUTPUTDIR%\mcc_config.h" /Y
copy "%ROOTDIR%\mcc\source\include\mcc_mqx.h" "%OUTPUTDIR%\mcc_mqx.h" /Y
goto end_script


:label_ds5
IF NOT EXIST "%OUTPUTDIR%" mkdir "%OUTPUTDIR%"
IF NOT EXIST "%OUTPUTDIR%\." mkdir "%OUTPUTDIR%\."
copy "%ROOTDIR%\mcc\source\include\mcc_vf600.h" "%OUTPUTDIR%\mcc_vf600.h" /Y
copy "%ROOTDIR%\mcc\source\include\mcc_api.h" "%OUTPUTDIR%\mcc_api.h" /Y
copy "%ROOTDIR%\mcc\source\include\mcc_common.h" "%OUTPUTDIR%\mcc_common.h" /Y
copy "%ROOTDIR%\mcc\source\include\mqx\mcc_config.h" "%OUTPUTDIR%\mcc_config.h" /Y
copy "%ROOTDIR%\mcc\source\include\mcc_mqx.h" "%OUTPUTDIR%\mcc_mqx.h" /Y
goto end_script


:label_iar
IF NOT EXIST "%OUTPUTDIR%" mkdir "%OUTPUTDIR%"
IF NOT EXIST "%OUTPUTDIR%\." mkdir "%OUTPUTDIR%\."
copy "%ROOTDIR%\mcc\source\include\mcc_vf600.h" "%OUTPUTDIR%\mcc_vf600.h" /Y
copy "%ROOTDIR%\mcc\source\include\mcc_api.h" "%OUTPUTDIR%\mcc_api.h" /Y
copy "%ROOTDIR%\mcc\source\include\mcc_common.h" "%OUTPUTDIR%\mcc_common.h" /Y
copy "%ROOTDIR%\mcc\source\include\mqx\mcc_config.h" "%OUTPUTDIR%\mcc_config.h" /Y
copy "%ROOTDIR%\mcc\source\include\mcc_mqx.h" "%OUTPUTDIR%\mcc_mqx.h" /Y
goto end_script



:end_script

