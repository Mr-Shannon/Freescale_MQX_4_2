@echo OFF
set NOPAUSE=%1
SET CWD=%CD%
cd ../../../../../build/make/bsp_twrvf65gs10_m4
mingw32-make TOOL=gcc_arm CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../build/make/psp_twrvf65gs10_m4
mingw32-make TOOL=gcc_arm CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
mingw32-make TOOL=gcc_arm CONFIG=debug LOAD=ram build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
SET CWD=%CD%
cd ../../../../../build/make/bsp_twrvf65gs10_m4
mingw32-make TOOL=gcc_arm CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../build/make/psp_twrvf65gs10_m4
mingw32-make TOOL=gcc_arm CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
mingw32-make TOOL=gcc_arm CONFIG=release LOAD=ram build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)

if not "%NOPAUSE%" == "nopause" (pause)
