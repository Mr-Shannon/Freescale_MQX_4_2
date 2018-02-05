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

:label_gcc_arm
IF NOT EXIST "%OUTPUTDIR%" mkdir "%OUTPUTDIR%"
IF NOT EXIST "%OUTPUTDIR%\." mkdir "%OUTPUTDIR%\."
IF NOT EXIST "%OUTPUTDIR%\.." mkdir "%OUTPUTDIR%\.."
copy "%ROOTDIR%\mqx\source\io\asrc\asrc_vybrid.h" "%OUTPUTDIR%\asrc_vybrid.h" /Y
copy "%ROOTDIR%\mqx\source\io\asrc\asrc_vybrid_prv.h" "%OUTPUTDIR%\asrc_vybrid_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\asrc\vybrid_asrc_regs.h" "%OUTPUTDIR%\vybrid_asrc_regs.h" /Y
copy "%ROOTDIR%\mqx\source\io\asrc\asrc.h" "%OUTPUTDIR%\asrc.h" /Y
copy "%ROOTDIR%\mqx\source\io\asrc\asrc_prv.h" "%OUTPUTDIR%\asrc_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\cm.h" "%OUTPUTDIR%\cm.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\cm_vybrid.h" "%OUTPUTDIR%\cm_vybrid.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\vybrid\bsp_clk_name.h" "%OUTPUTDIR%\bsp_clk_name.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\vybrid\bsp_clk_nodes.h" "%OUTPUTDIR%\bsp_clk_nodes.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\vybrid\bsp_clk_nodes_impl.h" "%OUTPUTDIR%\bsp_clk_nodes_impl.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\vybrid\bsp_clk_api.h" "%OUTPUTDIR%\bsp_clk_api.h" /Y
copy "%ROOTDIR%\config\svf522revb_a5\user_config.h" "%OUTPUTDIR%\..\user_config.h" /Y
copy "%ROOTDIR%\mqx\source\io\core_mutex\core_mutex_sema4.h" "%OUTPUTDIR%\core_mutex_sema4.h" /Y
copy "%ROOTDIR%\mqx\source\io\core_mutex\core_mutex.h" "%OUTPUTDIR%\core_mutex.h" /Y
copy "%ROOTDIR%\mqx\source\io\core_mutex\sema4.h" "%OUTPUTDIR%\sema4.h" /Y
copy "%ROOTDIR%\mqx\source\io\dcu4\dcu4.h" "%OUTPUTDIR%\dcu4.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\dma.h" "%OUTPUTDIR%\dma.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\edma.h" "%OUTPUTDIR%\edma.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\edma_prv.h" "%OUTPUTDIR%\edma_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_vybrid.h" "%OUTPUTDIR%\macnet_vybrid.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\phy\phy_lan8720.h" "%OUTPUTDIR%\phy_lan8720.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_rev.h" "%OUTPUTDIR%\macnet_rev.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_1588.h" "%OUTPUTDIR%\macnet_1588.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet_rev.h" "%OUTPUTDIR%\enet_rev.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_vybrid.h" "%OUTPUTDIR%\esai_vybrid.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_fifo\vybrid_esai_regs.h" "%OUTPUTDIR%\vybrid_esai_regs.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_vport\esai_vport_vybrid.h" "%OUTPUTDIR%\esai_vport_vybrid.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_vport\esai_vport_vybrid_prv.h" "%OUTPUTDIR%\esai_vport_vybrid_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_config.h" "%OUTPUTDIR%\esai_config.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_fifo\esai_fifo_config.h" "%OUTPUTDIR%\esai_fifo_config.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_fifo\esai_fifo_hw.h" "%OUTPUTDIR%\esai_fifo_hw.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_fifo\esai_fifo_node.h" "%OUTPUTDIR%\esai_fifo_node.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_fifo\esai_fifo_prv.h" "%OUTPUTDIR%\esai_fifo_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_vport\esai_fifo.h" "%OUTPUTDIR%\esai_fifo.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_vport\esai_vport.h" "%OUTPUTDIR%\esai_vport.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_vport\esai_vport_config.h" "%OUTPUTDIR%\esai_vport_config.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_vport\esai_vport_prv.h" "%OUTPUTDIR%\esai_vport_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\esdhc\esdhc.h" "%OUTPUTDIR%\esdhc.h" /Y
copy "%ROOTDIR%\mqx\source\io\fbdev\fbdev.h" "%OUTPUTDIR%\fbdev.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\freescale\flash_vybrid.h" "%OUTPUTDIR%\flash_vybrid.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\freescale\flash_quadspi.h" "%OUTPUTDIR%\flash_quadspi.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\flashx.h" "%OUTPUTDIR%\flashx.h" /Y
copy "%ROOTDIR%\mqx\source\io\can\flexcan\fsl_flexcan_hal.h" "%OUTPUTDIR%\fsl_flexcan_hal.h" /Y
copy "%ROOTDIR%\mqx\source\io\can\flexcan\fsl_flexcan_driver.h" "%OUTPUTDIR%\fsl_flexcan_driver.h" /Y
copy "%ROOTDIR%\mqx\source\io\can\flexcan\fsl_flexcan_int.h" "%OUTPUTDIR%\fsl_flexcan_int.h" /Y
copy "%ROOTDIR%\mqx\source\io\ftm\quaddec\ftm_quaddec_vybrid.c" "%OUTPUTDIR%\ftm_quaddec_vybrid.c" /Y
copy "%ROOTDIR%\mqx\source\io\ftm\ftm.h" "%OUTPUTDIR%\ftm.h" /Y
copy "%ROOTDIR%\mqx\source\io\ftm\quaddec\ftm_quaddec.h" "%OUTPUTDIR%\ftm_quaddec.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer_pit.h" "%OUTPUTDIR%\hwtimer_pit.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer_gtim.h" "%OUTPUTDIR%\hwtimer_gtim.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer.h" "%OUTPUTDIR%\hwtimer.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\qi2c.h" "%OUTPUTDIR%\qi2c.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\i2c_qi2c.h" "%OUTPUTDIR%\i2c_qi2c.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\i2c.h" "%OUTPUTDIR%\i2c.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\svf522revb_a5\bsp_cm.h" "%OUTPUTDIR%\bsp_cm.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\svf522revb_a5\init_lpm.h" "%OUTPUTDIR%\init_lpm.h" /Y
copy "%ROOTDIR%\config\common\small_ram_config.h" "%OUTPUTDIR%\..\small_ram_config.h" /Y
copy "%ROOTDIR%\config\common\smallest_config.h" "%OUTPUTDIR%\..\smallest_config.h" /Y
copy "%ROOTDIR%\config\common\maximum_config.h" "%OUTPUTDIR%\..\maximum_config.h" /Y
copy "%ROOTDIR%\config\common\verif_enabled_config.h" "%OUTPUTDIR%\..\verif_enabled_config.h" /Y
copy "%ROOTDIR%\mqx\source\include\mqx.h" "%OUTPUTDIR%\mqx.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\svf522revb_a5\bsp.h" "%OUTPUTDIR%\bsp.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\svf522revb_a5\bsp_rev.h" "%OUTPUTDIR%\bsp_rev.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\svf522revb_a5\svf522revb_a5.h" "%OUTPUTDIR%\svf522revb_a5.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\ethernet.h" "%OUTPUTDIR%\ethernet.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet.h" "%OUTPUTDIR%\enet.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet_wifi.h" "%OUTPUTDIR%\enet_wifi.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_expander\io_exp_max7310.h" "%OUTPUTDIR%\io_exp_max7310.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_expander\io_expander.h" "%OUTPUTDIR%\io_expander.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_mem\io_mem.h" "%OUTPUTDIR%\io_mem.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_null\io_null.h" "%OUTPUTDIR%\io_null.h" /Y
copy "%ROOTDIR%\mqx\source\io\pipe\io_pipe.h" "%OUTPUTDIR%\io_pipe.h" /Y
copy "%ROOTDIR%\mqx\source\io\lpm\vybrid\lpm_vybrid.h" "%OUTPUTDIR%\lpm_vybrid.h" /Y
copy "%ROOTDIR%\mqx\source\io\lpm\vybrid\vybrid_wkpu.h" "%OUTPUTDIR%\vybrid_wkpu.h" /Y
copy "%ROOTDIR%\mqx\source\io\lpm\lpm.h" "%OUTPUTDIR%\lpm.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwadc\lwadc_vadc.h" "%OUTPUTDIR%\lwadc_vadc.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwadc\lwadc.h" "%OUTPUTDIR%\lwadc.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwgpio\lwgpio_vgpio.h" "%OUTPUTDIR%\lwgpio_vgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwgpio\lwgpio.h" "%OUTPUTDIR%\lwgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\shmem\pcb_shm.h" "%OUTPUTDIR%\pcb_shm.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\shmem\pcbshmv.h" "%OUTPUTDIR%\pcbshmv.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\io_pcb.h" "%OUTPUTDIR%\io_pcb.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\mqxa\pcb_mqxa.h" "%OUTPUTDIR%\pcb_mqxa.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\mqxa\pcbmqxav.h" "%OUTPUTDIR%\pcbmqxav.h" /Y
copy "%ROOTDIR%\mqx\source\io\qspi\qspi.h" "%OUTPUTDIR%\qspi.h" /Y
copy "%ROOTDIR%\mqx\source\io\qspi\qspi_quadspi.h" "%OUTPUTDIR%\qspi_quadspi.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai_ksai.h" "%OUTPUTDIR%\sai_ksai.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai.h" "%OUTPUTDIR%\sai.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai_audio.h" "%OUTPUTDIR%\sai_audio.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard_esdhc\sdcard_esdhc.h" "%OUTPUTDIR%\sdcard_esdhc.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard.h" "%OUTPUTDIR%\sdcard.h" /Y
copy "%ROOTDIR%\mqx\source\io\serial\serl_kuart.h" "%OUTPUTDIR%\serl_kuart.h" /Y
copy "%ROOTDIR%\mqx\source\io\serial\serial.h" "%OUTPUTDIR%\serial.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi_dma.h" "%OUTPUTDIR%\spi_dspi_dma.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi_common.h" "%OUTPUTDIR%\spi_dspi_common.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi.h" "%OUTPUTDIR%\spi.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi.h" "%OUTPUTDIR%\spi_dspi.h" /Y
copy "%ROOTDIR%\mqx\source\io\tfs\tfs.h" "%OUTPUTDIR%\tfs.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_host_ehci.h" "%OUTPUTDIR%\if_host_ehci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_host_khci.h" "%OUTPUTDIR%\if_host_khci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_dev_ehci.h" "%OUTPUTDIR%\if_dev_ehci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_dev_khci.h" "%OUTPUTDIR%\if_dev_khci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\usb_bsp.h" "%OUTPUTDIR%\usb_bsp.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\svf522revb_a5\gcc_arm\intram.ld" "%OUTPUTDIR%\intram.ld" /Y
copy "%ROOTDIR%\mqx\source\bsp\svf522revb_a5\gcc_arm\ddr.ld" "%OUTPUTDIR%\ddr.ld" /Y
goto end_script


:label_ds5
IF NOT EXIST "%OUTPUTDIR%" mkdir "%OUTPUTDIR%"
IF NOT EXIST "%OUTPUTDIR%\." mkdir "%OUTPUTDIR%\."
IF NOT EXIST "%OUTPUTDIR%\.." mkdir "%OUTPUTDIR%\.."
copy "%ROOTDIR%\mqx\source\io\asrc\asrc_vybrid.h" "%OUTPUTDIR%\asrc_vybrid.h" /Y
copy "%ROOTDIR%\mqx\source\io\asrc\asrc_vybrid_prv.h" "%OUTPUTDIR%\asrc_vybrid_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\asrc\vybrid_asrc_regs.h" "%OUTPUTDIR%\vybrid_asrc_regs.h" /Y
copy "%ROOTDIR%\mqx\source\io\asrc\asrc.h" "%OUTPUTDIR%\asrc.h" /Y
copy "%ROOTDIR%\mqx\source\io\asrc\asrc_prv.h" "%OUTPUTDIR%\asrc_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\cm.h" "%OUTPUTDIR%\cm.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\cm_vybrid.h" "%OUTPUTDIR%\cm_vybrid.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\vybrid\bsp_clk_name.h" "%OUTPUTDIR%\bsp_clk_name.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\vybrid\bsp_clk_nodes.h" "%OUTPUTDIR%\bsp_clk_nodes.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\vybrid\bsp_clk_nodes_impl.h" "%OUTPUTDIR%\bsp_clk_nodes_impl.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\vybrid\bsp_clk_api.h" "%OUTPUTDIR%\bsp_clk_api.h" /Y
copy "%ROOTDIR%\config\svf522revb_a5\user_config.h" "%OUTPUTDIR%\..\user_config.h" /Y
copy "%ROOTDIR%\mqx\source\io\core_mutex\core_mutex_sema4.h" "%OUTPUTDIR%\core_mutex_sema4.h" /Y
copy "%ROOTDIR%\mqx\source\io\core_mutex\core_mutex.h" "%OUTPUTDIR%\core_mutex.h" /Y
copy "%ROOTDIR%\mqx\source\io\core_mutex\sema4.h" "%OUTPUTDIR%\sema4.h" /Y
copy "%ROOTDIR%\mqx\source\io\dcu4\dcu4.h" "%OUTPUTDIR%\dcu4.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\dma.h" "%OUTPUTDIR%\dma.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\edma.h" "%OUTPUTDIR%\edma.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\edma_prv.h" "%OUTPUTDIR%\edma_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_vybrid.h" "%OUTPUTDIR%\macnet_vybrid.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\phy\phy_lan8720.h" "%OUTPUTDIR%\phy_lan8720.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_rev.h" "%OUTPUTDIR%\macnet_rev.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_1588.h" "%OUTPUTDIR%\macnet_1588.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet_rev.h" "%OUTPUTDIR%\enet_rev.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_vybrid.h" "%OUTPUTDIR%\esai_vybrid.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_fifo\vybrid_esai_regs.h" "%OUTPUTDIR%\vybrid_esai_regs.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_vport\esai_vport_vybrid.h" "%OUTPUTDIR%\esai_vport_vybrid.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_vport\esai_vport_vybrid_prv.h" "%OUTPUTDIR%\esai_vport_vybrid_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_config.h" "%OUTPUTDIR%\esai_config.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_fifo\esai_fifo_config.h" "%OUTPUTDIR%\esai_fifo_config.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_fifo\esai_fifo_hw.h" "%OUTPUTDIR%\esai_fifo_hw.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_fifo\esai_fifo_node.h" "%OUTPUTDIR%\esai_fifo_node.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_fifo\esai_fifo_prv.h" "%OUTPUTDIR%\esai_fifo_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_vport\esai_fifo.h" "%OUTPUTDIR%\esai_fifo.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_vport\esai_vport.h" "%OUTPUTDIR%\esai_vport.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_vport\esai_vport_config.h" "%OUTPUTDIR%\esai_vport_config.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_vport\esai_vport_prv.h" "%OUTPUTDIR%\esai_vport_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\esdhc\esdhc.h" "%OUTPUTDIR%\esdhc.h" /Y
copy "%ROOTDIR%\mqx\source\io\fbdev\fbdev.h" "%OUTPUTDIR%\fbdev.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\freescale\flash_vybrid.h" "%OUTPUTDIR%\flash_vybrid.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\freescale\flash_quadspi.h" "%OUTPUTDIR%\flash_quadspi.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\flashx.h" "%OUTPUTDIR%\flashx.h" /Y
copy "%ROOTDIR%\mqx\source\io\can\flexcan\fsl_flexcan_hal.h" "%OUTPUTDIR%\fsl_flexcan_hal.h" /Y
copy "%ROOTDIR%\mqx\source\io\can\flexcan\fsl_flexcan_driver.h" "%OUTPUTDIR%\fsl_flexcan_driver.h" /Y
copy "%ROOTDIR%\mqx\source\io\can\flexcan\fsl_flexcan_int.h" "%OUTPUTDIR%\fsl_flexcan_int.h" /Y
copy "%ROOTDIR%\mqx\source\io\ftm\quaddec\ftm_quaddec_vybrid.c" "%OUTPUTDIR%\ftm_quaddec_vybrid.c" /Y
copy "%ROOTDIR%\mqx\source\io\ftm\ftm.h" "%OUTPUTDIR%\ftm.h" /Y
copy "%ROOTDIR%\mqx\source\io\ftm\quaddec\ftm_quaddec.h" "%OUTPUTDIR%\ftm_quaddec.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer_pit.h" "%OUTPUTDIR%\hwtimer_pit.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer_gtim.h" "%OUTPUTDIR%\hwtimer_gtim.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer.h" "%OUTPUTDIR%\hwtimer.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\qi2c.h" "%OUTPUTDIR%\qi2c.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\i2c_qi2c.h" "%OUTPUTDIR%\i2c_qi2c.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\i2c.h" "%OUTPUTDIR%\i2c.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\svf522revb_a5\bsp_cm.h" "%OUTPUTDIR%\bsp_cm.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\svf522revb_a5\init_lpm.h" "%OUTPUTDIR%\init_lpm.h" /Y
copy "%ROOTDIR%\config\common\small_ram_config.h" "%OUTPUTDIR%\..\small_ram_config.h" /Y
copy "%ROOTDIR%\config\common\smallest_config.h" "%OUTPUTDIR%\..\smallest_config.h" /Y
copy "%ROOTDIR%\config\common\maximum_config.h" "%OUTPUTDIR%\..\maximum_config.h" /Y
copy "%ROOTDIR%\config\common\verif_enabled_config.h" "%OUTPUTDIR%\..\verif_enabled_config.h" /Y
copy "%ROOTDIR%\mqx\source\include\mqx.h" "%OUTPUTDIR%\mqx.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\svf522revb_a5\bsp.h" "%OUTPUTDIR%\bsp.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\svf522revb_a5\bsp_rev.h" "%OUTPUTDIR%\bsp_rev.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\svf522revb_a5\svf522revb_a5.h" "%OUTPUTDIR%\svf522revb_a5.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\ethernet.h" "%OUTPUTDIR%\ethernet.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet.h" "%OUTPUTDIR%\enet.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet_wifi.h" "%OUTPUTDIR%\enet_wifi.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_expander\io_exp_max7310.h" "%OUTPUTDIR%\io_exp_max7310.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_expander\io_expander.h" "%OUTPUTDIR%\io_expander.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_mem\io_mem.h" "%OUTPUTDIR%\io_mem.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_null\io_null.h" "%OUTPUTDIR%\io_null.h" /Y
copy "%ROOTDIR%\mqx\source\io\pipe\io_pipe.h" "%OUTPUTDIR%\io_pipe.h" /Y
copy "%ROOTDIR%\mqx\source\io\lpm\vybrid\lpm_vybrid.h" "%OUTPUTDIR%\lpm_vybrid.h" /Y
copy "%ROOTDIR%\mqx\source\io\lpm\vybrid\vybrid_wkpu.h" "%OUTPUTDIR%\vybrid_wkpu.h" /Y
copy "%ROOTDIR%\mqx\source\io\lpm\lpm.h" "%OUTPUTDIR%\lpm.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwadc\lwadc_vadc.h" "%OUTPUTDIR%\lwadc_vadc.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwadc\lwadc.h" "%OUTPUTDIR%\lwadc.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwgpio\lwgpio_vgpio.h" "%OUTPUTDIR%\lwgpio_vgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwgpio\lwgpio.h" "%OUTPUTDIR%\lwgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\shmem\pcb_shm.h" "%OUTPUTDIR%\pcb_shm.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\shmem\pcbshmv.h" "%OUTPUTDIR%\pcbshmv.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\io_pcb.h" "%OUTPUTDIR%\io_pcb.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\mqxa\pcb_mqxa.h" "%OUTPUTDIR%\pcb_mqxa.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\mqxa\pcbmqxav.h" "%OUTPUTDIR%\pcbmqxav.h" /Y
copy "%ROOTDIR%\mqx\source\io\qspi\qspi.h" "%OUTPUTDIR%\qspi.h" /Y
copy "%ROOTDIR%\mqx\source\io\qspi\qspi_quadspi.h" "%OUTPUTDIR%\qspi_quadspi.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai_ksai.h" "%OUTPUTDIR%\sai_ksai.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai.h" "%OUTPUTDIR%\sai.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai_audio.h" "%OUTPUTDIR%\sai_audio.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard_esdhc\sdcard_esdhc.h" "%OUTPUTDIR%\sdcard_esdhc.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard.h" "%OUTPUTDIR%\sdcard.h" /Y
copy "%ROOTDIR%\mqx\source\io\serial\serl_kuart.h" "%OUTPUTDIR%\serl_kuart.h" /Y
copy "%ROOTDIR%\mqx\source\io\serial\serial.h" "%OUTPUTDIR%\serial.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi_dma.h" "%OUTPUTDIR%\spi_dspi_dma.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi_common.h" "%OUTPUTDIR%\spi_dspi_common.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi.h" "%OUTPUTDIR%\spi.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi.h" "%OUTPUTDIR%\spi_dspi.h" /Y
copy "%ROOTDIR%\mqx\source\io\tfs\tfs.h" "%OUTPUTDIR%\tfs.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_host_ehci.h" "%OUTPUTDIR%\if_host_ehci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_host_khci.h" "%OUTPUTDIR%\if_host_khci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_dev_ehci.h" "%OUTPUTDIR%\if_dev_ehci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_dev_khci.h" "%OUTPUTDIR%\if_dev_khci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\usb_bsp.h" "%OUTPUTDIR%\usb_bsp.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\svf522revb_a5\ds5\intram.scf" "%OUTPUTDIR%\intram.scf" /Y
copy "%ROOTDIR%\mqx\source\bsp\svf522revb_a5\ds5\ddr.scf" "%OUTPUTDIR%\ddr.scf" /Y
goto end_script


:label_iar
IF NOT EXIST "%OUTPUTDIR%" mkdir "%OUTPUTDIR%"
IF NOT EXIST "%OUTPUTDIR%\." mkdir "%OUTPUTDIR%\."
IF NOT EXIST "%OUTPUTDIR%\.." mkdir "%OUTPUTDIR%\.."
copy "%ROOTDIR%\mqx\source\io\asrc\asrc_vybrid.h" "%OUTPUTDIR%\asrc_vybrid.h" /Y
copy "%ROOTDIR%\mqx\source\io\asrc\asrc_vybrid_prv.h" "%OUTPUTDIR%\asrc_vybrid_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\asrc\vybrid_asrc_regs.h" "%OUTPUTDIR%\vybrid_asrc_regs.h" /Y
copy "%ROOTDIR%\mqx\source\io\asrc\asrc.h" "%OUTPUTDIR%\asrc.h" /Y
copy "%ROOTDIR%\mqx\source\io\asrc\asrc_prv.h" "%OUTPUTDIR%\asrc_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\cm.h" "%OUTPUTDIR%\cm.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\cm_vybrid.h" "%OUTPUTDIR%\cm_vybrid.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\vybrid\bsp_clk_name.h" "%OUTPUTDIR%\bsp_clk_name.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\vybrid\bsp_clk_nodes.h" "%OUTPUTDIR%\bsp_clk_nodes.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\vybrid\bsp_clk_nodes_impl.h" "%OUTPUTDIR%\bsp_clk_nodes_impl.h" /Y
copy "%ROOTDIR%\mqx\source\io\cm\vybrid\bsp_clk_api.h" "%OUTPUTDIR%\bsp_clk_api.h" /Y
copy "%ROOTDIR%\config\svf522revb_a5\user_config.h" "%OUTPUTDIR%\..\user_config.h" /Y
copy "%ROOTDIR%\mqx\source\io\core_mutex\core_mutex_sema4.h" "%OUTPUTDIR%\core_mutex_sema4.h" /Y
copy "%ROOTDIR%\mqx\source\io\core_mutex\core_mutex.h" "%OUTPUTDIR%\core_mutex.h" /Y
copy "%ROOTDIR%\mqx\source\io\core_mutex\sema4.h" "%OUTPUTDIR%\sema4.h" /Y
copy "%ROOTDIR%\mqx\source\io\dcu4\dcu4.h" "%OUTPUTDIR%\dcu4.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\dma.h" "%OUTPUTDIR%\dma.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\edma.h" "%OUTPUTDIR%\edma.h" /Y
copy "%ROOTDIR%\mqx\source\io\dma\edma_prv.h" "%OUTPUTDIR%\edma_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_vybrid.h" "%OUTPUTDIR%\macnet_vybrid.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\phy\phy_lan8720.h" "%OUTPUTDIR%\phy_lan8720.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_rev.h" "%OUTPUTDIR%\macnet_rev.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\macnet\macnet_1588.h" "%OUTPUTDIR%\macnet_1588.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet_rev.h" "%OUTPUTDIR%\enet_rev.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_vybrid.h" "%OUTPUTDIR%\esai_vybrid.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_fifo\vybrid_esai_regs.h" "%OUTPUTDIR%\vybrid_esai_regs.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_vport\esai_vport_vybrid.h" "%OUTPUTDIR%\esai_vport_vybrid.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_vport\esai_vport_vybrid_prv.h" "%OUTPUTDIR%\esai_vport_vybrid_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_config.h" "%OUTPUTDIR%\esai_config.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_fifo\esai_fifo_config.h" "%OUTPUTDIR%\esai_fifo_config.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_fifo\esai_fifo_hw.h" "%OUTPUTDIR%\esai_fifo_hw.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_fifo\esai_fifo_node.h" "%OUTPUTDIR%\esai_fifo_node.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_fifo\esai_fifo_prv.h" "%OUTPUTDIR%\esai_fifo_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_vport\esai_fifo.h" "%OUTPUTDIR%\esai_fifo.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_vport\esai_vport.h" "%OUTPUTDIR%\esai_vport.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_vport\esai_vport_config.h" "%OUTPUTDIR%\esai_vport_config.h" /Y
copy "%ROOTDIR%\mqx\source\io\esai\esai_vport\esai_vport_prv.h" "%OUTPUTDIR%\esai_vport_prv.h" /Y
copy "%ROOTDIR%\mqx\source\io\esdhc\esdhc.h" "%OUTPUTDIR%\esdhc.h" /Y
copy "%ROOTDIR%\mqx\source\io\fbdev\fbdev.h" "%OUTPUTDIR%\fbdev.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\freescale\flash_vybrid.h" "%OUTPUTDIR%\flash_vybrid.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\freescale\flash_quadspi.h" "%OUTPUTDIR%\flash_quadspi.h" /Y
copy "%ROOTDIR%\mqx\source\io\flashx\flashx.h" "%OUTPUTDIR%\flashx.h" /Y
copy "%ROOTDIR%\mqx\source\io\can\flexcan\fsl_flexcan_hal.h" "%OUTPUTDIR%\fsl_flexcan_hal.h" /Y
copy "%ROOTDIR%\mqx\source\io\can\flexcan\fsl_flexcan_driver.h" "%OUTPUTDIR%\fsl_flexcan_driver.h" /Y
copy "%ROOTDIR%\mqx\source\io\can\flexcan\fsl_flexcan_int.h" "%OUTPUTDIR%\fsl_flexcan_int.h" /Y
copy "%ROOTDIR%\mqx\source\io\ftm\quaddec\ftm_quaddec_vybrid.c" "%OUTPUTDIR%\ftm_quaddec_vybrid.c" /Y
copy "%ROOTDIR%\mqx\source\io\ftm\ftm.h" "%OUTPUTDIR%\ftm.h" /Y
copy "%ROOTDIR%\mqx\source\io\ftm\quaddec\ftm_quaddec.h" "%OUTPUTDIR%\ftm_quaddec.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer_pit.h" "%OUTPUTDIR%\hwtimer_pit.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer_gtim.h" "%OUTPUTDIR%\hwtimer_gtim.h" /Y
copy "%ROOTDIR%\mqx\source\io\hwtimer\hwtimer.h" "%OUTPUTDIR%\hwtimer.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\qi2c.h" "%OUTPUTDIR%\qi2c.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\i2c_qi2c.h" "%OUTPUTDIR%\i2c_qi2c.h" /Y
copy "%ROOTDIR%\mqx\source\io\i2c\i2c.h" "%OUTPUTDIR%\i2c.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\svf522revb_a5\bsp_cm.h" "%OUTPUTDIR%\bsp_cm.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\svf522revb_a5\init_lpm.h" "%OUTPUTDIR%\init_lpm.h" /Y
copy "%ROOTDIR%\config\common\small_ram_config.h" "%OUTPUTDIR%\..\small_ram_config.h" /Y
copy "%ROOTDIR%\config\common\smallest_config.h" "%OUTPUTDIR%\..\smallest_config.h" /Y
copy "%ROOTDIR%\config\common\maximum_config.h" "%OUTPUTDIR%\..\maximum_config.h" /Y
copy "%ROOTDIR%\config\common\verif_enabled_config.h" "%OUTPUTDIR%\..\verif_enabled_config.h" /Y
copy "%ROOTDIR%\mqx\source\include\mqx.h" "%OUTPUTDIR%\mqx.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\svf522revb_a5\bsp.h" "%OUTPUTDIR%\bsp.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\svf522revb_a5\bsp_rev.h" "%OUTPUTDIR%\bsp_rev.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\svf522revb_a5\svf522revb_a5.h" "%OUTPUTDIR%\svf522revb_a5.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\ethernet.h" "%OUTPUTDIR%\ethernet.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet.h" "%OUTPUTDIR%\enet.h" /Y
copy "%ROOTDIR%\mqx\source\io\enet\enet_wifi.h" "%OUTPUTDIR%\enet_wifi.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_expander\io_exp_max7310.h" "%OUTPUTDIR%\io_exp_max7310.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_expander\io_expander.h" "%OUTPUTDIR%\io_expander.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_mem\io_mem.h" "%OUTPUTDIR%\io_mem.h" /Y
copy "%ROOTDIR%\mqx\source\io\io_null\io_null.h" "%OUTPUTDIR%\io_null.h" /Y
copy "%ROOTDIR%\mqx\source\io\pipe\io_pipe.h" "%OUTPUTDIR%\io_pipe.h" /Y
copy "%ROOTDIR%\mqx\source\io\lpm\vybrid\lpm_vybrid.h" "%OUTPUTDIR%\lpm_vybrid.h" /Y
copy "%ROOTDIR%\mqx\source\io\lpm\vybrid\vybrid_wkpu.h" "%OUTPUTDIR%\vybrid_wkpu.h" /Y
copy "%ROOTDIR%\mqx\source\io\lpm\lpm.h" "%OUTPUTDIR%\lpm.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwadc\lwadc_vadc.h" "%OUTPUTDIR%\lwadc_vadc.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwadc\lwadc.h" "%OUTPUTDIR%\lwadc.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwgpio\lwgpio_vgpio.h" "%OUTPUTDIR%\lwgpio_vgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\lwgpio\lwgpio.h" "%OUTPUTDIR%\lwgpio.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\shmem\pcb_shm.h" "%OUTPUTDIR%\pcb_shm.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\shmem\pcbshmv.h" "%OUTPUTDIR%\pcbshmv.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\io_pcb.h" "%OUTPUTDIR%\io_pcb.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\mqxa\pcb_mqxa.h" "%OUTPUTDIR%\pcb_mqxa.h" /Y
copy "%ROOTDIR%\mqx\source\io\pcb\mqxa\pcbmqxav.h" "%OUTPUTDIR%\pcbmqxav.h" /Y
copy "%ROOTDIR%\mqx\source\io\qspi\qspi.h" "%OUTPUTDIR%\qspi.h" /Y
copy "%ROOTDIR%\mqx\source\io\qspi\qspi_quadspi.h" "%OUTPUTDIR%\qspi_quadspi.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai_ksai.h" "%OUTPUTDIR%\sai_ksai.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai.h" "%OUTPUTDIR%\sai.h" /Y
copy "%ROOTDIR%\mqx\source\io\sai\sai_audio.h" "%OUTPUTDIR%\sai_audio.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard_esdhc\sdcard_esdhc.h" "%OUTPUTDIR%\sdcard_esdhc.h" /Y
copy "%ROOTDIR%\mqx\source\io\sdcard\sdcard.h" "%OUTPUTDIR%\sdcard.h" /Y
copy "%ROOTDIR%\mqx\source\io\serial\serl_kuart.h" "%OUTPUTDIR%\serl_kuart.h" /Y
copy "%ROOTDIR%\mqx\source\io\serial\serial.h" "%OUTPUTDIR%\serial.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi_dma.h" "%OUTPUTDIR%\spi_dspi_dma.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi_common.h" "%OUTPUTDIR%\spi_dspi_common.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi.h" "%OUTPUTDIR%\spi.h" /Y
copy "%ROOTDIR%\mqx\source\io\spi\spi_dspi.h" "%OUTPUTDIR%\spi_dspi.h" /Y
copy "%ROOTDIR%\mqx\source\io\tfs\tfs.h" "%OUTPUTDIR%\tfs.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_host_ehci.h" "%OUTPUTDIR%\if_host_ehci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_host_khci.h" "%OUTPUTDIR%\if_host_khci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_dev_ehci.h" "%OUTPUTDIR%\if_dev_ehci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\if_dev_khci.h" "%OUTPUTDIR%\if_dev_khci.h" /Y
copy "%ROOTDIR%\mqx\source\io\usb\usb_bsp.h" "%OUTPUTDIR%\usb_bsp.h" /Y
copy "%ROOTDIR%\mqx\source\bsp\svf522revb_a5\iar\ddr.icf" "%OUTPUTDIR%\ddr.icf" /Y
copy "%ROOTDIR%\mqx\source\bsp\svf522revb_a5\iar\intram.icf" "%OUTPUTDIR%\intram.icf" /Y
copy "%ROOTDIR%\mqx\source\bsp\svf522revb_a5\iar\svf522revb_a5_ddr.mac" "%OUTPUTDIR%\svf522revb_a5_ddr.mac" /Y
goto end_script



:end_script

