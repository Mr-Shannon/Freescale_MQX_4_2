@echo OFF
SET CWD=%CD%

setlocal
cd %CWD%\..\..\..\usb_core\device\build\make\usbd_mqx_svf522revb_m4
cmd /c clean_gcc_arm nopause
cd %CWD%\..\..\..\usb_core\host\build\make\usbh_mqx_svf522revb_m4
cmd /c clean_gcc_arm nopause

if not "%1" == "nopause" (pause)
