@echo OFF
SET CWD=%CD%

setlocal
cd %CWD%\..\..\..\usb_core\device\build\make\usbd_mqx_svf522revb_a5
cmd /c build_gcc_arm nopause
cd %CWD%\..\..\..\usb_core\host\build\make\usbh_mqx_svf522revb_a5
cmd /c build_gcc_arm nopause

if not "%1" == "nopause" (pause)
