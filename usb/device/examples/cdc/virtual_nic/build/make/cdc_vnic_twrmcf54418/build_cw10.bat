@echo OFF
set NOPAUSE=%1
SET CWD=%CD%
cd ../../../../../../../../mqx/build/make/bsp_twrmcf54418
mingw32-make TOOL=cw10 CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../../../mqx/build/make/psp_twrmcf54418
mingw32-make TOOL=cw10 CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../../../rtcs/build/make/rtcs_twrmcf54418
mingw32-make TOOL=cw10 CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../build/make/usbd_twrmcf54418
mingw32-make TOOL=cw10 CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
mingw32-make TOOL=cw10 CONFIG=debug LOAD=extram build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
SET CWD=%CD%
cd ../../../../../../../../mqx/build/make/bsp_twrmcf54418
mingw32-make TOOL=cw10 CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../../../mqx/build/make/psp_twrmcf54418
mingw32-make TOOL=cw10 CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../../../rtcs/build/make/rtcs_twrmcf54418
mingw32-make TOOL=cw10 CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../build/make/usbd_twrmcf54418
mingw32-make TOOL=cw10 CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
mingw32-make TOOL=cw10 CONFIG=debug LOAD=extflash build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
SET CWD=%CD%
cd ../../../../../../../../mqx/build/make/bsp_twrmcf54418
mingw32-make TOOL=cw10 CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../../../mqx/build/make/psp_twrmcf54418
mingw32-make TOOL=cw10 CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../../../rtcs/build/make/rtcs_twrmcf54418
mingw32-make TOOL=cw10 CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../build/make/usbd_twrmcf54418
mingw32-make TOOL=cw10 CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
mingw32-make TOOL=cw10 CONFIG=release LOAD=extflash build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)

if not "%NOPAUSE%" == "nopause" (pause)
