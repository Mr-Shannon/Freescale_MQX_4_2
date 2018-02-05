#----------------------------------------------------------
# setup variables
#----------------------------------------------------------
MQX_ROOTDIR             = $(abspath ../../../../..)
TYPE                    = library
NAME                    = usbd
BOARD                   = twrmcf54418
LIBRARY_ROOTDIR         = $(MQX_ROOTDIR)/lib/$(BOARD).$(TOOL)
LIBRARY_DIR             = $(LIBRARY_ROOTDIR)/$(CONFIG)/usb
LIBRARY_FILE            = $(LIBRARY_DIR)/usbd.$(LIBRARY_EXT)
POSTBUILD_CMD           = $(if $(findstring $(HOSTENV),WINDOWS),$(MQX_ROOTDIR)/usb/device/build/bat/usbd_twrmcf54418.bat $(MQX_ROOTDIR) $(LIBRARY_DIR) $(TOOL),$(MQX_ROOTDIR)/usb/device/build/bat/usbd_twrmcf54418.sh $(MQX_ROOTDIR) $(LIBRARY_DIR) $(TOOL))


#-----------------------------------------------------------
# load tool settings
#-----------------------------------------------------------
-include tools/$(TOOL).mak


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
INCLUDE += $(MQX_ROOTDIR)/mqx/source/psp/coldfire
INCLUDE += $(MQX_ROOTDIR)/config/twrmcf54418
INCLUDE += $(MQX_ROOTDIR)/mqx/source/include
INCLUDE += $(MQX_ROOTDIR)/config/common
INCLUDE += $(TOOLCHAIN_ROOTDIR)/MCU/ColdFire_Support/ewl/EWL_C/include
INCLUDE += $(MQX_ROOTDIR)/usb/device/source/classes/include
INCLUDE += $(MQX_ROOTDIR)/usb/common/include
INCLUDE += $(MQX_ROOTDIR)/usb/device/source/include/ehci
INCLUDE += $(MQX_ROOTDIR)/usb/host/source/host/ehci
INCLUDE += $(MQX_ROOTDIR)/usb/device/source/include
INCLUDE += $(MQX_ROOTDIR)/usb/device/source/include/rtos
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/adc/mcf544xx
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/adc
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/enet/macnet
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/enet/phy
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/enet
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/esdhc
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/can/flexcan
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/gpio/mcf5441
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/gpio
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/i2c
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/i2c/polled
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/i2c/int
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/i2s
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/i2s/int
INCLUDE += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/int_ctrl
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/io_mem
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/io_null
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pipe
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/lwgpio
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/nandflash/nfc
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/nandflash
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pcb
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pcb/mqxa
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pccard
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pcflash
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/rtc
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/sdcard/sdcard_spi
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/sdcard/sdcard_esdhc
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/sdcard
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/serial
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/spi
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/tfs
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/timer
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/usb
INCLUDE += $(MQX_ROOTDIR)/mqx/source/tad


SOURCES += $(MQX_ROOTDIR)/usb/device/source/classes/audio/usb_audio.c
SOURCES += $(MQX_ROOTDIR)/usb/device/source/classes/cdc/usb_cdc.c
SOURCES += $(MQX_ROOTDIR)/usb/device/source/classes/cdc/usb_cdc_pstn.c
SOURCES += $(MQX_ROOTDIR)/usb/device/source/classes/common/usb_class.c
SOURCES += $(MQX_ROOTDIR)/usb/device/source/device/ehci/callback_ehci.c
SOURCES += $(MQX_ROOTDIR)/usb/device/source/device/ehci/ehci_dev_main.c
SOURCES += $(MQX_ROOTDIR)/usb/device/source/classes/common/usb_framework.c
SOURCES += $(MQX_ROOTDIR)/usb/device/source/classes/hid/usb_hid.c
SOURCES += $(MQX_ROOTDIR)/usb/device/source/classes/msd/usb_msc.c
SOURCES += $(MQX_ROOTDIR)/usb/device/source/classes/msd/usb_msc_scsi.c
SOURCES += $(MQX_ROOTDIR)/usb/device/source/classes/phdc/usb_phdc.c
SOURCES += $(MQX_ROOTDIR)/usb/device/source/device/dev_cncl.c
SOURCES += $(MQX_ROOTDIR)/usb/device/source/device/dev_ep_deinit.c
SOURCES += $(MQX_ROOTDIR)/usb/device/source/device/dev_main.c
SOURCES += $(MQX_ROOTDIR)/usb/device/source/device/dev_recv.c
SOURCES += $(MQX_ROOTDIR)/usb/device/source/device/dev_send.c
SOURCES += $(MQX_ROOTDIR)/usb/device/source/device/dev_shut.c
SOURCES += $(MQX_ROOTDIR)/usb/device/source/device/dev_utl.c


#----------------------------------------------------------
# load global settings
#----------------------------------------------------------
include $(MQX_ROOTDIR)/build/common/make/global.mak
-include $(MQX_ROOTDIR)/build/$(BOARD)/make/tools/$(TOOL).mak
include $(MQX_ROOTDIR)/build/common/make/verify.mak
include $(MQX_ROOTDIR)/build/common/make/lib-process.mak

