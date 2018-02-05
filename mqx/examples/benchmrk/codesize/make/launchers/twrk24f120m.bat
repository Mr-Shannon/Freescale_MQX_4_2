@echo off

set BOARD=twrk24f120m
REM set KDS_DIR=C:/FREESC~1/KDS_25~1.0
REM set IAR_DIR=C:/PROGRA~1/IARSYS~1/EMBEDD~1.0
REM set UV4_DIR=C:/Keil
REM set GCCARM_DIR=c:/PROGRA~1/GNUTOO~1/4F412~1.820

cd ..
call make_one.bat %BOARD% cortex_m kds      intflash kds %KDS_DIR%
call make_one.bat %BOARD% cortex_m iar      intflash iar %IAR_DIR%
call make_one.bat %BOARD% cortex_m uv4      intflash uv4 %UV4_DIR%
call make_one.bat %BOARD% cortex_m gcc_arm  intflash gcc_arm %GCCARM_DIR%
cd launchers
