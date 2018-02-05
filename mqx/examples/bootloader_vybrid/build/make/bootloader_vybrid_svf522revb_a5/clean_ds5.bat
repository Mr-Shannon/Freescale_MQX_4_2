@echo OFF
set NOPAUSE=%1
mingw32-make TOOL=ds5 CONFIG=debug LINKER_FILE=$(MQX_ROOTDIR)/../mqx/examples/bootloader_vybrid/sram_ds5_a5.scf clean
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
mingw32-make TOOL=ds5 CONFIG=release LINKER_FILE=$(MQX_ROOTDIR)/../mqx/examples/bootloader_vybrid/sram_ds5_a5.scf clean
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)

if not "%NOPAUSE%" == "nopause" (pause)
