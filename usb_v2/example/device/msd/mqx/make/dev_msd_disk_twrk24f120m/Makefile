#----------------------------------------------------------
# setup required variables 
#----------------------------------------------------------
USB_ROOTDIR         = $(abspath ../../../../../..)
MQX_ROOTDIR             = $(USB_ROOTDIR)/..
LIBRARY_ROOTDIR         = $(MQX_ROOTDIR)/lib/$(BOARD).$(TOOL)
APPLICATION_DIR     = ./$(TOOL)/$(LOADNAME)_$(CONFIG)
APPLICATION_FILE    = $(APPLICATION_DIR)/$(NAME)_$(BOARD).$(APPLICATION_EXT)
LINKER_FILE         = $(call GET_BSP_LINKER_FILE)
TYPE                = application
NAME                = dev_msd_disk
BOARD               = twrk24f120m


#-----------------------------------------------------------
# load tool settings
#-----------------------------------------------------------
include tools/$(TOOL).mak


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
INCLUDE += $(USB_ROOTDIR)/example/device/msd
INCLUDE += $(USB_ROOTDIR)/example/device/msd/mqx
endif
ifeq ($(CONFIG),release)
INCLUDE += $(USB_ROOTDIR)/example/device/msd
INCLUDE += $(USB_ROOTDIR)/example/device/msd/mqx
endif



#-----------------------------------------------------------
# common 'app' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/example/device/msd/disk.c
SOURCES += $(USB_ROOTDIR)/example/device/msd/mqx/sd.c
SOURCES += $(USB_ROOTDIR)/example/device/msd/usb_descriptor.c



#----------------------------------------------------------
# include partial makefiles
#----------------------------------------------------------
include $(USB_ROOTDIR)/build/common/make/global.mak
-include $(USB_ROOTDIR)/build/$(BOARD)/make/tools/$(TOOL).mak
include $(USB_ROOTDIR)/build/common/make/verify.mak
include $(USB_ROOTDIR)/build/common/make/app-process.mak
#----------------------------------------------------------
