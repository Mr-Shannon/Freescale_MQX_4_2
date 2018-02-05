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
copy "%ROOTDIR%\mqx\source\io\adc\mcf544xx\adc_mcf544xx.h" "%OUTPUTDIR%\adc_mcf544xx.h" /Y
copy "%ROOTDIR%\mqx\source\io\adc\adc.h" "%OUTPUTDIR%\adc.h" /Y
copy "%ROOTDIR%\mqx\source\io\adc\adc_conf.h" "%OUTPUTDIR%\adc_conf.h" /Y
copy "%ROOTDIR%\config\twrmcf54418\user_config.h" "%OUTPUTDIR%\..\user_config.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_mcf5441.h" "%OUTPUTDIR%\macnet_mcf5441.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\phy\phy_dp83xxx.h" "%OUTPUTDIR%\phy_dp83xxx.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\phy\phy_ksz8041.h" "%OUTPUTDIR%\phy_ksz8041.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_rev.h" "%OUTPUTDIR%\macnet_rev.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_1588.h" "%OUTPUTDIR%\macnet_1588.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet_rev.h" "%OUTPUTDIR%\enet_rev.h" /Y
copy "%ROOTDIR%\mqx\source\io\esdhc\esdhc.h" "%OUTPUTDIR%\esdhc.h" /Y
copy "%ROOTDIR%\mqx\source\io\can\flexcan\flexcan.h" "%OUTPUTDIR%\flexcan.h" /Y
copy "%ROOTDIR%\mqx\source\io\gpio\mcf5441\io_gpio_mcf5441.h" "%OUTPUTDIR%\io_gpio_mcf5441.h" /Y
copy "%ROOTDIR%\mqx\source\io\gpio\io_gpio.h" "%OUTPUTDIR%\io_gpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\i2c_mcf54xx.h" "%OUTPUTDIR%\i2c_mcf54xx.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\i2c.h" "%OUTPUTDIR%\i2c.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2s\i2s_audio.h" "%OUTPUTDIR%\i2s_audio.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2s\i2s_mcf54xx.h" "%OUTPUTDIR%\i2s_mcf54xx.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2s\i2s.h" "%OUTPUTDIR%\i2s.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf54418\bsp_cm.h" "%OUTPUTDIR%\bsp_cm.h" /Y
copy "%ROOTDIR%\config\common\small_ram_config.h" "%OUTPUTDIR%\..\small_ram_config.h" /Y
copy "%ROOTDIR%\config\common\smallest_config.h" "%OUTPUTDIR%\..\smallest_config.h" /Y
copy "%ROOTDIR%\config\common\maximum_config.h" "%OUTPUTDIR%\..\maximum_config.h" /Y
copy "%ROOTDIR%\config\common\verif_enabled_config.h" "%OUTPUTDIR%\..\verif_enabled_config.h" /Y
copy "%ROOTDIR%\mqx\source\include\mqx.h" "%OUTPUTDIR%\mqx.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf54418\bsp.h" "%OUTPUTDIR%\bsp.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf54418\bsp_rev.h" "%OUTPUTDIR%\bsp_rev.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf54418\twrmcf54418.h" "%OUTPUTDIR%\twrmcf54418.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\ethernet.h" "%OUTPUTDIR%\ethernet.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet.h" "%OUTPUTDIR%\enet.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet_wifi.h" "%OUTPUTDIR%\enet_wifi.h" /Y
copy "%ROOTDIR%\mqx\source\io\int_ctrl\int_ctrl_mcf5441.h" "%OUTPUTDIR%\int_ctrl_mcf5441.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_mem\io_mem.h" "%OUTPUTDIR%\io_mem.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_null\io_null.h" "%OUTPUTDIR%\io_null.h" /Y
copy "%ROOTDIR%\mqx\source\io\pipe\io_pipe.h" "%OUTPUTDIR%\io_pipe.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwgpio\lwgpio_mcf5441.h" "%OUTPUTDIR%\lwgpio_mcf5441.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwgpio\lwgpio.h" "%OUTPUTDIR%\lwgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\nandflash\nfc\nfc.h" "%OUTPUTDIR%\nfc.h" /Y
copy "%ROOTDIR%\mqx\source\io\nandflash\nfc\nfc_dma.h" "%OUTPUTDIR%\nfc_dma.h" /Y
copy "%ROOTDIR%\mqx\source\io\nandflash\nandflash.h" "%OUTPUTDIR%\nandflash.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\io_pcb.h" "%OUTPUTDIR%\io_pcb.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\mqxa\pcb_mqxa.h" "%OUTPUTDIR%\pcb_mqxa.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\mqxa\pcbmqxav.h" "%OUTPUTDIR%\pcbmqxav.h" /Y
copy "%ROOTDIR%\mqx\source\io\pccard\pccardflexbus.h" "%OUTPUTDIR%\pccardflexbus.h" /Y
copy "%ROOTDIR%\mqx\source\io\pccard\apccard.h" "%OUTPUTDIR%\apccard.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\pcflash.h" "%OUTPUTDIR%\pcflash.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\apcflshpr.h" "%OUTPUTDIR%\apcflshpr.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\ata.h" "%OUTPUTDIR%\ata.h" /Y
copy "%ROOTDIR%\mqx\source\io\rtc\irtc_mcf5441x.h" "%OUTPUTDIR%\irtc_mcf5441x.h" /Y
copy "%ROOTDIR%\mqx\source\io\rtc\irtc_mcf5xxx.h" "%OUTPUTDIR%\irtc_mcf5xxx.h" /Y
copy "%ROOTDIR%\mqx\source\io\rtc\rtc.h" "%OUTPUTDIR%\rtc.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard_spi\sdcard_spi.h" "%OUTPUTDIR%\sdcard_spi.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard_esdhc\sdcard_esdhc.h" "%OUTPUTDIR%\sdcard_esdhc.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard.h" "%OUTPUTDIR%\sdcard.h" /Y
copy "%ROOTDIR%\mqx\source\io\serial\serl_mcf54xx.h" "%OUTPUTDIR%\serl_mcf54xx.h" /Y
copy "%ROOTDIR%\mqx\source\io\serial\serial.h" "%OUTPUTDIR%\serial.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi.h" "%OUTPUTDIR%\spi_dspi.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi_common.h" "%OUTPUTDIR%\spi_dspi_common.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi.h" "%OUTPUTDIR%\spi.h" /Y
copy "%ROOTDIR%\mqx\source\io\tfs\tfs.h" "%OUTPUTDIR%\tfs.h" /Y
copy "%ROOTDIR%\mqx\source\io\timer\timer_pit.h" "%OUTPUTDIR%\timer_pit.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_host_ehci.h" "%OUTPUTDIR%\if_host_ehci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_host_khci.h" "%OUTPUTDIR%\if_host_khci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_dev_ehci.h" "%OUTPUTDIR%\if_dev_ehci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_dev_khci.h" "%OUTPUTDIR%\if_dev_khci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\usb_bsp.h" "%OUTPUTDIR%\usb_bsp.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf54418\cw\extflash.lcf" "%OUTPUTDIR%\extflash.lcf" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf54418\cw\extram.lcf" "%OUTPUTDIR%\extram.lcf" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf54418\cw\dbg\m5441xevb_ddr2.cfg" "%OUTPUTDIR%\..\..\dbg\m5441xevb_ddr2.cfg" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf54418\cw\dbg\twrmcf54418.cfg" "%OUTPUTDIR%\..\..\dbg\twrmcf54418.cfg" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrmcf54418\cw\dbg\twrmcf54418.mem" "%OUTPUTDIR%\..\..\dbg\twrmcf54418.mem" /Y
goto end_script



:end_script

