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
copy "%ROOTDIR%\mfs\source\include\mfs_cnfg.h" "%OUTPUTDIR%\mfs_cnfg.h" /Y
copy "%ROOTDIR%\mfs\source\include\mfs_rev.h" "%OUTPUTDIR%\mfs_rev.h" /Y
copy "%ROOTDIR%\mfs\source\include\mfs.h" "%OUTPUTDIR%\mfs.h" /Y
copy "%ROOTDIR%\mfs\source\include\part_mgr.h" "%OUTPUTDIR%\part_mgr.h" /Y
goto end_script


:label_kds
IF NOT EXIST "%OUTPUTDIR%" mkdir "%OUTPUTDIR%"
IF NOT EXIST "%OUTPUTDIR%\." mkdir "%OUTPUTDIR%\."
copy "%ROOTDIR%\mfs\source\include\mfs_cnfg.h" "%OUTPUTDIR%\mfs_cnfg.h" /Y
copy "%ROOTDIR%\mfs\source\include\mfs_rev.h" "%OUTPUTDIR%\mfs_rev.h" /Y
copy "%ROOTDIR%\mfs\source\include\mfs.h" "%OUTPUTDIR%\mfs.h" /Y
copy "%ROOTDIR%\mfs\source\include\part_mgr.h" "%OUTPUTDIR%\part_mgr.h" /Y
goto end_script


:label_uv4
IF NOT EXIST "%OUTPUTDIR%" mkdir "%OUTPUTDIR%"
IF NOT EXIST "%OUTPUTDIR%\." mkdir "%OUTPUTDIR%\."
copy "%ROOTDIR%\mfs\source\include\mfs_cnfg.h" "%OUTPUTDIR%\mfs_cnfg.h" /Y
copy "%ROOTDIR%\mfs\source\include\mfs_rev.h" "%OUTPUTDIR%\mfs_rev.h" /Y
copy "%ROOTDIR%\mfs\source\include\mfs.h" "%OUTPUTDIR%\mfs.h" /Y
copy "%ROOTDIR%\mfs\source\include\part_mgr.h" "%OUTPUTDIR%\part_mgr.h" /Y
goto end_script


:label_iar
IF NOT EXIST "%OUTPUTDIR%" mkdir "%OUTPUTDIR%"
IF NOT EXIST "%OUTPUTDIR%\." mkdir "%OUTPUTDIR%\."
copy "%ROOTDIR%\mfs\source\include\mfs_cnfg.h" "%OUTPUTDIR%\mfs_cnfg.h" /Y
copy "%ROOTDIR%\mfs\source\include\mfs_rev.h" "%OUTPUTDIR%\mfs_rev.h" /Y
copy "%ROOTDIR%\mfs\source\include\mfs.h" "%OUTPUTDIR%\mfs.h" /Y
copy "%ROOTDIR%\mfs\source\include\part_mgr.h" "%OUTPUTDIR%\part_mgr.h" /Y
goto end_script



:end_script

