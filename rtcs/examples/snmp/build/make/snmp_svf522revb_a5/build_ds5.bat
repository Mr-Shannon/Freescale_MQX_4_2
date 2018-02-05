@echo OFF
set NOPAUSE=%1
SET CWD=%CD%
cd ../../../../../../mqx/build/make/bsp_svf522revb_a5
mingw32-make TOOL=ds5 CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../mqx/build/make/psp_svf522revb_a5
mingw32-make TOOL=ds5 CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../build/make/rtcs_svf522revb_a5
mingw32-make TOOL=ds5 CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
mingw32-make TOOL=ds5 CONFIG=debug LOAD=ddr build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
SET CWD=%CD%
cd ../../../../../../mqx/build/make/bsp_svf522revb_a5
mingw32-make TOOL=ds5 CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../mqx/build/make/psp_svf522revb_a5
mingw32-make TOOL=ds5 CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../build/make/rtcs_svf522revb_a5
mingw32-make TOOL=ds5 CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
mingw32-make TOOL=ds5 CONFIG=release LOAD=ddr build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)

if not "%NOPAUSE%" == "nopause" (pause)
