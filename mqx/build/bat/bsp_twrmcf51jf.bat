@echo off

rem convert path to backslash format
set ROOTDIR=%1
set ROOTDIR=%ROOTDIR:/=\%
set ROOTDIR=%ROOTDIR:"=%
set OUTPUTDIR=%2
set OUTPUTDIR=%OUTPUTDIR:/=\%
set OUTPUTDIR=%OUTPUTDIR:"=%
set TOOL=%3

rem process one of label bellow
goto label_%TOOL%

:label_cw10
IF NOT EXIST "%OUTPUTDIR%" mkdir "%OUTPUTDIR%"
IF NOT EXIST "%OUTPUTDIR%\." mkdir "%OUTPUTDIR%\."
IF NOT EXIST "%OUTPUTDIR%\.." mkdir "%OUTPUTDIR%\.."
IF NOT EXIST "%OUTPUTDIR%\../../dbg" mkdir "%OUTPUTDIR%\../../dbg"
IF NOT EXIST "%OUTPUTDIR%\Generated_Code" mkdir "%OUTPUTDIR%\Generated_Code"
IF NOT EXIST "%OUTPUTDIR%\Sources" mkdir "%OUTPUTDIR%\Sources"
IF NOT EXIST "%OUTPUTDIR%\tss" mkdir "%OUTPUTDIR%\tss"
copy "%ROOTDIR%\mqx\source\io\adc\kadc\adc_mcf51jf.h" "%OUTPUTDIR%\adc_mcf51jf.h" /Y
copy "%ROOTDIR%\mqx\source\io\adc\kadc\adc_kadc.h" "%OUTPUTDIR%\adc_kadc.h" /Y
copy "%ROOTDIR%\mqx\source\io\adc\adc.h" "%OUTPUTDIR%\adc.h" /Y
copy "%ROOTDIR%\mqx\source\io\adc\adc_conf.h" "%OUTPUTDIR%\adc_conf.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\cm_cfplus.h" "%OUTPUTDIR%\cm_cfplus.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\cm.h" "%OUTPUTDIR%\cm.h" /Y
copy "%ROOTDIR%\config\twrmcf51jf\user_config.h" "%OUTPUTDIR%\..\user_config.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\freescale\flash_mcf51jf.h" "%OUTPUTDIR%\flash_mcf51jf.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\freescale\flash_ftfl.h" "%OUTPUTDIR%\flash_ftfl.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\flashx.h" "%OUTPUTDIR%\flashx.h" /Y
copy "%ROOTDIR%\mqx\source\io\gpio\mcf51jf\io_gpio_mcf51jf.h" "%OUTPUTDIR%\io_gpio_mcf51jf.h" /Y
copy "%ROOTDIR%\mqx\source\io\gpio\io_gpio.h" "%OUTPUTDIR%\io_gpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\btnled.h" "%OUTPUTDIR%\btnled.h" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\derivative.h" "%OUTPUTDIR%\derivative.h" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\hmi_client.h" "%OUTPUTDIR%\hmi_client.h" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\hmi_lwgpio_provider.h" "%OUTPUTDIR%\hmi_lwgpio_provider.h" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\hmi_tss_provider.h" "%OUTPUTDIR%\hmi_tss_provider.h" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\hmi_uids.h" "%OUTPUTDIR%\hmi_uids.h" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\hmi_provider.h" "%OUTPUTDIR%\hmi_provider.h" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\TSS\shared\TSS_API.h" "%OUTPUTDIR%\tss\TSS_API.h" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\TSS\shared\TSS_DataTypes.h" "%OUTPUTDIR%\tss\TSS_DataTypes.h" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\TSS\shared\TSS_GPIO.h" "%OUTPUTDIR%\tss\TSS_GPIO.h" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\TSS\shared\TSS_Sensor.h" "%OUTPUTDIR%\tss\TSS_Sensor.h" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\TSS\shared\TSS_SensorGPIO.h" "%OUTPUTDIR%\tss\TSS_SensorGPIO.h" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\TSS\shared\TSS_SensorGPIO_def.h" "%OUTPUTDIR%\tss\TSS_SensorGPIO_def.h" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\TSS\shared\TSS_SensorTSI.h" "%OUTPUTDIR%\tss\TSS_SensorTSI.h" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\TSS\shared\TSS_SensorTSI_def.h" "%OUTPUTDIR%\tss\TSS_SensorTSI_def.h" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\TSS\shared\TSS_SensorTSIL.h" "%OUTPUTDIR%\tss\TSS_SensorTSIL.h" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\TSS\shared\TSS_SensorTSIL_def.h" "%OUTPUTDIR%\tss\TSS_SensorTSIL_def.h" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\TSS\shared\TSS_StatusCodes.h" "%OUTPUTDIR%\tss\TSS_StatusCodes.h" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\TSS\shared\TSS_SystemSetupVal.h" "%OUTPUTDIR%\tss\TSS_SystemSetupVal.h" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\TSS\shared\TSS_Timer.h" "%OUTPUTDIR%\tss\TSS_Timer.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer_lpt.h" "%OUTPUTDIR%\hwtimer_lpt.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer.h" "%OUTPUTDIR%\hwtimer.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\i2c_ki2c.h" "%OUTPUTDIR%\i2c_ki2c.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\i2c.h" "%OUTPUTDIR%\i2c.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf51jf\bsp_cm.h" "%OUTPUTDIR%\bsp_cm.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf51jf\TSS_SystemSetup.h" "%OUTPUTDIR%\TSS_SystemSetup.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf51jf\init_lpm.h" "%OUTPUTDIR%\init_lpm.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf51jf\init_usb.c" "%OUTPUTDIR%\init_usb.c" /Y
copy "%ROOTDIR%\config\common\small_ram_config.h" "%OUTPUTDIR%\..\small_ram_config.h" /Y
copy "%ROOTDIR%\config\common\smallest_config.h" "%OUTPUTDIR%\..\smallest_config.h" /Y
copy "%ROOTDIR%\config\common\maximum_config.h" "%OUTPUTDIR%\..\maximum_config.h" /Y
copy "%ROOTDIR%\config\common\verif_enabled_config.h" "%OUTPUTDIR%\..\verif_enabled_config.h" /Y
copy "%ROOTDIR%\mqx\source\include\mqx.h" "%OUTPUTDIR%\mqx.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf51jf\bsp.h" "%OUTPUTDIR%\bsp.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf51jf\bsp_rev.h" "%OUTPUTDIR%\bsp_rev.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf51jf\PE_LDD.h" "%OUTPUTDIR%\Generated_Code\PE_LDD.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf51jf\PE_Types.h" "%OUTPUTDIR%\Generated_Code\PE_Types.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf51jf\twrmcf51jf.h" "%OUTPUTDIR%\twrmcf51jf.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\ethernet.h" "%OUTPUTDIR%\ethernet.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet.h" "%OUTPUTDIR%\enet.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet_wifi.h" "%OUTPUTDIR%\enet_wifi.h" /Y
copy "%ROOTDIR%\mqx\source\io\int_ctrl\int_ctrl_mcfplus.h" "%OUTPUTDIR%\int_ctrl_mcfplus.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_mem\io_mem.h" "%OUTPUTDIR%\io_mem.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_null\io_null.h" "%OUTPUTDIR%\io_null.h" /Y
copy "%ROOTDIR%\mqx\source\io\pipe\io_pipe.h" "%OUTPUTDIR%\io_pipe.h" /Y
copy "%ROOTDIR%\mqx\source\io\lpm\lpm_cfplus.h" "%OUTPUTDIR%\lpm_cfplus.h" /Y
copy "%ROOTDIR%\mqx\source\io\lpm\lpm.h" "%OUTPUTDIR%\lpm.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwgpio\lwgpio_mcf51jf.h" "%OUTPUTDIR%\lwgpio_mcf51jf.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwgpio\lwgpio.h" "%OUTPUTDIR%\lwgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\io_pcb.h" "%OUTPUTDIR%\io_pcb.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\mqxa\pcb_mqxa.h" "%OUTPUTDIR%\pcb_mqxa.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\mqxa\pcbmqxav.h" "%OUTPUTDIR%\pcbmqxav.h" /Y
copy "%ROOTDIR%\mqx\source\io\pccard\pccardflexbus.h" "%OUTPUTDIR%\pccardflexbus.h" /Y
copy "%ROOTDIR%\mqx\source\io\pccard\apccard.h" "%OUTPUTDIR%\apccard.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\pcflash.h" "%OUTPUTDIR%\pcflash.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\apcflshpr.h" "%OUTPUTDIR%\apcflshpr.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\ata.h" "%OUTPUTDIR%\ata.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard_spi\sdcard_spi.h" "%OUTPUTDIR%\sdcard_spi.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard.h" "%OUTPUTDIR%\sdcard.h" /Y
copy "%ROOTDIR%\mqx\source\io\serial\serl_kuart.h" "%OUTPUTDIR%\serl_kuart.h" /Y
copy "%ROOTDIR%\mqx\source\io\serial\serial.h" "%OUTPUTDIR%\serial.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi_legacy\spi_spi16.h" "%OUTPUTDIR%\spi_spi16.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi_legacy\spi.h" "%OUTPUTDIR%\spi.h" /Y
copy "%ROOTDIR%\mqx\source\io\tfs\tfs.h" "%OUTPUTDIR%\tfs.h" /Y
copy "%ROOTDIR%\mqx\source\io\timer\timer_mtim16.h" "%OUTPUTDIR%\timer_mtim16.h" /Y
copy "%ROOTDIR%\mqx\source\io\timer\timer_pscaler.h" "%OUTPUTDIR%\timer_pscaler.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_host_ehci.h" "%OUTPUTDIR%\if_host_ehci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_host_khci.h" "%OUTPUTDIR%\if_host_khci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_dev_ehci.h" "%OUTPUTDIR%\if_dev_ehci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_dev_khci.h" "%OUTPUTDIR%\if_dev_khci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\usb_bsp.h" "%OUTPUTDIR%\usb_bsp.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb_dcd\usb_dcd_kn.h" "%OUTPUTDIR%\usb_dcd_kn.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb_dcd\usb_dcd_kn_prv.h" "%OUTPUTDIR%\usb_dcd_kn_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb_dcd\usb_dcd.h" "%OUTPUTDIR%\usb_dcd.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf51jf\cw\intflash.lcf" "%OUTPUTDIR%\intflash.lcf" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf51jf\cw\dbg\twrmcf51jf.cfg" "%OUTPUTDIR%\..\..\dbg\twrmcf51jf.cfg" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf51jf\cw\dbg\twrmcf51jf.mem" "%OUTPUTDIR%\..\..\dbg\twrmcf51jf.mem" /Y
copy "%ROOTDIR%\mqx\build\cw10\bsp_twrmcf51jf\Generated_Code\Readme.txt" "%OUTPUTDIR%\Generated_Code\Readme.txt" /Y
copy "%ROOTDIR%\mqx\build\cw10\bsp_twrmcf51jf\Generated_Code" "%OUTPUTDIR%\Generated_Code" /Y
copy "%ROOTDIR%\mqx\build\cw10\bsp_twrmcf51jf\Sources\Readme.txt" "%OUTPUTDIR%\Sources\Readme.txt" /Y
copy "%ROOTDIR%\mqx\build\cw10\bsp_twrmcf51jf\Sources" "%OUTPUTDIR%\Sources" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\TSS\lib_cw\TSS_CFV1.a" "%OUTPUTDIR%\tss.a" /Y
goto end_script



:end_script

