@echo OFF
set NOPAUSE=%1
mingw32-make TOOL=ds5 CONFIG=debug LOAD=ddr clean
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
mingw32-make TOOL=ds5 CONFIG=release LOAD=ddr clean
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)

if not "%NOPAUSE%" == "nopause" (pause)
