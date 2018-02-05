@echo OFF
set NOPAUSE=%1
mingw32-make TOOL=iar CONFIG=debug LINKER_FILE=$(MQX_ROOTDIR)/../mqx/examples/bootloader_vybrid_qspixip/sram_iar_m4.icf clean
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
mingw32-make TOOL=iar CONFIG=release LINKER_FILE=$(MQX_ROOTDIR)/../mqx/examples/bootloader_vybrid_qspixip/sram_iar_m4.icf clean
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)

if not "%NOPAUSE%" == "nopause" (pause)
