#----------------------------------------------------------
# setup variables
#----------------------------------------------------------
USB_ROOTDIR            = $(abspath ../../../../..)
OS                     = mqx
#-----------------------------------------------
# set board infomation
#-----------------------------------------------

TYPE                    = library
NAME                    = usbotg_mqx
BOARD                   = twrk64f120m
MQX_ROOTDIR             = $(USB_ROOTDIR)/..
LIBRARY_ROOTDIR         = $(MQX_ROOTDIR)/lib/$(BOARD).$(TOOL)
USB_LIBRARY_ROOTDIR     = $(USB_ROOTDIR)/output/$(BOARD).$(TOOL)
LIBRARY_DIR             = $(USB_LIBRARY_ROOTDIR)/$(CONFIG)/usbotg/mqx
LIBRARY_FILE            = $(LIBRARY_DIR)/libusbotg_mqx.$(LIBRARY_EXT)
POSTBUILD_CMD           = $(if $(findstring $(HOSTENV),WINDOWS),$(USB_ROOTDIR)/usb_core/otg/build/bat/usbotg_twrk64f120m.bat $(USB_ROOTDIR) $(LIBRARY_DIR) $(TOOL) mqx,$(USB_ROOTDIR)/usb_core/otg/build/bat/usbotg_twrk64f120m.sh $(USB_ROOTDIR) $(LIBRARY_DIR) $(TOOL) mqx)


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
INCLUDE += $(USB_ROOTDIR)/usb_core/device/include/twrk64f120m
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
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/audio
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/cdc
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/hid
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/hub
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/msd
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/phdc
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/controller
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/controller/khci
INCLUDE += $(USB_ROOTDIR)/usb_core/host/include/twrk64f120m
INCLUDE += $(USB_ROOTDIR)/usb_core/host/include
INCLUDE += $(USB_ROOTDIR)/usb_core/include
INCLUDE += $(USB_ROOTDIR)/usb_core/otg/sources/include
INCLUDE += $(USB_ROOTDIR)/usb_core/otg/sources/driver
INCLUDE += $(USB_ROOTDIR)/usb_core/otg/sources/driver/khci
INCLUDE += $(USB_ROOTDIR)/usb_core/otg/sources/driver/max3353
INCLUDE += $(USB_ROOTDIR)/usb_core/otg/sources/otg
endif
ifeq ($(CONFIG),release)
INCLUDE += $(USB_ROOTDIR)/adapter/sources
INCLUDE += $(USB_ROOTDIR)/adapter/sources/mqx
INCLUDE += $(USB_ROOTDIR)/usb_core/hal
INCLUDE += $(USB_ROOTDIR)/usb_core/device/include/twrk64f120m
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
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/audio
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/cdc
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/hid
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/hub
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/msd
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/classes/phdc
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/controller
INCLUDE += $(USB_ROOTDIR)/usb_core/host/sources/controller/khci
INCLUDE += $(USB_ROOTDIR)/usb_core/host/include/twrk64f120m
INCLUDE += $(USB_ROOTDIR)/usb_core/host/include
INCLUDE += $(USB_ROOTDIR)/usb_core/include
INCLUDE += $(USB_ROOTDIR)/usb_core/otg/sources/include
INCLUDE += $(USB_ROOTDIR)/usb_core/otg/sources/driver
INCLUDE += $(USB_ROOTDIR)/usb_core/otg/sources/driver/khci
INCLUDE += $(USB_ROOTDIR)/usb_core/otg/sources/driver/max3353
INCLUDE += $(USB_ROOTDIR)/usb_core/otg/sources/otg
endif



#-----------------------------------------------------------
# 'adapter' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/adapter/sources/mqx/adapter_mqx.c

#-----------------------------------------------------------
# 'usb_core_device_sources_bsp' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/device/sources/bsp/twrk64f120m/usb_dev_bsp.c

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
# 'usb_core_host_controller_driver_khci' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/controller/khci/khci.c
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/controller/khci/host_khci_interface.c

#-----------------------------------------------------------
# 'usb_core_host_sources_bsp' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/host/sources/bsp/twrk64f120m/usb_host_bsp.c

#-----------------------------------------------------------
# 'usb_core_otg_sources_bsp' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/otg/sources/bsp/twrk64f120m/usb_otg_bsp.c

#-----------------------------------------------------------
# 'usb_core_otg_sources_driver' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/otg/sources/driver/usb_otg.c

#-----------------------------------------------------------
# 'usb_core_otg_sources_driver_khci' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/otg/sources/driver/khci/usb_otg_khci.c

#-----------------------------------------------------------
# 'usb_core_otg_sources_driver_max3353' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/otg/sources/driver/max3353/mqx/usb_otg_max3353.c
SOURCES += $(USB_ROOTDIR)/usb_core/otg/sources/driver/max3353/max3353_interface.c

#-----------------------------------------------------------
# 'usb_core_otg_sources_otg' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/usb_core/otg/sources/otg/usb_otg_main.c
SOURCES += $(USB_ROOTDIR)/usb_core/otg/sources/otg/usb_otg_sm_a.c
SOURCES += $(USB_ROOTDIR)/usb_core/otg/sources/otg/usb_otg_sm_b.c
SOURCES += $(USB_ROOTDIR)/usb_core/otg/sources/otg/usb_otg_sm_main.c


#----------------------------------------------------------
# include partial makefiles
#----------------------------------------------------------
include $(USB_ROOTDIR)/build/common/make/global.mak
-include $(USB_ROOTDIR)/build/$(BOARD)/make/tools/$(TOOL).mak
include $(USB_ROOTDIR)/build/common/make/verify.mak
include $(USB_ROOTDIR)/build/common/make/lib-process.mak
#----------------------------------------------------------
