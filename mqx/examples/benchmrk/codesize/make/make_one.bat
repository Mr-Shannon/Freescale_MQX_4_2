@echo off
path %PATH%;C:\MinGW\bin

rem Take parameters
set BOARD=%1
set PSPDIR=%2
set TOOL=%3
set LOAD=%4
set MAPFMT=%5
set TOOLCHAIN_DIR=%6


for %%A in (typical maximum small) do CALL :FOR_LOOP %%A
goto done

:FOR_LOOP
REM build_bsp
echo #########@@@ Building for %BOARD% with %TOOL%: BSP %1
mingw32-make.exe -C mkbsp BOARD=%BOARD% TOOL=%TOOL% CODESIZE_CFG=%1 MAPFMT=%MAPFMT% TOOLCHAIN_DIR=%TOOLCHAIN_DIR% build 

REM build_psp
echo #########@@@ Building for %BOARD% with %TOOL%: PSP %1 
mingw32-make.exe -C mkpsp BOARD=%BOARD% TOOL=%TOOL% CODESIZE_CFG=%1 MAPFMT=%MAPFMT% TOOLCHAIN_DIR=%TOOLCHAIN_DIR% build 

REM remove verif_enabled_config.h in output dir as it is not a correct one to use
cd ../output/lib
del verif_enabled_config.h /S /Q /F
cd ../../make

REM build_app
echo #########@@@ Building for %BOARD% with %TOOL%: APP %1_MAX 
mingw32-make.exe -C mkapp BOARD=%BOARD% TOOL=%TOOL% LOAD=%LOAD% PSP_DIR=%PSPDIR% CODESIZE_CFG=%1 CODESIZE_TARGET=MAX MAPFMT=%MAPFMT% TOOLCHAIN_DIR=%TOOLCHAIN_DIR% build 
echo #########@@@ Building for %BOARD% with %TOOL%: APP %1_SMALL 
mingw32-make.exe -C mkapp BOARD=%BOARD% TOOL=%TOOL% LOAD=%LOAD% PSP_DIR=%PSPDIR% CODESIZE_CFG=%1 CODESIZE_TARGET=SMALL MAPFMT=%MAPFMT% TOOLCHAIN_DIR=%TOOLCHAIN_DIR% build 
echo #########@@@ Building for %BOARD% with %TOOL%: APP %1_TYPICAL
mingw32-make.exe -C mkapp BOARD=%BOARD% TOOL=%TOOL% LOAD=%LOAD% PSP_DIR=%PSPDIR% CODESIZE_CFG=%1 CODESIZE_TARGET=TYPICAL MAPFMT=%MAPFMT% TOOLCHAIN_DIR=%TOOLCHAIN_DIR% build 
if %1==small echo #########@@@ Building for %BOARD% with %TOOL%: APP %1_TINIEST 
if %1==small mingw32-make.exe -C mkapp BOARD=%BOARD% TOOL=%TOOL% LOAD=%LOAD% PSP_DIR=%PSPDIR% CODESIZE_CFG=%1 CODESIZE_TARGET=TINIEST MAPFMT=%MAPFMT% TOOLCHAIN_DIR=%TOOLCHAIN_DIR% build 


:done
