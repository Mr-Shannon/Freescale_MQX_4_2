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

:label_cw10gcc
IF NOT EXIST "%OUTPUTDIR%" mkdir "%OUTPUTDIR%"
IF NOT EXIST "%OUTPUTDIR%\." mkdir "%OUTPUTDIR%\."
copy "%ROOTDIR%\ffs\source\nandflash_wl.h" "%OUTPUTDIR%\nandflash_wl.h" /Y
copy "%ROOTDIR%\ffs\source\nandflash_wl_ffs.h" "%OUTPUTDIR%\nandflash_wl_ffs.h" /Y
copy "%ROOTDIR%\ffs\source\nandflash_wl_config.h" "%OUTPUTDIR%\nandflash_wl_config.h" /Y
goto end_script


:label_gcc_arm
IF NOT EXIST "%OUTPUTDIR%" mkdir "%OUTPUTDIR%"
IF NOT EXIST "%OUTPUTDIR%\." mkdir "%OUTPUTDIR%\."
copy "%ROOTDIR%\ffs\source\nandflash_wl.h" "%OUTPUTDIR%\nandflash_wl.h" /Y
copy "%ROOTDIR%\ffs\source\nandflash_wl_ffs.h" "%OUTPUTDIR%\nandflash_wl_ffs.h" /Y
copy "%ROOTDIR%\ffs\source\nandflash_wl_config.h" "%OUTPUTDIR%\nandflash_wl_config.h" /Y
goto end_script


:label_kds
IF NOT EXIST "%OUTPUTDIR%" mkdir "%OUTPUTDIR%"
IF NOT EXIST "%OUTPUTDIR%\." mkdir "%OUTPUTDIR%\."
copy "%ROOTDIR%\ffs\source\nandflash_wl.h" "%OUTPUTDIR%\nandflash_wl.h" /Y
copy "%ROOTDIR%\ffs\source\nandflash_wl_ffs.h" "%OUTPUTDIR%\nandflash_wl_ffs.h" /Y
copy "%ROOTDIR%\ffs\source\nandflash_wl_config.h" "%OUTPUTDIR%\nandflash_wl_config.h" /Y
goto end_script


:label_uv4
IF NOT EXIST "%OUTPUTDIR%" mkdir "%OUTPUTDIR%"
IF NOT EXIST "%OUTPUTDIR%\." mkdir "%OUTPUTDIR%\."
copy "%ROOTDIR%\ffs\source\nandflash_wl.h" "%OUTPUTDIR%\nandflash_wl.h" /Y
copy "%ROOTDIR%\ffs\source\nandflash_wl_ffs.h" "%OUTPUTDIR%\nandflash_wl_ffs.h" /Y
copy "%ROOTDIR%\ffs\source\nandflash_wl_config.h" "%OUTPUTDIR%\nandflash_wl_config.h" /Y
goto end_script


:label_iar
IF NOT EXIST "%OUTPUTDIR%" mkdir "%OUTPUTDIR%"
IF NOT EXIST "%OUTPUTDIR%\." mkdir "%OUTPUTDIR%\."
copy "%ROOTDIR%\ffs\source\nandflash_wl.h" "%OUTPUTDIR%\nandflash_wl.h" /Y
copy "%ROOTDIR%\ffs\source\nandflash_wl_ffs.h" "%OUTPUTDIR%\nandflash_wl_ffs.h" /Y
copy "%ROOTDIR%\ffs\source\nandflash_wl_config.h" "%OUTPUTDIR%\nandflash_wl_config.h" /Y
goto end_script



:end_script

