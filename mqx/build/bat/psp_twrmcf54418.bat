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
copy "%ROOTDIR%\mqx\source\psp\coldfire\asm_mac.h" "%OUTPUTDIR%\asm_mac.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\mqx_assert.h" "%OUTPUTDIR%\mqx_assert.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\coldfire.h" "%OUTPUTDIR%\coldfire.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\psp.h" "%OUTPUTDIR%\psp.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\psp_abi.h" "%OUTPUTDIR%\psp_abi.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\psp_comp.h" "%OUTPUTDIR%\psp_comp.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\psp_cpu.h" "%OUTPUTDIR%\psp_cpu.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\psp_cpudef.h" "%OUTPUTDIR%\psp_cpudef.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\psp_math.h" "%OUTPUTDIR%\psp_math.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\psp_rev.h" "%OUTPUTDIR%\psp_rev.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\psp_supp.h" "%OUTPUTDIR%\psp_supp.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\psp_time.h" "%OUTPUTDIR%\psp_time.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\psptypes.h" "%OUTPUTDIR%\psptypes.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\reg_enet.h" "%OUTPUTDIR%\reg_enet.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\reg_nfc.h" "%OUTPUTDIR%\reg_nfc.h" /Y
copy "%ROOTDIR%\config\common\small_ram_config.h" "%OUTPUTDIR%\small_ram_config.h" /Y
copy "%ROOTDIR%\mqx\source\include\gen_rev.h" "%OUTPUTDIR%\gen_rev.h" /Y
copy "%ROOTDIR%\mqx\source\include\eds.h" "%OUTPUTDIR%\eds.h" /Y
copy "%ROOTDIR%\mqx\source\include\edserial.h" "%OUTPUTDIR%\edserial.h" /Y
copy "%ROOTDIR%\mqx\source\include\event.h" "%OUTPUTDIR%\event.h" /Y
copy "%ROOTDIR%\mqx\source\include\event_prv.h" "%OUTPUTDIR%\event_prv.h" /Y
copy "%ROOTDIR%\mqx\source\include\fio.h" "%OUTPUTDIR%\fio.h" /Y
copy "%ROOTDIR%\mqx\source\include\charq.h" "%OUTPUTDIR%\charq.h" /Y
copy "%ROOTDIR%\mqx\source\include\io.h" "%OUTPUTDIR%\io.h" /Y
copy "%ROOTDIR%\mqx\source\include\ioctl.h" "%OUTPUTDIR%\ioctl.h" /Y
copy "%ROOTDIR%\mqx\source\include\io_rev.h" "%OUTPUTDIR%\io_rev.h" /Y
copy "%ROOTDIR%\mqx\source\include\ipc.h" "%OUTPUTDIR%\ipc.h" /Y
copy "%ROOTDIR%\mqx\source\include\ipc_pcb.h" "%OUTPUTDIR%\ipc_pcb.h" /Y
copy "%ROOTDIR%\mqx\source\include\ipc_pcbv.h" "%OUTPUTDIR%\ipc_pcbv.h" /Y
copy "%ROOTDIR%\mqx\source\include\klog.h" "%OUTPUTDIR%\klog.h" /Y
copy "%ROOTDIR%\mqx\source\include\log.h" "%OUTPUTDIR%\log.h" /Y
copy "%ROOTDIR%\mqx\source\include\lwsem.h" "%OUTPUTDIR%\lwsem.h" /Y
copy "%ROOTDIR%\mqx\source\include\lwevent.h" "%OUTPUTDIR%\lwevent.h" /Y
copy "%ROOTDIR%\mqx\source\include\lwevent_prv.h" "%OUTPUTDIR%\lwevent_prv.h" /Y
copy "%ROOTDIR%\mqx\source\include\lwlog.h" "%OUTPUTDIR%\lwlog.h" /Y
copy "%ROOTDIR%\mqx\source\include\lwmem.h" "%OUTPUTDIR%\lwmem.h" /Y
copy "%ROOTDIR%\mqx\source\include\lwmem_prv.h" "%OUTPUTDIR%\lwmem_prv.h" /Y
copy "%ROOTDIR%\mqx\source\include\lwmsgq.h" "%OUTPUTDIR%\lwmsgq.h" /Y
copy "%ROOTDIR%\mqx\source\include\lwtimer.h" "%OUTPUTDIR%\lwtimer.h" /Y
copy "%ROOTDIR%\mqx\source\include\mem_prv.h" "%OUTPUTDIR%\mem_prv.h" /Y
copy "%ROOTDIR%\mqx\source\include\message.h" "%OUTPUTDIR%\message.h" /Y
copy "%ROOTDIR%\mqx\source\include\mmu.h" "%OUTPUTDIR%\mmu.h" /Y
copy "%ROOTDIR%\mqx\source\include\mqx.h" "%OUTPUTDIR%\mqx.h" /Y
copy "%ROOTDIR%\mqx\source\include\mqx_cnfg.h" "%OUTPUTDIR%\mqx_cnfg.h" /Y
copy "%ROOTDIR%\mqx\source\include\mqx_cpudef.h" "%OUTPUTDIR%\mqx_cpudef.h" /Y
copy "%ROOTDIR%\mqx\source\include\mqx_inc.h" "%OUTPUTDIR%\mqx_inc.h" /Y
copy "%ROOTDIR%\mqx\source\include\mqx_ioc.h" "%OUTPUTDIR%\mqx_ioc.h" /Y
copy "%ROOTDIR%\mqx\source\include\mqx_prv.h" "%OUTPUTDIR%\mqx_prv.h" /Y
copy "%ROOTDIR%\mqx\source\include\mqx_str.h" "%OUTPUTDIR%\mqx_str.h" /Y
copy "%ROOTDIR%\mqx\source\include\mqx_macros.h" "%OUTPUTDIR%\mqx_macros.h" /Y
copy "%ROOTDIR%\mqx\source\include\msg_prv.h" "%OUTPUTDIR%\msg_prv.h" /Y
copy "%ROOTDIR%\mqx\source\include\mutex.h" "%OUTPUTDIR%\mutex.h" /Y
copy "%ROOTDIR%\mqx\source\include\name.h" "%OUTPUTDIR%\name.h" /Y
copy "%ROOTDIR%\mqx\source\include\name_prv.h" "%OUTPUTDIR%\name_prv.h" /Y
copy "%ROOTDIR%\mqx\source\include\partition.h" "%OUTPUTDIR%\partition.h" /Y
copy "%ROOTDIR%\mqx\source\include\partition_prv.h" "%OUTPUTDIR%\partition_prv.h" /Y
copy "%ROOTDIR%\mqx\source\include\pcb.h" "%OUTPUTDIR%\pcb.h" /Y
copy "%ROOTDIR%\mqx\source\include\psptypes_legacy.h" "%OUTPUTDIR%\psptypes_legacy.h" /Y
copy "%ROOTDIR%\mqx\source\include\posix.h" "%OUTPUTDIR%\posix.h" /Y
copy "%ROOTDIR%\mqx\source\include\queue.h" "%OUTPUTDIR%\queue.h" /Y
copy "%ROOTDIR%\mqx\source\include\sem.h" "%OUTPUTDIR%\sem.h" /Y
copy "%ROOTDIR%\mqx\source\include\sem_prv.h" "%OUTPUTDIR%\sem_prv.h" /Y
copy "%ROOTDIR%\mqx\source\include\timer.h" "%OUTPUTDIR%\timer.h" /Y
copy "%ROOTDIR%\mqx\source\include\watchdog.h" "%OUTPUTDIR%\watchdog.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\mcf5441.h" "%OUTPUTDIR%\mcf5441.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\mcf544xx_adc.h" "%OUTPUTDIR%\mcf544xx_adc.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\mcf54xx_ccm.h" "%OUTPUTDIR%\mcf54xx_ccm.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\mcf54xx_fcan.h" "%OUTPUTDIR%\mcf54xx_fcan.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\mcf54xx_i2c.h" "%OUTPUTDIR%\mcf54xx_i2c.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\mcf54xx_ictl.h" "%OUTPUTDIR%\mcf54xx_ictl.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\mcf54xx_sdramc.h" "%OUTPUTDIR%\mcf54xx_sdramc.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\mcf54xx_uart.h" "%OUTPUTDIR%\mcf54xx_uart.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\mcf5xxx_dspi.h" "%OUTPUTDIR%\mcf5xxx_dspi.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\mcf5xxx_esdhc.h" "%OUTPUTDIR%\mcf5xxx_esdhc.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\mcf5xxx_esw.h" "%OUTPUTDIR%\mcf5xxx_esw.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\mcf5xxx_fb.h" "%OUTPUTDIR%\mcf5xxx_fb.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\mcf5xxx_irtc.h" "%OUTPUTDIR%\mcf5xxx_irtc.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\mcf5xxx_pit.h" "%OUTPUTDIR%\mcf5xxx_pit.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\mcf5xxx_usbotg.h" "%OUTPUTDIR%\mcf5xxx_usbotg.h" /Y
copy "%ROOTDIR%\mqx\source\tad\tad.h" "%OUTPUTDIR%\tad.h" /Y
copy "%ROOTDIR%\mqx\source\include\tlsf.h" "%OUTPUTDIR%\tlsf.h" /Y
copy "%ROOTDIR%\mqx\source\include\tlsfbits.h" "%OUTPUTDIR%\tlsfbits.h" /Y
copy "%ROOTDIR%\mqx\source\include\tlsf_adaptation.h" "%OUTPUTDIR%\tlsf_adaptation.h" /Y
copy "%ROOTDIR%\mqx\source\psp\coldfire\cw_comp.h" "%OUTPUTDIR%\cw_comp.h" /Y
goto end_script



:end_script

