@echo OFF
set NOPAUSE=%1
SET CWD=%CD%
cd ../../../../../mqx/build/make/bsp_frdmk64f
mingw32-make TOOL=gcc_arm CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../mqx/build/make/psp_frdmk64f
mingw32-make TOOL=gcc_arm CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../mfs/build/make/mfs_frdmk64f
mingw32-make TOOL=gcc_arm CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../rtcs/build/make/rtcs_frdmk64f
mingw32-make TOOL=gcc_arm CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../shell/build/make/shell_frdmk64f
mingw32-make TOOL=gcc_arm CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../usb_v2/usb_core/host/build/make/usbh_mqx_frdmk64f
mingw32-make TOOL=gcc_arm CONFIG=debug build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
mingw32-make TOOL=gcc_arm CONFIG=debug LOAD=intflash build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
SET CWD=%CD%
cd ../../../../../mqx/build/make/bsp_frdmk64f
mingw32-make TOOL=gcc_arm CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../mqx/build/make/psp_frdmk64f
mingw32-make TOOL=gcc_arm CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../mfs/build/make/mfs_frdmk64f
mingw32-make TOOL=gcc_arm CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../rtcs/build/make/rtcs_frdmk64f
mingw32-make TOOL=gcc_arm CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../shell/build/make/shell_frdmk64f
mingw32-make TOOL=gcc_arm CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
SET CWD=%CD%
cd ../../../../../usb_v2/usb_core/host/build/make/usbh_mqx_frdmk64f
mingw32-make TOOL=gcc_arm CONFIG=release build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)
cd %CWD%
mingw32-make TOOL=gcc_arm CONFIG=release LOAD=intflash build
if errorlevel 1 if NOT "%NOPAUSE%" == "nopause" (pause)

if not "%NOPAUSE%" == "nopause" (pause)
