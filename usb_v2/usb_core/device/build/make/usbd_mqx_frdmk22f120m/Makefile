#----------------------------------------------------------
# setup variables
#----------------------------------------------------------
USB_ROOTDIR            = $(abspath ../../../../..)
OS                     = mqx
#-----------------------------------------------
# set board infomation
#-----------------------------------------------

TYPE                    = library
NAME                    = usbd_mqx
BOARD                   = frdmk22f120m
MQX_ROOTDIR             = $(USB_ROOTDIR)/..
LIBRARY_ROOTDIR         = $(MQX_ROOTDIR)/lib/$(BOARD).$(TOOL)
USB_LIBRARY_ROOTDIR     = $(USB_ROOTDIR)/output/$(BOARD).$(TOOL)
LIBRARY_DIR             = $(USB_LIBRARY_ROOTDIR)/$(CONFIG)/usbd/mqx
LIBRARY_FILE            = $(LIBRARY_DIR)/libusbd_mqx.$(LIBRARY_EXT)
POSTBUILD_CMD           = $(if $(findstring $(HOSTENV),WINDOWS),$(USB_ROOTDIR)/usb_core/device/build/bat/usbd_frdmk22f120m.bat $(USB_ROOTDIR) $(LIBRARY_DIR) $(TOOL) mqx,$(USB_ROOTDIR)/usb_core/device/build/bat/usbd_frdmk22f120m.sh $(USB_ROOTDIR) $(LIBRARY_DIR) $(TOOL) mqx)


#-----------------------------------------------------------
# load tool settings
#-----------------------------------------------------------
include tools/$(TOOL).mak


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
INCLUDE += $(USB_ROOTDIR)/adapter/sources
INCLUDE += $(USB_ROOTDIR)/adapter/sources/mqx
INCLUDE += $(USB_ROOTDIR)/usb_core/hal
INCLUDE += $(USB_ROOTDIR)/usb_core/device/include/frdmk22f120m
INCLUDE += $(USB_ROOTDIR)/usb_core/device/include
INCLUDE += $(USB_ROOTDIR)/usb_core/device/sources/classes/audio
INCLUDE += $(USB_ROOTDIR)/usb_core/device/sources/classes/include/config
INCLUDE += $(USB_ROOTDIR)/usb_core/device/sources/classes/cdc
INCLUDE += $(USB_ROOTDIR)/usb_core/device/sources/classes/common
INCLUDE += $(USB_ROOTDIR)/usb_core/device/sources/classes/composite
INCLUDE += $(USB_ROOTDIR)/usb_core/device/sources/classes/hid
INCLUDE += $(USB_ROOTDIR)/usb_core/device/sources/classes/include
INCLUDE += $(USB_ROOTDIR)/usb_core/device/sources/classes/msd
INCLUDE += $(USB_ROOTDIR)/usb_core/device/sources/classes/phdc
INCLUDE += $(USB_ROOTDIR)/usb_core/device/sources/controller
INCLUDE += $(USB_ROOTDIR)/usb_core/device/sources/controller/khci
INCLUDE += $(USB_ROOTDIR)/usb_core/include
endif
ifeq ($(CONFIG),release)
INCLUDE += $(USB_ROOTDIR)/adapter/sources
INCLUDE += $(USB_ROOTDIR)/adapter/sources/mqx
INCLUDE += $(USB_ROOTDIR)/usb_core/hal
INCLUDE += $(USB_ROOTDIR)/usb_core/device/include/frdmk22f120m
INCLUDE += $(USB_ROOTDIR)/usb_core/device/include
INCLUDE += $(USB_ROOTDIR)/usb_core/device/sources/classes/audio
INCLUDE += $(USB_ROOTDIR)/usb_core/device/sources/classes/include/config
INCLUDE += $(USB_ROOTDIR)/usb_core/device/sources/classes/cdc
INCLUDE += $(USB_ROOTDIR)/usb_core/device/sources/classes/common
INCLUDE += $(USB_ROOTDIR)/usb_core/device/sources/classes/composite
INCLUDE += $(USB_ROOTDIR)/usb_core/device/sources/classes/hid
INCLUDE += $(USB_ROOTDIR)/usb_core/device/sources/classes/include
INCLUDE += $(USB_ROOTDIR)/usb_core/device/sources/classes/msd
INCLUDE += $(USB_ROOTDIR)/usb_core/device/sources/classes/phdc
INCLUDE += $(USB_ROOTDIR)/usb_core/device/sources/controller
INCLUDE += $(USB_ROOTDIR)/usb_core/device/sources/controller/khci
INCLUDE += $(USB_ROOTDIR)/usb_core/include
endif



#-----------------------------------------------------------
# 'adapter' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/adapter/sources/mqx/adapter_mqx.c

#-----------------------------------------------------------
# 'usb_core_device_sources_bsp' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/device/sources/bsp/frdmk22f120m/usb_dev_bsp.c

#-----------------------------------------------------------
# 'usb_core_device_sources_class_driver_audio' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/device/sources/classes/audio/usb_audio.c

#-----------------------------------------------------------
# 'usb_core_device_sources_class_driver_cdc' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/device/sources/classes/cdc/usb_cdc_pstn.c
SOURCES += $(USB_ROOTDIR)/usb_core/device/sources/classes/cdc/usb_cdc.c

#-----------------------------------------------------------
# 'usb_core_device_sources_class_driver_common' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/device/sources/classes/common/usb_class.c

#-----------------------------------------------------------
# 'usb_core_device_sources_class_driver_composite' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/device/sources/classes/composite/usb_composite.c

#-----------------------------------------------------------
# 'usb_core_device_sources_class_driver_hid' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/device/sources/classes/hid/usb_hid.c

#-----------------------------------------------------------
# 'usb_core_device_sources_class_driver_msd' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/device/sources/classes/msd/usb_msc_scsi.c
SOURCES += $(USB_ROOTDIR)/usb_core/device/sources/classes/msd/usb_msc.c

#-----------------------------------------------------------
# 'usb_core_device_sources_class_driver_phdc' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/device/sources/classes/phdc/usb_phdc.c

#-----------------------------------------------------------
# 'usb_core_device_sources_controller_driver' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/device/sources/controller/usb_dev.c
SOURCES += $(USB_ROOTDIR)/usb_core/device/sources/controller/usb_framework.c

#-----------------------------------------------------------
# 'usb_core_device_sources_controller_driver_khci' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/device/sources/controller/khci/khci_dev.c
SOURCES += $(USB_ROOTDIR)/usb_core/device/sources/controller/khci/device_khci_interface.c


#----------------------------------------------------------
# include partial makefiles
#----------------------------------------------------------
include $(USB_ROOTDIR)/build/common/make/global.mak
-include $(USB_ROOTDIR)/build/$(BOARD)/make/tools/$(TOOL).mak
include $(USB_ROOTDIR)/build/common/make/verify.mak
include $(USB_ROOTDIR)/build/common/make/lib-process.mak
#----------------------------------------------------------
