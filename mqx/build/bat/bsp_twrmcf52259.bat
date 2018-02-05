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
copy "%ROOTDIR%\mqx\source\io\adc\mcf522xx\adc_mcf522xx.h" "%OUTPUTDIR%\adc_mcf522xx.h" /Y
copy "%ROOTDIR%\mqx\source\io\adc\adc.h" "%OUTPUTDIR%\adc.h" /Y
copy "%ROOTDIR%\mqx\source\io\adc\adc_conf.h" "%OUTPUTDIR%\adc_conf.h" /Y
copy "%ROOTDIR%\config\twrmcf52259\user_config.h" "%OUTPUTDIR%\..\user_config.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\mcf5xxx_fec\mcf5225_fec.h" "%OUTPUTDIR%\mcf5225_fec.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\mcf5xxx_fec\mcf5xxx_fec_rev.h" "%OUTPUTDIR%\mcf5xxx_fec_rev.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\phy\phy_ksz8041.h" "%OUTPUTDIR%\phy_ksz8041.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet_rev.h" "%OUTPUTDIR%\enet_rev.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\freescale\flash_mcf5225.h" "%OUTPUTDIR%\flash_mcf5225.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\freescale\flash_mcf52xx.h" "%OUTPUTDIR%\flash_mcf52xx.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\flashx.h" "%OUTPUTDIR%\flashx.h" /Y
copy "%ROOTDIR%\mqx\source\io\can\flexcan\flexcan.h" "%OUTPUTDIR%\flexcan.h" /Y
copy "%ROOTDIR%\mqx\source\io\gpio\mcf5225\io_gpio_mcf5225.h" "%OUTPUTDIR%\io_gpio_mcf5225.h" /Y
copy "%ROOTDIR%\mqx\source\io\gpio\io_gpio.h" "%OUTPUTDIR%\io_gpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\i2c_mcf52xx.h" "%OUTPUTDIR%\i2c_mcf52xx.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\i2c.h" "%OUTPUTDIR%\i2c.h" /Y
copy "%ROOTDIR%\config\common\small_ram_config.h" "%OUTPUTDIR%\..\small_ram_config.h" /Y
copy "%ROOTDIR%\config\common\smallest_config.h" "%OUTPUTDIR%\..\smallest_config.h" /Y
copy "%ROOTDIR%\config\common\maximum_config.h" "%OUTPUTDIR%\..\maximum_config.h" /Y
copy "%ROOTDIR%\config\common\verif_enabled_config.h" "%OUTPUTDIR%\..\verif_enabled_config.h" /Y
copy "%ROOTDIR%\mqx\source\include\mqx.h" "%OUTPUTDIR%\mqx.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf52259\bsp.h" "%OUTPUTDIR%\bsp.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf52259\bsp_rev.h" "%OUTPUTDIR%\bsp_rev.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf52259\twrmcf52259.h" "%OUTPUTDIR%\twrmcf52259.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\ethernet.h" "%OUTPUTDIR%\ethernet.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet.h" "%OUTPUTDIR%\enet.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet_wifi.h" "%OUTPUTDIR%\enet_wifi.h" /Y
copy "%ROOTDIR%\mqx\source\io\int_ctrl\int_ctrl_mcf5225.h" "%OUTPUTDIR%\int_ctrl_mcf5225.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_mem\io_mem.h" "%OUTPUTDIR%\io_mem.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_null\io_null.h" "%OUTPUTDIR%\io_null.h" /Y
copy "%ROOTDIR%\mqx\source\io\pipe\io_pipe.h" "%OUTPUTDIR%\io_pipe.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwgpio\lwgpio_mcf5225.h" "%OUTPUTDIR%\lwgpio_mcf5225.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwgpio\lwgpio.h" "%OUTPUTDIR%\lwgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\io_pcb.h" "%OUTPUTDIR%\io_pcb.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\mqxa\pcb_mqxa.h" "%OUTPUTDIR%\pcb_mqxa.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\mqxa\pcbmqxav.h" "%OUTPUTDIR%\pcbmqxav.h" /Y
copy "%ROOTDIR%\mqx\source\io\pccard\pccardflexbus.h" "%OUTPUTDIR%\pccardflexbus.h" /Y
copy "%ROOTDIR%\mqx\source\io\pccard\apccard.h" "%OUTPUTDIR%\apccard.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\pcflash.h" "%OUTPUTDIR%\pcflash.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\apcflshpr.h" "%OUTPUTDIR%\apcflshpr.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\ata.h" "%OUTPUTDIR%\ata.h" /Y
copy "%ROOTDIR%\mqx\source\io\rtc\rtc_mcf52xx.h" "%OUTPUTDIR%\rtc_mcf52xx.h" /Y
copy "%ROOTDIR%\mqx\source\io\rtc\rtc.h" "%OUTPUTDIR%\rtc.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard_spi\sdcard_spi.h" "%OUTPUTDIR%\sdcard_spi.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard.h" "%OUTPUTDIR%\sdcard.h" /Y
copy "%ROOTDIR%\mqx\source\io\serial\serl_mcf52xx.h" "%OUTPUTDIR%\serl_mcf52xx.h" /Y
copy "%ROOTDIR%\mqx\source\io\serial\serial.h" "%OUTPUTDIR%\serial.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi_legacy\spi_mcf5xxx_qspi.h" "%OUTPUTDIR%\spi_mcf5xxx_qspi.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi_legacy\spi.h" "%OUTPUTDIR%\spi.h" /Y
copy "%ROOTDIR%\mqx\source\io\tchres\tchres.h" "%OUTPUTDIR%\tchres.h" /Y
copy "%ROOTDIR%\mqx\source\io\tfs\tfs.h" "%OUTPUTDIR%\tfs.h" /Y
copy "%ROOTDIR%\mqx\source\io\timer\timer_pit.h" "%OUTPUTDIR%\timer_pit.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_host_ehci.h" "%OUTPUTDIR%\if_host_ehci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_host_khci.h" "%OUTPUTDIR%\if_host_khci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_dev_ehci.h" "%OUTPUTDIR%\if_dev_ehci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_dev_khci.h" "%OUTPUTDIR%\if_dev_khci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\usb_bsp.h" "%OUTPUTDIR%\usb_bsp.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf52259\cw\extmram.lcf" "%OUTPUTDIR%\extmram.lcf" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf52259\cw\intflash.lcf" "%OUTPUTDIR%\intflash.lcf" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf52259\cw\intram.lcf" "%OUTPUTDIR%\intram.lcf" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf52259\cw\dbg\twrmcf52259.cfg" "%OUTPUTDIR%\..\..\dbg\twrmcf52259.cfg" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf52259\cw\dbg\twrmcf52259.mem" "%OUTPUTDIR%\..\..\dbg\twrmcf52259.mem" /Y
goto end_script



:end_script

