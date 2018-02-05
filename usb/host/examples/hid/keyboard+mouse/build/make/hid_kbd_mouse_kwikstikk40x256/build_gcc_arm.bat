@echo OFF
set NOPAUSE=%1
SET CWD=%CD%
cd ../../../../../../../../mqx/build/make/bsp_kwikstikk40x256
mingw32-make TOOL=gcc_arm CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../../../mqx/build/make/psp_kwikstikk40x256
mingw32-make TOOL=gcc_arm CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../build/make/usbh_kwikstikk40x256
mingw32-make TOOL=gcc_arm CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
mingw32-make TOOL=gcc_arm CONFIG=debug LOAD=intflash build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
SET CWD=%CD%
cd ../../../../../../../../mqx/build/make/bsp_kwikstikk40x256
mingw32-make TOOL=gcc_arm CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../../../mqx/build/make/psp_kwikstikk40x256
mingw32-make TOOL=gcc_arm CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../build/make/usbh_kwikstikk40x256
mingw32-make TOOL=gcc_arm CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
mingw32-make TOOL=gcc_arm CONFIG=release LOAD=intflash build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)

if not "%NOPAUSE%" == "nopause" (pause)
