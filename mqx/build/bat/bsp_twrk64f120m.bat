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

:label_cw10gcc
IF NOT EXIST "%OUTPUTDIR%" mkdir "%OUTPUTDIR%"
IF NOT EXIST "%OUTPUTDIR%\." mkdir "%OUTPUTDIR%\."
IF NOT EXIST "%OUTPUTDIR%\.." mkdir "%OUTPUTDIR%\.."
IF NOT EXIST "%OUTPUTDIR%\Generated_Code" mkdir "%OUTPUTDIR%\Generated_Code"
IF NOT EXIST "%OUTPUTDIR%\Generated_Code/" mkdir "%OUTPUTDIR%\Generated_Code/"
IF NOT EXIST "%OUTPUTDIR%\Sources/" mkdir "%OUTPUTDIR%\Sources/"
copy "%ROOTDIR%\mqx\source\io\adc\kadc\adc_mk64.h" "%OUTPUTDIR%\adc_mk64.h" /Y
copy "%ROOTDIR%\mqx\source\io\adc\kadc\adc_kadc.h" "%OUTPUTDIR%\adc_kadc.h" /Y
copy "%ROOTDIR%\mqx\source\io\adc\adc.h" "%OUTPUTDIR%\adc.h" /Y
copy "%ROOTDIR%\mqx\source\io\adc\adc_conf.h" "%OUTPUTDIR%\adc_conf.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\cm_kinetis.h" "%OUTPUTDIR%\cm_kinetis.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\cm.h" "%OUTPUTDIR%\cm.h" /Y
copy "%ROOTDIR%\config\twrk64f120m\user_config.h" "%OUTPUTDIR%\..\user_config.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\dma.h" "%OUTPUTDIR%\dma.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\edma.h" "%OUTPUTDIR%\edma.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\edma_prv.h" "%OUTPUTDIR%\edma_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_mk64.h" "%OUTPUTDIR%\macnet_mk64.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\phy\phy_ksz8041.h" "%OUTPUTDIR%\phy_ksz8041.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_rev.h" "%OUTPUTDIR%\macnet_rev.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_1588.h" "%OUTPUTDIR%\macnet_1588.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet_rev.h" "%OUTPUTDIR%\enet_rev.h" /Y
copy "%ROOTDIR%\mqx\source\io\esdhc\esdhc.h" "%OUTPUTDIR%\esdhc.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\freescale\flash_mk64.h" "%OUTPUTDIR%\flash_mk64.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\freescale\flash_ftfe.h" "%OUTPUTDIR%\flash_ftfe.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\flashx.h" "%OUTPUTDIR%\flashx.h" /Y
copy "%ROOTDIR%\mqx\source\io\can\flexcan\kflexcan.h" "%OUTPUTDIR%\kflexcan.h" /Y
copy "%ROOTDIR%\mqx\source\io\gpio\kgpio\io_gpio_kgpio.h" "%OUTPUTDIR%\io_gpio_kgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\gpio\io_gpio.h" "%OUTPUTDIR%\io_gpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer_lpt.h" "%OUTPUTDIR%\hwtimer_lpt.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer_systick.h" "%OUTPUTDIR%\hwtimer_systick.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer_pit.h" "%OUTPUTDIR%\hwtimer_pit.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer.h" "%OUTPUTDIR%\hwtimer.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\i2c_ki2c.h" "%OUTPUTDIR%\i2c_ki2c.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\i2c.h" "%OUTPUTDIR%\i2c.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\bsp_cm.h" "%OUTPUTDIR%\bsp_cm.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\init_lpm.h" "%OUTPUTDIR%\init_lpm.h" /Y
copy "%ROOTDIR%\config\common\small_ram_config.h" "%OUTPUTDIR%\..\small_ram_config.h" /Y
copy "%ROOTDIR%\config\common\smallest_config.h" "%OUTPUTDIR%\..\smallest_config.h" /Y
copy "%ROOTDIR%\config\common\maximum_config.h" "%OUTPUTDIR%\..\maximum_config.h" /Y
copy "%ROOTDIR%\config\common\verif_enabled_config.h" "%OUTPUTDIR%\..\verif_enabled_config.h" /Y
copy "%ROOTDIR%\mqx\source\include\mqx.h" "%OUTPUTDIR%\mqx.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\bsp.h" "%OUTPUTDIR%\bsp.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\bsp_rev.h" "%OUTPUTDIR%\bsp_rev.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\PE_LDD.h" "%OUTPUTDIR%\Generated_Code\PE_LDD.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\PE_Types.h" "%OUTPUTDIR%\Generated_Code\PE_Types.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\twrk64f120m.h" "%OUTPUTDIR%\twrk64f120m.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\ethernet.h" "%OUTPUTDIR%\ethernet.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet.h" "%OUTPUTDIR%\enet.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet_wifi.h" "%OUTPUTDIR%\enet_wifi.h" /Y
copy "%ROOTDIR%\mqx\source\io\debug\iodebug.h" "%OUTPUTDIR%\iodebug.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_mem\io_mem.h" "%OUTPUTDIR%\io_mem.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_null\io_null.h" "%OUTPUTDIR%\io_null.h" /Y
copy "%ROOTDIR%\mqx\source\io\pipe\io_pipe.h" "%OUTPUTDIR%\io_pipe.h" /Y
copy "%ROOTDIR%\mqx\source\io\lpm\lpm_kinetis.h" "%OUTPUTDIR%\lpm_kinetis.h" /Y
copy "%ROOTDIR%\mqx\source\io\lpm\lpm.h" "%OUTPUTDIR%\lpm.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwadc\lwadc_kadc.h" "%OUTPUTDIR%\lwadc_kadc.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwadc\lwadc.h" "%OUTPUTDIR%\lwadc.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwgpio\lwgpio_kgpio.h" "%OUTPUTDIR%\lwgpio_kgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwgpio\lwgpio.h" "%OUTPUTDIR%\lwgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\io_pcb.h" "%OUTPUTDIR%\io_pcb.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\mqxa\pcb_mqxa.h" "%OUTPUTDIR%\pcb_mqxa.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\mqxa\pcbmqxav.h" "%OUTPUTDIR%\pcbmqxav.h" /Y
copy "%ROOTDIR%\mqx\source\io\pccard\pccardflexbus.h" "%OUTPUTDIR%\pccardflexbus.h" /Y
copy "%ROOTDIR%\mqx\source\io\pccard\apccard.h" "%OUTPUTDIR%\apccard.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\pcflash.h" "%OUTPUTDIR%\pcflash.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\apcflshpr.h" "%OUTPUTDIR%\apcflshpr.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\ata.h" "%OUTPUTDIR%\ata.h" /Y
copy "%ROOTDIR%\mqx\source\io\rtc\krtc.h" "%OUTPUTDIR%\krtc.h" /Y
copy "%ROOTDIR%\mqx\source\io\rtc\rtc.h" "%OUTPUTDIR%\rtc.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai_ksai.h" "%OUTPUTDIR%\sai_ksai.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai.h" "%OUTPUTDIR%\sai.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai_audio.h" "%OUTPUTDIR%\sai_audio.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard_esdhc\sdcard_esdhc.h" "%OUTPUTDIR%\sdcard_esdhc.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard_spi\sdcard_spi.h" "%OUTPUTDIR%\sdcard_spi.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard.h" "%OUTPUTDIR%\sdcard.h" /Y
copy "%ROOTDIR%\mqx\source\io\serial\serl_kuart.h" "%OUTPUTDIR%\serl_kuart.h" /Y
copy "%ROOTDIR%\mqx\source\io\serial\serial.h" "%OUTPUTDIR%\serial.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi_dma.h" "%OUTPUTDIR%\spi_dspi_dma.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi_common.h" "%OUTPUTDIR%\spi_dspi_common.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi.h" "%OUTPUTDIR%\spi.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi.h" "%OUTPUTDIR%\spi_dspi.h" /Y
copy "%ROOTDIR%\mqx\source\io\tchres\tchres.h" "%OUTPUTDIR%\tchres.h" /Y
copy "%ROOTDIR%\mqx\source\io\tfs\tfs.h" "%OUTPUTDIR%\tfs.h" /Y
copy "%ROOTDIR%\mqx\source\io\timer\timer_qpit.h" "%OUTPUTDIR%\timer_qpit.h" /Y
copy "%ROOTDIR%\mqx\source\io\timer\qpit.h" "%OUTPUTDIR%\qpit.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_host_ehci.h" "%OUTPUTDIR%\if_host_ehci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_host_khci.h" "%OUTPUTDIR%\if_host_khci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_dev_ehci.h" "%OUTPUTDIR%\if_dev_ehci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_dev_khci.h" "%OUTPUTDIR%\if_dev_khci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\usb_bsp.h" "%OUTPUTDIR%\usb_bsp.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb_dcd\usb_dcd_kn.h" "%OUTPUTDIR%\usb_dcd_kn.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb_dcd\usb_dcd_kn_prv.h" "%OUTPUTDIR%\usb_dcd_kn_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb_dcd\usb_dcd.h" "%OUTPUTDIR%\usb_dcd.h" /Y
xcopy /s /e /y /h "%ROOTDIR%\mqx\build\cw10gcc\bsp_twrk64f120m\Generated_Code\*" "%OUTPUTDIR%\Generated_Code\*"
xcopy /s /e /y /h "%ROOTDIR%\mqx\build\cw10gcc\bsp_twrk64f120m\Sources\*" "%OUTPUTDIR%\Sources\*"
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\gcc_cw\intflash.ld" "%OUTPUTDIR%\intflash.ld" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\TSS\lib_cw_gcc\libTSS_KXX_M4.a" "%OUTPUTDIR%\tss.a" /Y
goto end_script


:label_gcc_arm
IF NOT EXIST "%OUTPUTDIR%" mkdir "%OUTPUTDIR%"
IF NOT EXIST "%OUTPUTDIR%\." mkdir "%OUTPUTDIR%\."
IF NOT EXIST "%OUTPUTDIR%\.." mkdir "%OUTPUTDIR%\.."
IF NOT EXIST "%OUTPUTDIR%\Generated_Code" mkdir "%OUTPUTDIR%\Generated_Code"
copy "%ROOTDIR%\mqx\source\io\adc\kadc\adc_mk64.h" "%OUTPUTDIR%\adc_mk64.h" /Y
copy "%ROOTDIR%\mqx\source\io\adc\kadc\adc_kadc.h" "%OUTPUTDIR%\adc_kadc.h" /Y
copy "%ROOTDIR%\mqx\source\io\adc\adc.h" "%OUTPUTDIR%\adc.h" /Y
copy "%ROOTDIR%\mqx\source\io\adc\adc_conf.h" "%OUTPUTDIR%\adc_conf.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\cm_kinetis.h" "%OUTPUTDIR%\cm_kinetis.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\cm.h" "%OUTPUTDIR%\cm.h" /Y
copy "%ROOTDIR%\config\twrk64f120m\user_config.h" "%OUTPUTDIR%\..\user_config.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\dma.h" "%OUTPUTDIR%\dma.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\edma.h" "%OUTPUTDIR%\edma.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\edma_prv.h" "%OUTPUTDIR%\edma_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_mk64.h" "%OUTPUTDIR%\macnet_mk64.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\phy\phy_ksz8041.h" "%OUTPUTDIR%\phy_ksz8041.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_rev.h" "%OUTPUTDIR%\macnet_rev.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_1588.h" "%OUTPUTDIR%\macnet_1588.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet_rev.h" "%OUTPUTDIR%\enet_rev.h" /Y
copy "%ROOTDIR%\mqx\source\io\esdhc\esdhc.h" "%OUTPUTDIR%\esdhc.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\freescale\flash_mk64.h" "%OUTPUTDIR%\flash_mk64.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\freescale\flash_ftfe.h" "%OUTPUTDIR%\flash_ftfe.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\flashx.h" "%OUTPUTDIR%\flashx.h" /Y
copy "%ROOTDIR%\mqx\source\io\can\flexcan\kflexcan.h" "%OUTPUTDIR%\kflexcan.h" /Y
copy "%ROOTDIR%\mqx\source\io\gpio\kgpio\io_gpio_kgpio.h" "%OUTPUTDIR%\io_gpio_kgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\gpio\io_gpio.h" "%OUTPUTDIR%\io_gpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer_lpt.h" "%OUTPUTDIR%\hwtimer_lpt.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer_systick.h" "%OUTPUTDIR%\hwtimer_systick.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer_pit.h" "%OUTPUTDIR%\hwtimer_pit.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer.h" "%OUTPUTDIR%\hwtimer.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\i2c_ki2c.h" "%OUTPUTDIR%\i2c_ki2c.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\i2c.h" "%OUTPUTDIR%\i2c.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\bsp_cm.h" "%OUTPUTDIR%\bsp_cm.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\init_lpm.h" "%OUTPUTDIR%\init_lpm.h" /Y
copy "%ROOTDIR%\config\common\small_ram_config.h" "%OUTPUTDIR%\..\small_ram_config.h" /Y
copy "%ROOTDIR%\config\common\smallest_config.h" "%OUTPUTDIR%\..\smallest_config.h" /Y
copy "%ROOTDIR%\config\common\maximum_config.h" "%OUTPUTDIR%\..\maximum_config.h" /Y
copy "%ROOTDIR%\config\common\verif_enabled_config.h" "%OUTPUTDIR%\..\verif_enabled_config.h" /Y
copy "%ROOTDIR%\mqx\source\include\mqx.h" "%OUTPUTDIR%\mqx.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\bsp.h" "%OUTPUTDIR%\bsp.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\bsp_rev.h" "%OUTPUTDIR%\bsp_rev.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\PE_LDD.h" "%OUTPUTDIR%\Generated_Code\PE_LDD.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\PE_Types.h" "%OUTPUTDIR%\Generated_Code\PE_Types.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\twrk64f120m.h" "%OUTPUTDIR%\twrk64f120m.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\ethernet.h" "%OUTPUTDIR%\ethernet.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet.h" "%OUTPUTDIR%\enet.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet_wifi.h" "%OUTPUTDIR%\enet_wifi.h" /Y
copy "%ROOTDIR%\mqx\source\io\debug\iodebug.h" "%OUTPUTDIR%\iodebug.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_mem\io_mem.h" "%OUTPUTDIR%\io_mem.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_null\io_null.h" "%OUTPUTDIR%\io_null.h" /Y
copy "%ROOTDIR%\mqx\source\io\pipe\io_pipe.h" "%OUTPUTDIR%\io_pipe.h" /Y
copy "%ROOTDIR%\mqx\source\io\lpm\lpm_kinetis.h" "%OUTPUTDIR%\lpm_kinetis.h" /Y
copy "%ROOTDIR%\mqx\source\io\lpm\lpm.h" "%OUTPUTDIR%\lpm.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwadc\lwadc_kadc.h" "%OUTPUTDIR%\lwadc_kadc.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwadc\lwadc.h" "%OUTPUTDIR%\lwadc.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwgpio\lwgpio_kgpio.h" "%OUTPUTDIR%\lwgpio_kgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwgpio\lwgpio.h" "%OUTPUTDIR%\lwgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\io_pcb.h" "%OUTPUTDIR%\io_pcb.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\mqxa\pcb_mqxa.h" "%OUTPUTDIR%\pcb_mqxa.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\mqxa\pcbmqxav.h" "%OUTPUTDIR%\pcbmqxav.h" /Y
copy "%ROOTDIR%\mqx\source\io\pccard\pccardflexbus.h" "%OUTPUTDIR%\pccardflexbus.h" /Y
copy "%ROOTDIR%\mqx\source\io\pccard\apccard.h" "%OUTPUTDIR%\apccard.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\pcflash.h" "%OUTPUTDIR%\pcflash.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\apcflshpr.h" "%OUTPUTDIR%\apcflshpr.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\ata.h" "%OUTPUTDIR%\ata.h" /Y
copy "%ROOTDIR%\mqx\source\io\rtc\krtc.h" "%OUTPUTDIR%\krtc.h" /Y
copy "%ROOTDIR%\mqx\source\io\rtc\rtc.h" "%OUTPUTDIR%\rtc.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai_ksai.h" "%OUTPUTDIR%\sai_ksai.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai.h" "%OUTPUTDIR%\sai.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai_audio.h" "%OUTPUTDIR%\sai_audio.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard_esdhc\sdcard_esdhc.h" "%OUTPUTDIR%\sdcard_esdhc.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard_spi\sdcard_spi.h" "%OUTPUTDIR%\sdcard_spi.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard.h" "%OUTPUTDIR%\sdcard.h" /Y
copy "%ROOTDIR%\mqx\source\io\serial\serl_kuart.h" "%OUTPUTDIR%\serl_kuart.h" /Y
copy "%ROOTDIR%\mqx\source\io\serial\serial.h" "%OUTPUTDIR%\serial.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi_dma.h" "%OUTPUTDIR%\spi_dspi_dma.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi_common.h" "%OUTPUTDIR%\spi_dspi_common.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi.h" "%OUTPUTDIR%\spi.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi.h" "%OUTPUTDIR%\spi_dspi.h" /Y
copy "%ROOTDIR%\mqx\source\io\tchres\tchres.h" "%OUTPUTDIR%\tchres.h" /Y
copy "%ROOTDIR%\mqx\source\io\tfs\tfs.h" "%OUTPUTDIR%\tfs.h" /Y
copy "%ROOTDIR%\mqx\source\io\timer\timer_qpit.h" "%OUTPUTDIR%\timer_qpit.h" /Y
copy "%ROOTDIR%\mqx\source\io\timer\qpit.h" "%OUTPUTDIR%\qpit.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_host_ehci.h" "%OUTPUTDIR%\if_host_ehci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_host_khci.h" "%OUTPUTDIR%\if_host_khci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_dev_ehci.h" "%OUTPUTDIR%\if_dev_ehci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_dev_khci.h" "%OUTPUTDIR%\if_dev_khci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\usb_bsp.h" "%OUTPUTDIR%\usb_bsp.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb_dcd\usb_dcd_kn.h" "%OUTPUTDIR%\usb_dcd_kn.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb_dcd\usb_dcd_kn_prv.h" "%OUTPUTDIR%\usb_dcd_kn_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb_dcd\usb_dcd.h" "%OUTPUTDIR%\usb_dcd.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\gcc_arm\intflash.ld" "%OUTPUTDIR%\intflash.ld" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\TSS\lib_cw_gcc\libTSS_KXX_M4.a" "%OUTPUTDIR%\tss.a" /Y
goto end_script


:label_kds
IF NOT EXIST "%OUTPUTDIR%" mkdir "%OUTPUTDIR%"
IF NOT EXIST "%OUTPUTDIR%\." mkdir "%OUTPUTDIR%\."
IF NOT EXIST "%OUTPUTDIR%\.." mkdir "%OUTPUTDIR%\.."
IF NOT EXIST "%OUTPUTDIR%\Generated_Code" mkdir "%OUTPUTDIR%\Generated_Code"
copy "%ROOTDIR%\mqx\source\io\adc\kadc\adc_mk64.h" "%OUTPUTDIR%\adc_mk64.h" /Y
copy "%ROOTDIR%\mqx\source\io\adc\kadc\adc_kadc.h" "%OUTPUTDIR%\adc_kadc.h" /Y
copy "%ROOTDIR%\mqx\source\io\adc\adc.h" "%OUTPUTDIR%\adc.h" /Y
copy "%ROOTDIR%\mqx\source\io\adc\adc_conf.h" "%OUTPUTDIR%\adc_conf.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\cm_kinetis.h" "%OUTPUTDIR%\cm_kinetis.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\cm.h" "%OUTPUTDIR%\cm.h" /Y
copy "%ROOTDIR%\config\twrk64f120m\user_config.h" "%OUTPUTDIR%\..\user_config.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\dma.h" "%OUTPUTDIR%\dma.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\edma.h" "%OUTPUTDIR%\edma.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\edma_prv.h" "%OUTPUTDIR%\edma_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_mk64.h" "%OUTPUTDIR%\macnet_mk64.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\phy\phy_ksz8041.h" "%OUTPUTDIR%\phy_ksz8041.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_rev.h" "%OUTPUTDIR%\macnet_rev.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_1588.h" "%OUTPUTDIR%\macnet_1588.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet_rev.h" "%OUTPUTDIR%\enet_rev.h" /Y
copy "%ROOTDIR%\mqx\source\io\esdhc\esdhc.h" "%OUTPUTDIR%\esdhc.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\freescale\flash_mk64.h" "%OUTPUTDIR%\flash_mk64.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\freescale\flash_ftfe.h" "%OUTPUTDIR%\flash_ftfe.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\flashx.h" "%OUTPUTDIR%\flashx.h" /Y
copy "%ROOTDIR%\mqx\source\io\can\flexcan\kflexcan.h" "%OUTPUTDIR%\kflexcan.h" /Y
copy "%ROOTDIR%\mqx\source\io\gpio\kgpio\io_gpio_kgpio.h" "%OUTPUTDIR%\io_gpio_kgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\gpio\io_gpio.h" "%OUTPUTDIR%\io_gpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer_lpt.h" "%OUTPUTDIR%\hwtimer_lpt.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer_systick.h" "%OUTPUTDIR%\hwtimer_systick.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer_pit.h" "%OUTPUTDIR%\hwtimer_pit.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer.h" "%OUTPUTDIR%\hwtimer.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\i2c_ki2c.h" "%OUTPUTDIR%\i2c_ki2c.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\i2c.h" "%OUTPUTDIR%\i2c.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\bsp_cm.h" "%OUTPUTDIR%\bsp_cm.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\init_lpm.h" "%OUTPUTDIR%\init_lpm.h" /Y
copy "%ROOTDIR%\config\common\small_ram_config.h" "%OUTPUTDIR%\..\small_ram_config.h" /Y
copy "%ROOTDIR%\config\common\smallest_config.h" "%OUTPUTDIR%\..\smallest_config.h" /Y
copy "%ROOTDIR%\config\common\maximum_config.h" "%OUTPUTDIR%\..\maximum_config.h" /Y
copy "%ROOTDIR%\config\common\verif_enabled_config.h" "%OUTPUTDIR%\..\verif_enabled_config.h" /Y
copy "%ROOTDIR%\mqx\source\include\mqx.h" "%OUTPUTDIR%\mqx.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\bsp.h" "%OUTPUTDIR%\bsp.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\bsp_rev.h" "%OUTPUTDIR%\bsp_rev.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\PE_LDD.h" "%OUTPUTDIR%\Generated_Code\PE_LDD.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\PE_Types.h" "%OUTPUTDIR%\Generated_Code\PE_Types.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\twrk64f120m.h" "%OUTPUTDIR%\twrk64f120m.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\ethernet.h" "%OUTPUTDIR%\ethernet.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet.h" "%OUTPUTDIR%\enet.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet_wifi.h" "%OUTPUTDIR%\enet_wifi.h" /Y
copy "%ROOTDIR%\mqx\source\io\debug\iodebug.h" "%OUTPUTDIR%\iodebug.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_mem\io_mem.h" "%OUTPUTDIR%\io_mem.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_null\io_null.h" "%OUTPUTDIR%\io_null.h" /Y
copy "%ROOTDIR%\mqx\source\io\pipe\io_pipe.h" "%OUTPUTDIR%\io_pipe.h" /Y
copy "%ROOTDIR%\mqx\source\io\lpm\lpm_kinetis.h" "%OUTPUTDIR%\lpm_kinetis.h" /Y
copy "%ROOTDIR%\mqx\source\io\lpm\lpm.h" "%OUTPUTDIR%\lpm.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwadc\lwadc_kadc.h" "%OUTPUTDIR%\lwadc_kadc.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwadc\lwadc.h" "%OUTPUTDIR%\lwadc.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwgpio\lwgpio_kgpio.h" "%OUTPUTDIR%\lwgpio_kgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwgpio\lwgpio.h" "%OUTPUTDIR%\lwgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\io_pcb.h" "%OUTPUTDIR%\io_pcb.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\mqxa\pcb_mqxa.h" "%OUTPUTDIR%\pcb_mqxa.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\mqxa\pcbmqxav.h" "%OUTPUTDIR%\pcbmqxav.h" /Y
copy "%ROOTDIR%\mqx\source\io\pccard\pccardflexbus.h" "%OUTPUTDIR%\pccardflexbus.h" /Y
copy "%ROOTDIR%\mqx\source\io\pccard\apccard.h" "%OUTPUTDIR%\apccard.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\pcflash.h" "%OUTPUTDIR%\pcflash.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\apcflshpr.h" "%OUTPUTDIR%\apcflshpr.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\ata.h" "%OUTPUTDIR%\ata.h" /Y
copy "%ROOTDIR%\mqx\source\io\rtc\krtc.h" "%OUTPUTDIR%\krtc.h" /Y
copy "%ROOTDIR%\mqx\source\io\rtc\rtc.h" "%OUTPUTDIR%\rtc.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai_ksai.h" "%OUTPUTDIR%\sai_ksai.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai.h" "%OUTPUTDIR%\sai.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai_audio.h" "%OUTPUTDIR%\sai_audio.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard_esdhc\sdcard_esdhc.h" "%OUTPUTDIR%\sdcard_esdhc.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard_spi\sdcard_spi.h" "%OUTPUTDIR%\sdcard_spi.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard.h" "%OUTPUTDIR%\sdcard.h" /Y
copy "%ROOTDIR%\mqx\source\io\serial\serl_kuart.h" "%OUTPUTDIR%\serl_kuart.h" /Y
copy "%ROOTDIR%\mqx\source\io\serial\serial.h" "%OUTPUTDIR%\serial.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi_dma.h" "%OUTPUTDIR%\spi_dspi_dma.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi_common.h" "%OUTPUTDIR%\spi_dspi_common.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi.h" "%OUTPUTDIR%\spi.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi.h" "%OUTPUTDIR%\spi_dspi.h" /Y
copy "%ROOTDIR%\mqx\source\io\tchres\tchres.h" "%OUTPUTDIR%\tchres.h" /Y
copy "%ROOTDIR%\mqx\source\io\tfs\tfs.h" "%OUTPUTDIR%\tfs.h" /Y
copy "%ROOTDIR%\mqx\source\io\timer\timer_qpit.h" "%OUTPUTDIR%\timer_qpit.h" /Y
copy "%ROOTDIR%\mqx\source\io\timer\qpit.h" "%OUTPUTDIR%\qpit.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_host_ehci.h" "%OUTPUTDIR%\if_host_ehci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_host_khci.h" "%OUTPUTDIR%\if_host_khci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_dev_ehci.h" "%OUTPUTDIR%\if_dev_ehci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_dev_khci.h" "%OUTPUTDIR%\if_dev_khci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\usb_bsp.h" "%OUTPUTDIR%\usb_bsp.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb_dcd\usb_dcd_kn.h" "%OUTPUTDIR%\usb_dcd_kn.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb_dcd\usb_dcd_kn_prv.h" "%OUTPUTDIR%\usb_dcd_kn_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb_dcd\usb_dcd.h" "%OUTPUTDIR%\usb_dcd.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\gcc_arm\intflash.ld" "%OUTPUTDIR%\intflash.ld" /Y
goto end_script


:label_uv4
IF NOT EXIST "%OUTPUTDIR%" mkdir "%OUTPUTDIR%"
IF NOT EXIST "%OUTPUTDIR%\." mkdir "%OUTPUTDIR%\."
IF NOT EXIST "%OUTPUTDIR%\.." mkdir "%OUTPUTDIR%\.."
IF NOT EXIST "%OUTPUTDIR%\Generated_Code" mkdir "%OUTPUTDIR%\Generated_Code"
copy "%ROOTDIR%\mqx\source\io\adc\kadc\adc_mk64.h" "%OUTPUTDIR%\adc_mk64.h" /Y
copy "%ROOTDIR%\mqx\source\io\adc\kadc\adc_kadc.h" "%OUTPUTDIR%\adc_kadc.h" /Y
copy "%ROOTDIR%\mqx\source\io\adc\adc.h" "%OUTPUTDIR%\adc.h" /Y
copy "%ROOTDIR%\mqx\source\io\adc\adc_conf.h" "%OUTPUTDIR%\adc_conf.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\cm_kinetis.h" "%OUTPUTDIR%\cm_kinetis.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\cm.h" "%OUTPUTDIR%\cm.h" /Y
copy "%ROOTDIR%\config\twrk64f120m\user_config.h" "%OUTPUTDIR%\..\user_config.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\dma.h" "%OUTPUTDIR%\dma.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\edma.h" "%OUTPUTDIR%\edma.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\edma_prv.h" "%OUTPUTDIR%\edma_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_mk64.h" "%OUTPUTDIR%\macnet_mk64.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\phy\phy_ksz8041.h" "%OUTPUTDIR%\phy_ksz8041.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_rev.h" "%OUTPUTDIR%\macnet_rev.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_1588.h" "%OUTPUTDIR%\macnet_1588.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet_rev.h" "%OUTPUTDIR%\enet_rev.h" /Y
copy "%ROOTDIR%\mqx\source\io\esdhc\esdhc.h" "%OUTPUTDIR%\esdhc.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\freescale\flash_mk64.h" "%OUTPUTDIR%\flash_mk64.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\freescale\flash_ftfe.h" "%OUTPUTDIR%\flash_ftfe.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\flashx.h" "%OUTPUTDIR%\flashx.h" /Y
copy "%ROOTDIR%\mqx\source\io\can\flexcan\kflexcan.h" "%OUTPUTDIR%\kflexcan.h" /Y
copy "%ROOTDIR%\mqx\source\io\gpio\kgpio\io_gpio_kgpio.h" "%OUTPUTDIR%\io_gpio_kgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\gpio\io_gpio.h" "%OUTPUTDIR%\io_gpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer_lpt.h" "%OUTPUTDIR%\hwtimer_lpt.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer_systick.h" "%OUTPUTDIR%\hwtimer_systick.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer_pit.h" "%OUTPUTDIR%\hwtimer_pit.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer.h" "%OUTPUTDIR%\hwtimer.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\i2c_ki2c.h" "%OUTPUTDIR%\i2c_ki2c.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\i2c.h" "%OUTPUTDIR%\i2c.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\bsp_cm.h" "%OUTPUTDIR%\bsp_cm.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\init_lpm.h" "%OUTPUTDIR%\init_lpm.h" /Y
copy "%ROOTDIR%\config\common\small_ram_config.h" "%OUTPUTDIR%\..\small_ram_config.h" /Y
copy "%ROOTDIR%\config\common\smallest_config.h" "%OUTPUTDIR%\..\smallest_config.h" /Y
copy "%ROOTDIR%\config\common\maximum_config.h" "%OUTPUTDIR%\..\maximum_config.h" /Y
copy "%ROOTDIR%\config\common\verif_enabled_config.h" "%OUTPUTDIR%\..\verif_enabled_config.h" /Y
copy "%ROOTDIR%\mqx\source\include\mqx.h" "%OUTPUTDIR%\mqx.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\bsp.h" "%OUTPUTDIR%\bsp.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\bsp_rev.h" "%OUTPUTDIR%\bsp_rev.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\PE_LDD.h" "%OUTPUTDIR%\Generated_Code\PE_LDD.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\PE_Types.h" "%OUTPUTDIR%\Generated_Code\PE_Types.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\twrk64f120m.h" "%OUTPUTDIR%\twrk64f120m.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\ethernet.h" "%OUTPUTDIR%\ethernet.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet.h" "%OUTPUTDIR%\enet.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet_wifi.h" "%OUTPUTDIR%\enet_wifi.h" /Y
copy "%ROOTDIR%\mqx\source\io\debug\iodebug.h" "%OUTPUTDIR%\iodebug.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_mem\io_mem.h" "%OUTPUTDIR%\io_mem.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_null\io_null.h" "%OUTPUTDIR%\io_null.h" /Y
copy "%ROOTDIR%\mqx\source\io\pipe\io_pipe.h" "%OUTPUTDIR%\io_pipe.h" /Y
copy "%ROOTDIR%\mqx\source\io\lpm\lpm_kinetis.h" "%OUTPUTDIR%\lpm_kinetis.h" /Y
copy "%ROOTDIR%\mqx\source\io\lpm\lpm.h" "%OUTPUTDIR%\lpm.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwadc\lwadc_kadc.h" "%OUTPUTDIR%\lwadc_kadc.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwadc\lwadc.h" "%OUTPUTDIR%\lwadc.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwgpio\lwgpio_kgpio.h" "%OUTPUTDIR%\lwgpio_kgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwgpio\lwgpio.h" "%OUTPUTDIR%\lwgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\io_pcb.h" "%OUTPUTDIR%\io_pcb.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\mqxa\pcb_mqxa.h" "%OUTPUTDIR%\pcb_mqxa.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\mqxa\pcbmqxav.h" "%OUTPUTDIR%\pcbmqxav.h" /Y
copy "%ROOTDIR%\mqx\source\io\pccard\pccardflexbus.h" "%OUTPUTDIR%\pccardflexbus.h" /Y
copy "%ROOTDIR%\mqx\source\io\pccard\apccard.h" "%OUTPUTDIR%\apccard.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\pcflash.h" "%OUTPUTDIR%\pcflash.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\apcflshpr.h" "%OUTPUTDIR%\apcflshpr.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\ata.h" "%OUTPUTDIR%\ata.h" /Y
copy "%ROOTDIR%\mqx\source\io\rtc\krtc.h" "%OUTPUTDIR%\krtc.h" /Y
copy "%ROOTDIR%\mqx\source\io\rtc\rtc.h" "%OUTPUTDIR%\rtc.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai_ksai.h" "%OUTPUTDIR%\sai_ksai.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai.h" "%OUTPUTDIR%\sai.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai_audio.h" "%OUTPUTDIR%\sai_audio.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard_esdhc\sdcard_esdhc.h" "%OUTPUTDIR%\sdcard_esdhc.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard_spi\sdcard_spi.h" "%OUTPUTDIR%\sdcard_spi.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard.h" "%OUTPUTDIR%\sdcard.h" /Y
copy "%ROOTDIR%\mqx\source\io\serial\serl_kuart.h" "%OUTPUTDIR%\serl_kuart.h" /Y
copy "%ROOTDIR%\mqx\source\io\serial\serial.h" "%OUTPUTDIR%\serial.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi_dma.h" "%OUTPUTDIR%\spi_dspi_dma.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi_common.h" "%OUTPUTDIR%\spi_dspi_common.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi.h" "%OUTPUTDIR%\spi.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi.h" "%OUTPUTDIR%\spi_dspi.h" /Y
copy "%ROOTDIR%\mqx\source\io\tchres\tchres.h" "%OUTPUTDIR%\tchres.h" /Y
copy "%ROOTDIR%\mqx\source\io\tfs\tfs.h" "%OUTPUTDIR%\tfs.h" /Y
copy "%ROOTDIR%\mqx\source\io\timer\timer_qpit.h" "%OUTPUTDIR%\timer_qpit.h" /Y
copy "%ROOTDIR%\mqx\source\io\timer\qpit.h" "%OUTPUTDIR%\qpit.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_host_ehci.h" "%OUTPUTDIR%\if_host_ehci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_host_khci.h" "%OUTPUTDIR%\if_host_khci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_dev_ehci.h" "%OUTPUTDIR%\if_dev_ehci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_dev_khci.h" "%OUTPUTDIR%\if_dev_khci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\usb_bsp.h" "%OUTPUTDIR%\usb_bsp.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb_dcd\usb_dcd_kn.h" "%OUTPUTDIR%\usb_dcd_kn.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb_dcd\usb_dcd_kn_prv.h" "%OUTPUTDIR%\usb_dcd_kn_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb_dcd\usb_dcd.h" "%OUTPUTDIR%\usb_dcd.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\uv4\intflash.scf" "%OUTPUTDIR%\intflash.scf" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\TSS\lib_uv4\TSS_KXX_M4.lib" "%OUTPUTDIR%\tss.lib" /Y
goto end_script


:label_iar
IF NOT EXIST "%OUTPUTDIR%" mkdir "%OUTPUTDIR%"
IF NOT EXIST "%OUTPUTDIR%\." mkdir "%OUTPUTDIR%\."
IF NOT EXIST "%OUTPUTDIR%\.." mkdir "%OUTPUTDIR%\.."
IF NOT EXIST "%OUTPUTDIR%\Generated_Code" mkdir "%OUTPUTDIR%\Generated_Code"
copy "%ROOTDIR%\mqx\source\io\adc\kadc\adc_mk64.h" "%OUTPUTDIR%\adc_mk64.h" /Y
copy "%ROOTDIR%\mqx\source\io\adc\kadc\adc_kadc.h" "%OUTPUTDIR%\adc_kadc.h" /Y
copy "%ROOTDIR%\mqx\source\io\adc\adc.h" "%OUTPUTDIR%\adc.h" /Y
copy "%ROOTDIR%\mqx\source\io\adc\adc_conf.h" "%OUTPUTDIR%\adc_conf.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\cm_kinetis.h" "%OUTPUTDIR%\cm_kinetis.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\cm.h" "%OUTPUTDIR%\cm.h" /Y
copy "%ROOTDIR%\config\twrk64f120m\user_config.h" "%OUTPUTDIR%\..\user_config.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\dma.h" "%OUTPUTDIR%\dma.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\edma.h" "%OUTPUTDIR%\edma.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\edma_prv.h" "%OUTPUTDIR%\edma_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_mk64.h" "%OUTPUTDIR%\macnet_mk64.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\phy\phy_ksz8041.h" "%OUTPUTDIR%\phy_ksz8041.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_rev.h" "%OUTPUTDIR%\macnet_rev.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_1588.h" "%OUTPUTDIR%\macnet_1588.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet_rev.h" "%OUTPUTDIR%\enet_rev.h" /Y
copy "%ROOTDIR%\mqx\source\io\esdhc\esdhc.h" "%OUTPUTDIR%\esdhc.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\freescale\flash_mk64.h" "%OUTPUTDIR%\flash_mk64.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\freescale\flash_ftfe.h" "%OUTPUTDIR%\flash_ftfe.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\flashx.h" "%OUTPUTDIR%\flashx.h" /Y
copy "%ROOTDIR%\mqx\source\io\can\flexcan\kflexcan.h" "%OUTPUTDIR%\kflexcan.h" /Y
copy "%ROOTDIR%\mqx\source\io\gpio\kgpio\io_gpio_kgpio.h" "%OUTPUTDIR%\io_gpio_kgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\gpio\io_gpio.h" "%OUTPUTDIR%\io_gpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer_lpt.h" "%OUTPUTDIR%\hwtimer_lpt.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer_systick.h" "%OUTPUTDIR%\hwtimer_systick.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer_pit.h" "%OUTPUTDIR%\hwtimer_pit.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer.h" "%OUTPUTDIR%\hwtimer.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\i2c_ki2c.h" "%OUTPUTDIR%\i2c_ki2c.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\i2c.h" "%OUTPUTDIR%\i2c.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\bsp_cm.h" "%OUTPUTDIR%\bsp_cm.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\init_lpm.h" "%OUTPUTDIR%\init_lpm.h" /Y
copy "%ROOTDIR%\config\common\small_ram_config.h" "%OUTPUTDIR%\..\small_ram_config.h" /Y
copy "%ROOTDIR%\config\common\smallest_config.h" "%OUTPUTDIR%\..\smallest_config.h" /Y
copy "%ROOTDIR%\config\common\maximum_config.h" "%OUTPUTDIR%\..\maximum_config.h" /Y
copy "%ROOTDIR%\config\common\verif_enabled_config.h" "%OUTPUTDIR%\..\verif_enabled_config.h" /Y
copy "%ROOTDIR%\mqx\source\include\mqx.h" "%OUTPUTDIR%\mqx.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\bsp.h" "%OUTPUTDIR%\bsp.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\bsp_rev.h" "%OUTPUTDIR%\bsp_rev.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\PE_LDD.h" "%OUTPUTDIR%\Generated_Code\PE_LDD.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\PE_Types.h" "%OUTPUTDIR%\Generated_Code\PE_Types.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\twrk64f120m.h" "%OUTPUTDIR%\twrk64f120m.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\ethernet.h" "%OUTPUTDIR%\ethernet.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet.h" "%OUTPUTDIR%\enet.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet_wifi.h" "%OUTPUTDIR%\enet_wifi.h" /Y
copy "%ROOTDIR%\mqx\source\io\debug\iodebug.h" "%OUTPUTDIR%\iodebug.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_mem\io_mem.h" "%OUTPUTDIR%\io_mem.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_null\io_null.h" "%OUTPUTDIR%\io_null.h" /Y
copy "%ROOTDIR%\mqx\source\io\pipe\io_pipe.h" "%OUTPUTDIR%\io_pipe.h" /Y
copy "%ROOTDIR%\mqx\source\io\lpm\lpm_kinetis.h" "%OUTPUTDIR%\lpm_kinetis.h" /Y
copy "%ROOTDIR%\mqx\source\io\lpm\lpm.h" "%OUTPUTDIR%\lpm.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwadc\lwadc_kadc.h" "%OUTPUTDIR%\lwadc_kadc.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwadc\lwadc.h" "%OUTPUTDIR%\lwadc.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwgpio\lwgpio_kgpio.h" "%OUTPUTDIR%\lwgpio_kgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwgpio\lwgpio.h" "%OUTPUTDIR%\lwgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\io_pcb.h" "%OUTPUTDIR%\io_pcb.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\mqxa\pcb_mqxa.h" "%OUTPUTDIR%\pcb_mqxa.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\mqxa\pcbmqxav.h" "%OUTPUTDIR%\pcbmqxav.h" /Y
copy "%ROOTDIR%\mqx\source\io\pccard\pccardflexbus.h" "%OUTPUTDIR%\pccardflexbus.h" /Y
copy "%ROOTDIR%\mqx\source\io\pccard\apccard.h" "%OUTPUTDIR%\apccard.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\pcflash.h" "%OUTPUTDIR%\pcflash.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\apcflshpr.h" "%OUTPUTDIR%\apcflshpr.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcflash\ata.h" "%OUTPUTDIR%\ata.h" /Y
copy "%ROOTDIR%\mqx\source\io\rtc\krtc.h" "%OUTPUTDIR%\krtc.h" /Y
copy "%ROOTDIR%\mqx\source\io\rtc\rtc.h" "%OUTPUTDIR%\rtc.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai_ksai.h" "%OUTPUTDIR%\sai_ksai.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai.h" "%OUTPUTDIR%\sai.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai_audio.h" "%OUTPUTDIR%\sai_audio.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard_esdhc\sdcard_esdhc.h" "%OUTPUTDIR%\sdcard_esdhc.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard_spi\sdcard_spi.h" "%OUTPUTDIR%\sdcard_spi.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard.h" "%OUTPUTDIR%\sdcard.h" /Y
copy "%ROOTDIR%\mqx\source\io\serial\serl_kuart.h" "%OUTPUTDIR%\serl_kuart.h" /Y
copy "%ROOTDIR%\mqx\source\io\serial\serial.h" "%OUTPUTDIR%\serial.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi_dma.h" "%OUTPUTDIR%\spi_dspi_dma.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi_common.h" "%OUTPUTDIR%\spi_dspi_common.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi.h" "%OUTPUTDIR%\spi.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi.h" "%OUTPUTDIR%\spi_dspi.h" /Y
copy "%ROOTDIR%\mqx\source\io\tchres\tchres.h" "%OUTPUTDIR%\tchres.h" /Y
copy "%ROOTDIR%\mqx\source\io\tfs\tfs.h" "%OUTPUTDIR%\tfs.h" /Y
copy "%ROOTDIR%\mqx\source\io\timer\timer_qpit.h" "%OUTPUTDIR%\timer_qpit.h" /Y
copy "%ROOTDIR%\mqx\source\io\timer\qpit.h" "%OUTPUTDIR%\qpit.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_host_ehci.h" "%OUTPUTDIR%\if_host_ehci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_host_khci.h" "%OUTPUTDIR%\if_host_khci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_dev_ehci.h" "%OUTPUTDIR%\if_dev_ehci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_dev_khci.h" "%OUTPUTDIR%\if_dev_khci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\usb_bsp.h" "%OUTPUTDIR%\usb_bsp.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb_dcd\usb_dcd_kn.h" "%OUTPUTDIR%\usb_dcd_kn.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb_dcd\usb_dcd_kn_prv.h" "%OUTPUTDIR%\usb_dcd_kn_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb_dcd\usb_dcd.h" "%OUTPUTDIR%\usb_dcd.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\iar\intflash.icf" "%OUTPUTDIR%\intflash.icf" /Y
copy "%ROOTDIR%\mqx\source\bsp\twrk64f120m\iar\ram.icf" "%OUTPUTDIR%\ram.icf" /Y
copy "%ROOTDIR%\mqx\source\io\hmi\TSS\lib_iar\TSS_KXX_M4.a" "%OUTPUTDIR%\tss.a" /Y
goto end_script



:end_script

