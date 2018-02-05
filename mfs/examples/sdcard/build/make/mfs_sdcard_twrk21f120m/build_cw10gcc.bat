@echo OFF
set NOPAUSE=%1
SET CWD=%CD%
cd ../../../../../../mqx/build/make/bsp_twrk21f120m
mingw32-make TOOL=cw10gcc CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../mqx/build/make/psp_twrk21f120m
mingw32-make TOOL=cw10gcc CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../build/make/mfs_twrk21f120m
mingw32-make TOOL=cw10gcc CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../shell/build/make/shell_twrk21f120m
mingw32-make TOOL=cw10gcc CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
mingw32-make TOOL=cw10gcc CONFIG=debug LOAD=intflash build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
SET CWD=%CD%
cd ../../../../../../mqx/build/make/bsp_twrk21f120m
mingw32-make TOOL=cw10gcc CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../mqx/build/make/psp_twrk21f120m
mingw32-make TOOL=cw10gcc CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../build/make/mfs_twrk21f120m
mingw32-make TOOL=cw10gcc CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../shell/build/make/shell_twrk21f120m
mingw32-make TOOL=cw10gcc CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
mingw32-make TOOL=cw10gcc CONFIG=release LOAD=intflash build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)

if not "%NOPAUSE%" == "nopause" (pause)
