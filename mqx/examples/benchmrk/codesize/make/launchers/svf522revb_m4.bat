@echo off

set BOARD=svf522revb_m4
REM set IAR_DIR=C:/PROGRA~1/IARSYS~1/EMBEDD~1.0
REM set DS5_DIR=C:/Keil
REM set GCCARM_DIR=c:/PROGRA~1/GNUTOO~1/4F412~1.820

cd ..
call make_one.bat %BOARD% cortex_m iar      ram iar %IAR_DIR%
call make_one.bat %BOARD% cortex_m ds5      ram ds5 %DS5_DIR%
call make_one.bat %BOARD% cortex_m gcc_arm  ram gcc_arm %GCCARM_DIR%
cd launchers
