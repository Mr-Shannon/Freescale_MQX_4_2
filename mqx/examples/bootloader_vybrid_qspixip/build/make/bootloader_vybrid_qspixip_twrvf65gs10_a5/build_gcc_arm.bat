@echo OFF
set NOPAUSE=%1
SET CWD=%CD%
cd ../../../../../build/make/bsp_twrvf65gs10_a5
mingw32-make TOOL=gcc_arm CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../build/make/psp_twrvf65gs10_a5
mingw32-make TOOL=gcc_arm CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../mfs/build/make/mfs_twrvf65gs10_a5
mingw32-make TOOL=gcc_arm CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
mingw32-make TOOL=gcc_arm CONFIG=debug LINKER_FILE=$(MQX_ROOTDIR)/../mqx/examples/bootloader_vybrid_qspixip/sram_gcc_arm_a5.ld build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
SET CWD=%CD%
cd ../../../../../build/make/bsp_twrvf65gs10_a5
mingw32-make TOOL=gcc_arm CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../build/make/psp_twrvf65gs10_a5
mingw32-make TOOL=gcc_arm CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../../mfs/build/make/mfs_twrvf65gs10_a5
mingw32-make TOOL=gcc_arm CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
mingw32-make TOOL=gcc_arm CONFIG=release LINKER_FILE=$(MQX_ROOTDIR)/../mqx/examples/bootloader_vybrid_qspixip/sram_gcc_arm_a5.ld build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)

if not "%NOPAUSE%" == "nopause" (pause)
