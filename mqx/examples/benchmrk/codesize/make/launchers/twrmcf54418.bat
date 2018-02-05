@echo off

set BOARD=twrmcf54418
REM set CW10_DIR=C:/FREESC~1/CW_MCU~1.6

cd ..
call make_one.bat %BOARD% coldfire cw10  extflash cw10 %CW10_DIR%
cd launchers
