@echo OFF
set NOPAUSE=%1
mingw32-make TOOL=gcc_arm CONFIG=debug LINKER_FILE=$(MQX_ROOTDIR)/../mqx/examples/bootloader_vybrid_qspixip/sram_gcc_arm_a5.ld clean
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
mingw32-make TOOL=gcc_arm CONFIG=release LINKER_FILE=$(MQX_ROOTDIR)/../mqx/examples/bootloader_vybrid_qspixip/sram_gcc_arm_a5.ld clean
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)

if not "%NOPAUSE%" == "nopause" (pause)
