#----------------------------------------------------------
# setup variables
#----------------------------------------------------------
USB_ROOTDIR            = $(abspath ../../../../..)
OS                     = mqx
#-----------------------------------------------
# set board infomation
#-----------------------------------------------

TYPE                    = library
NAME                    = usbh_mqx
BOARD                   = twrk65f180m
MQX_ROOTDIR             = $(USB_ROOTDIR)/..
LIBRARY_ROOTDIR         = $(MQX_ROOTDIR)/lib/$(BOARD).$(TOOL)
USB_LIBRARY_ROOTDIR     = $(USB_ROOTDIR)/output/$(BOARD).$(TOOL)
LIBRARY_DIR             = $(USB_LIBRARY_ROOTDIR)/$(CONFIG)/usbh/mqx
LIBRARY_FILE            = $(LIBRARY_DIR)/libusbh_mqx.$(LIBRARY_EXT)
POSTBUILD_CMD           = $(if $(findstring $(HOSTENV),WINDOWS),$(USB_ROOTDIR)/usb_core/host/build/bat/usbh_twrk65f180m.bat $(USB_ROOTDIR) $(LIBRARY_DIR) $(TOOL) mqx,$(USB_ROOTDIR)/usb_core/host/build/bat/usbh_twrk65f180m.sh $(USB_ROOTDIR) $(LIBRARY_DIR) $(TOOL) mqx)


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
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/audio
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/cdc
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/hid
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/hub
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/msd
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/phdc
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/controller
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/controller/ehci
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/controller/khci
INCLUDE += $(USB_ROOTDIR)/usb_core/host/include/twrk65f180m
INCLUDE += $(USB_ROOTDIR)/usb_core/host/include
INCLUDE += $(USB_ROOTDIR)/usb_core/include
endif
ifeq ($(CONFIG),release)
INCLUDE += $(USB_ROOTDIR)/adapter/sources
INCLUDE += $(USB_ROOTDIR)/adapter/sources/mqx
INCLUDE += $(USB_ROOTDIR)/usb_core/hal
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/audio
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/cdc
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/hid
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/hub
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/msd
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/phdc
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/controller
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/controller/ehci
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/controller/khci
INCLUDE += $(USB_ROOTDIR)/usb_core/host/include/twrk65f180m
INCLUDE += $(USB_ROOTDIR)/usb_core/host/include
INCLUDE += $(USB_ROOTDIR)/usb_core/include
endif



#-----------------------------------------------------------
# 'adapter' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/adapter/sources/mqx/adapter_mqx.c

#-----------------------------------------------------------
# 'usb_core_host_class_driver_audio' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/classes/audio/usb_host_audio.c
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/classes/audio/usb_host_audio_intf.c

#-----------------------------------------------------------
# 'usb_core_host_class_driver_cdc' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/classes/cdc/usb_host_cdc.c
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/classes/cdc/usb_host_cdc_intf.c

#-----------------------------------------------------------
# 'usb_core_host_class_driver_common' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/classes/common/usb_classes.c

#-----------------------------------------------------------
# 'usb_core_host_class_driver_hid' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/classes/hid/usb_host_hid.c

#-----------------------------------------------------------
# 'usb_core_host_class_driver_hub' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/classes/hub/usb_host_hub_sm.c
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/classes/hub/usb_host_hub.c

#-----------------------------------------------------------
# 'usb_core_host_class_driver_msd' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/classes/msd/usb_host_msd_bo.c
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/classes/msd/usb_host_msd_queue.c
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/classes/msd/usb_host_msd_ufi.c

#-----------------------------------------------------------
# 'usb_core_host_class_driver_phdc' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/classes/phdc/usb_host_phdc.c

#-----------------------------------------------------------
# 'usb_core_host_controller_driver' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/controller/usb_host_ch9.c
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/controller/usb_host_common.c
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/controller/usb_host_dev_mng.c
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/controller/usb_host.c

#-----------------------------------------------------------
# 'usb_core_host_controller_driver_ehci' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/controller/ehci/ehci_host.c
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/controller/ehci/host_ehci_interface.c

#-----------------------------------------------------------
# 'usb_core_host_controller_driver_khci' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/controller/khci/khci.c
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/controller/khci/host_khci_interface.c

#-----------------------------------------------------------
# 'usb_core_host_sources_bsp' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/bsp/twrk65f180m/usb_host_bsp.c


#----------------------------------------------------------
# include partial makefiles
#----------------------------------------------------------
include $(USB_ROOTDIR)/build/common/make/global.mak
-include $(USB_ROOTDIR)/build/$(BOARD)/make/tools/$(TOOL).mak
include $(USB_ROOTDIR)/build/common/make/verify.mak
include $(USB_ROOTDIR)/build/common/make/lib-process.mak
#----------------------------------------------------------
