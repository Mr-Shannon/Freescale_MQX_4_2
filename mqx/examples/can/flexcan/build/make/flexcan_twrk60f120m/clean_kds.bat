@echo OFF
set NOPAUSE=%1
mingw32-make TOOL=kds CONFIG=debug LOAD=intflash clean
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
mingw32-make TOOL=kds CONFIG=release LOAD=intflash clean
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)

if not "%NOPAUSE%" == "nopause" (pause)
