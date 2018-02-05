@echo off

rem convert path to backslash format
Set CURRENTDIR=%CD%
set USBROOTDIR=%~f1
set USBROOTDIR=%USBROOTDIR:/=\%
set OUTPUTDIR=%~f2
set OUTPUTDIR=%OUTPUTDIR:/=\%
set TOOL=%3
set OS=%4

rem copy common files
IF NOT EXIST %OUTPUTDIR% mkdir %OUTPUTDIR%
cd /d %USBROOTDIR%
copy usb_core\include\usb.h %OUTPUTDIR%\ /Y
copy usb_core\include\compiler.h %OUTPUTDIR%\ /Y
copy usb_core\include\types.h %OUTPUTDIR%\ /Y
copy usb_core\include\usb_desc.h %OUTPUTDIR%\ /Y
copy usb_core\include\usb_error.h %OUTPUTDIR%\ /Y
copy usb_core\include\usb_misc.h %OUTPUTDIR%\ /Y
copy usb_core\include\usb_opt.h %OUTPUTDIR%\ /Y
copy usb_core\include\usb_types.h %OUTPUTDIR%\ /Y
copy adapter\sources\adapter.h %OUTPUTDIR%\ /Y
copy adapter\sources\adapter_types.h %OUTPUTDIR%\ /Y
copy usb_core\device\include\twrk24f120m\usb_device_config.h %OUTPUTDIR%\ /Y
copy usb_core\device\include\usb_device_stack_interface.h %OUTPUTDIR%\ /Y
copy usb_core\device\sources\classes\include\usb_class_audio.h %OUTPUTDIR%\ /Y
copy usb_core\device\sources\classes\include\usb_class_cdc.h %OUTPUTDIR%\ /Y
copy usb_core\device\sources\classes\include\usb_class.h %OUTPUTDIR%\ /Y
copy usb_core\device\sources\classes\include\usb_class_composite.h %OUTPUTDIR%\ /Y
copy usb_core\device\sources\classes\include\usb_class_hid.h %OUTPUTDIR%\ /Y
copy usb_core\device\sources\classes\include\usb_class_msc.h %OUTPUTDIR%\ /Y
copy usb_core\device\sources\classes\include\usb_class_phdc.h %OUTPUTDIR%\ /Y
copy usb_core\device\sources\classes\include\config\usb_audio_config.h %OUTPUTDIR%\ /Y
copy usb_core\device\sources\classes\include\config\usb_cdc_config.h %OUTPUTDIR%\ /Y
copy usb_core\device\sources\classes\include\config\usb_composite_config.h %OUTPUTDIR%\ /Y
copy usb_core\device\sources\classes\include\config\usb_hid_config.h %OUTPUTDIR%\ /Y
copy usb_core\device\sources\classes\include\config\usb_msc_config.h %OUTPUTDIR%\ /Y
copy usb_core\device\sources\classes\include\config\usb_phdc_config.h %OUTPUTDIR%\ /Y

goto tool_%TOOL%

rem cw10 files
:tool_cw10
goto os_%OS%

rem iar files
:tool_iar
goto os_%OS%

rem cw10gcc files
:tool_cw10gcc
goto os_%OS%

rem uv4 files
:tool_uv4
goto os_%OS%

rem gcc_arm files
:tool_gcc_arm
goto os_%OS%

rem kds files
:tool_kds
goto os_%OS%

rem mqx file
:os_mqx
copy adapter\sources\mqx\adapter_mqx.h %OUTPUTDIR%\ /Y 
copy adapter\sources\mqx\adapter_cfg.h %OUTPUTDIR%\ /Y
goto copy_end

rem bm file
:os_bm
copy adapter\sources\bm\adapter_bm.h %OUTPUTDIR%\ /Y 
copy adapter\sources\bm\adapter_cfg.h %OUTPUTDIR%\ /Y
goto copy_end

rem sdk file
:os_sdk
copy adapter\sources\sdk\adapter_sdk.h %OUTPUTDIR%\ /Y 
copy adapter\sources\sdk\adapter_cfg.h %OUTPUTDIR%\ /Y
goto copy_end

:copy_end
cd /d %CURRENTDIR%
