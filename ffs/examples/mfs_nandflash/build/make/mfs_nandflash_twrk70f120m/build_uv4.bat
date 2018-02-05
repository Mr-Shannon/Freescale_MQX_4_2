@echo OFF
set NOPAUSE=%1
SET CWD=%CD%
cd ../../../../../../mqx/build/make/bsp_twrk70f120m
mingw32-make TOOL=uv4 CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../mqx/build/make/psp_twrk70f120m
mingw32-make TOOL=uv4 CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../mfs/build/make/mfs_twrk70f120m
mingw32-make TOOL=uv4 CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../build/make/ffs_twrk70f120m
mingw32-make TOOL=uv4 CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../shell/build/make/shell_twrk70f120m
mingw32-make TOOL=uv4 CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
mingw32-make TOOL=uv4 CONFIG=debug LOAD=intflash_sramdata build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
SET CWD=%CD%
cd ../../../../../../mqx/build/make/bsp_twrk70f120m
mingw32-make TOOL=uv4 CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../mqx/build/make/psp_twrk70f120m
mingw32-make TOOL=uv4 CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../mfs/build/make/mfs_twrk70f120m
mingw32-make TOOL=uv4 CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../build/make/ffs_twrk70f120m
mingw32-make TOOL=uv4 CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../shell/build/make/shell_twrk70f120m
mingw32-make TOOL=uv4 CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
mingw32-make TOOL=uv4 CONFIG=release LOAD=intflash_sramdata build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
SET CWD=%CD%
cd ../../../../../../mqx/build/make/bsp_twrk70f120m
mingw32-make TOOL=uv4 CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../mqx/build/make/psp_twrk70f120m
mingw32-make TOOL=uv4 CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../mfs/build/make/mfs_twrk70f120m
mingw32-make TOOL=uv4 CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../build/make/ffs_twrk70f120m
mingw32-make TOOL=uv4 CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../shell/build/make/shell_twrk70f120m
mingw32-make TOOL=uv4 CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
mingw32-make TOOL=uv4 CONFIG=debug LOAD=intflash_ddrdata build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
SET CWD=%CD%
cd ../../../../../../mqx/build/make/bsp_twrk70f120m
mingw32-make TOOL=uv4 CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../mqx/build/make/psp_twrk70f120m
mingw32-make TOOL=uv4 CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../mfs/build/make/mfs_twrk70f120m
mingw32-make TOOL=uv4 CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../build/make/ffs_twrk70f120m
mingw32-make TOOL=uv4 CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../shell/build/make/shell_twrk70f120m
mingw32-make TOOL=uv4 CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
mingw32-make TOOL=uv4 CONFIG=release LOAD=intflash_ddrdata build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)

if not "%NOPAUSE%" == "nopause" (pause)
