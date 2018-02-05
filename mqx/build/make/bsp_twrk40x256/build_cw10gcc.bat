@echo OFF
set NOPAUSE=%1
mingw32-make TOOL=cw10gcc CONFIG=debug build -j3
if errorlevel 1 (
set NOPAUSE=0
pause
)
mingw32-make TOOL=cw10gcc CONFIG=release build -j3
if errorlevel 1 (
set NOPAUSE=0
pause
)

if not "%1" == "nopause" (pause)
