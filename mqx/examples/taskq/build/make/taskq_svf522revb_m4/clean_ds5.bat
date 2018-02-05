@echo OFF
set NOPAUSE=%1
mingw32-make TOOL=ds5 CONFIG=debug LOAD=ram clean
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
mingw32-make TOOL=ds5 CONFIG=release LOAD=ram clean
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)

if not "%NOPAUSE%" == "nopause" (pause)
