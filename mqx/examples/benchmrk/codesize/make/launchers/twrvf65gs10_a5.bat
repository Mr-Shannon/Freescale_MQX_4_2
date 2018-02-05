@echo off

set BOARD=twrvf65gs10_a5
REM set IAR_DIR=C:/PROGRA~1/IARSYS~1/EMBEDD~1.0
REM set DS5_DIR=C:/Keil
REM set GCCARM_DIR=c:/PROGRA~1/GNUTOO~1/4F412~1.820

cd ..
REM call make_one.bat %BOARD% cortex_a iar      ddr iar %IAR_DIR%
REM call make_one.bat %BOARD% cortex_a ds5      ddr ds5 %DS5_DIR%
call make_one.bat %BOARD% cortex_a gcc_arm  ddr gcc_arm %GCCARM_DIR%
cd launchers
