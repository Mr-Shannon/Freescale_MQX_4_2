#----------------------------------------------------------
# setup variables
#----------------------------------------------------------
MQX_ROOTDIR             = $(abspath ../../../..)
TYPE                    = library
NAME                    = shell
BOARD                   = twrmcf51jf
LIBRARY_ROOTDIR         = $(MQX_ROOTDIR)/lib/$(BOARD).$(TOOL)
LIBRARY_DIR             = $(LIBRARY_ROOTDIR)/$(CONFIG)/shell
LIBRARY_FILE            = $(LIBRARY_DIR)/shell.$(LIBRARY_EXT)
POSTBUILD_CMD           = $(if $(findstring $(HOSTENV),WINDOWS),$(MQX_ROOTDIR)/shell/build/bat/shell_twrmcf51jf.bat $(MQX_ROOTDIR) $(LIBRARY_DIR) $(TOOL),$(MQX_ROOTDIR)/shell/build/bat/shell_twrmcf51jf.sh $(MQX_ROOTDIR) $(LIBRARY_DIR) $(TOOL))


#-----------------------------------------------------------
# load tool settings
#-----------------------------------------------------------
-include tools/$(TOOL).mak


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
INCLUDE += $(MQX_ROOTDIR)/mqx/source/psp/coldfire
INCLUDE += $(MQX_ROOTDIR)/config/twrmcf51jf
INCLUDE += $(MQX_ROOTDIR)/mqx/source/include
INCLUDE += $(MQX_ROOTDIR)/config/common
INCLUDE += $(TOOLCHAIN_ROOTDIR)/MCU/ColdFire_Support/ewl/EWL_C/include
INCLUDE += $(MQX_ROOTDIR)/shell/source/include
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/adc/kadc
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/adc
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/cm
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx/freescale
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx/amd
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx/fujitsu
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx/spansion
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx/atmel
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx/istrata
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx/sharp
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/gpio/mcf51jf
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/gpio
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/hmi
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/hmi/TSS/shared
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/hwtimer
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/i2c
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/i2c/polled
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/i2c/int
INCLUDE += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf51jf
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/enet
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/int_ctrl
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/io_mem
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/io_null
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pipe
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/lpm
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/lwgpio
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pcb
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pcb/mqxa
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pccard
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pcflash
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/sdcard/sdcard_spi
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/sdcard
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/serial
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/spi_legacy
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/spi_legacy/int
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/spi_legacy/polled
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/tfs
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/timer
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/usb
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/usb_dcd
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/usb_dcd/polled
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/usb_dcd/int
INCLUDE += $(MQX_ROOTDIR)/mqx/source/tad
INCLUDE += $(MQX_ROOTDIR)/mfs/source/include
INCLUDE += $(MQX_ROOTDIR)/rtcs/source/include
INCLUDE += $(MQX_ROOTDIR)/ssl


SOURCES += $(MQX_ROOTDIR)/shell/source/mfs/sh_cache.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mfs/sh_cd.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mfs/sh_compare.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mfs/sh_copy.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mfs/sh_create.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mfs/sh_del.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mfs/sh_df.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mfs/sh_di.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mfs/sh_dir.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mfs/sh_dirent.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mfs/sh_disect.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mfs/sh_flush.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mfs/sh_format.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mfs/sh_mkdir.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mfs/sh_pwd.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mfs/sh_read.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mfs/sh_readtest.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mfs/sh_rename.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mfs/sh_rmdir.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mfs/sh_type.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mfs/sh_write.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mfs/sh_writetest.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mqx/sh_abort.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mqx/sh_kill.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mqx/sh_pause.c
SOURCES += $(MQX_ROOTDIR)/shell/source/mqx/sh_tad.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_arpdisp.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_clock.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_echo.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_echosrv.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_enet.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_ftpc.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_ftpsrv.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_gate.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_getroute.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_ghbn.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_getname.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_ipconfig.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_iwconfig.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_llmnrsrv.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_nat.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_nstat.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_ping.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_ppp.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_rtcs.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_sendto.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_smtp.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_snmpd.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_tftpcln.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_tftpsrv.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_telnetcln.c
SOURCES += $(MQX_ROOTDIR)/shell/source/rtcs/sh_telnetsrv.c
SOURCES += $(MQX_ROOTDIR)/shell/source/shell/sh_cmdlist.c
SOURCES += $(MQX_ROOTDIR)/shell/source/shell/sh_exit.c
SOURCES += $(MQX_ROOTDIR)/shell/source/shell/sh_help.c
SOURCES += $(MQX_ROOTDIR)/shell/source/shell/sh_sh.c
SOURCES += $(MQX_ROOTDIR)/shell/source/shell/sh_util.c
SOURCES += $(MQX_ROOTDIR)/shell/source/shell/shell.c


#----------------------------------------------------------
# load global settings
#----------------------------------------------------------
include $(MQX_ROOTDIR)/build/common/make/global.mak
-include $(MQX_ROOTDIR)/build/$(BOARD)/make/tools/$(TOOL).mak
include $(MQX_ROOTDIR)/build/common/make/verify.mak
include $(MQX_ROOTDIR)/build/common/make/lib-process.mak

