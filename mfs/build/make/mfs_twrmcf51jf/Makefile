#----------------------------------------------------------
# setup variables
#----------------------------------------------------------
MQX_ROOTDIR             = $(abspath ../../../..)
TYPE                    = library
NAME                    = mfs
BOARD                   = twrmcf51jf
LIBRARY_ROOTDIR         = $(MQX_ROOTDIR)/lib/$(BOARD).$(TOOL)
LIBRARY_DIR             = $(LIBRARY_ROOTDIR)/$(CONFIG)/mfs
LIBRARY_FILE            = $(LIBRARY_DIR)/mfs.$(LIBRARY_EXT)
POSTBUILD_CMD           = $(if $(findstring $(HOSTENV),WINDOWS),$(MQX_ROOTDIR)/mfs/build/bat/mfs_twrmcf51jf.bat $(MQX_ROOTDIR) $(LIBRARY_DIR) $(TOOL),$(MQX_ROOTDIR)/mfs/build/bat/mfs_twrmcf51jf.sh $(MQX_ROOTDIR) $(LIBRARY_DIR) $(TOOL))


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
INCLUDE += $(MQX_ROOTDIR)/mfs/source/include
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


SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/dir_read.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_attribute.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_cache.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_chain.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_cluster.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_delete.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_dir_chain.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_dir_entry.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_directory.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_fat.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_find.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_fio.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_flush.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_format.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_globals.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_handle.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_ioctl.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_lfn.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_misc.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_mount.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_open.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_parse.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_read.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_rename.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_rw.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_search.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_time.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_unicode.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_valdev.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/mfs_write.c
SOURCES += $(MQX_ROOTDIR)/mfs/source/generic/part_mgr.c


#----------------------------------------------------------
# load global settings
#----------------------------------------------------------
include $(MQX_ROOTDIR)/build/common/make/global.mak
-include $(MQX_ROOTDIR)/build/$(BOARD)/make/tools/$(TOOL).mak
include $(MQX_ROOTDIR)/build/common/make/verify.mak
include $(MQX_ROOTDIR)/build/common/make/lib-process.mak

