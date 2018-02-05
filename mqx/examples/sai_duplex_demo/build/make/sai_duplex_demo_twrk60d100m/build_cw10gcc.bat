@echo OFF
set NOPAUSE=%1
SET CWD=%CD%
cd ../../../../../build/make/bsp_twrk60d100m
mingw32-make TOOL=cw10gcc CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../build/make/psp_twrk60d100m
mingw32-make TOOL=cw10gcc CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../mfs/build/make/mfs_twrk60d100m
mingw32-make TOOL=cw10gcc CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../shell/build/make/shell_twrk60d100m
mingw32-make TOOL=cw10gcc CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
mingw32-make TOOL=cw10gcc CONFIG=debug LOAD=intflash build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
SET CWD=%CD%
cd ../../../../../build/make/bsp_twrk60d100m
mingw32-make TOOL=cw10gcc CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../build/make/psp_twrk60d100m
mingw32-make TOOL=cw10gcc CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../mfs/build/make/mfs_twrk60d100m
mingw32-make TOOL=cw10gcc CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../shell/build/make/shell_twrk60d100m
mingw32-make TOOL=cw10gcc CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
mingw32-make TOOL=cw10gcc CONFIG=release LOAD=intflash build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)

if not "%NOPAUSE%" == "nopause" (pause)
