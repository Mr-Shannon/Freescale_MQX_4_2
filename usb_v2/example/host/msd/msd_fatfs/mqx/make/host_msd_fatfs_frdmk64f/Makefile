#----------------------------------------------------------
# setup required variables 
#----------------------------------------------------------
USB_ROOTDIR         = $(abspath ../../../../../../..)
MQX_ROOTDIR             = $(USB_ROOTDIR)/..
LIBRARY_ROOTDIR         = $(MQX_ROOTDIR)/lib/$(BOARD).$(TOOL)
APPLICATION_DIR     = ./$(TOOL)/$(LOADNAME)_$(CONFIG)
APPLICATION_FILE    = $(APPLICATION_DIR)/$(NAME)_$(BOARD).$(APPLICATION_EXT)
LINKER_FILE         = $(call GET_BSP_LINKER_FILE)
TYPE                = application
NAME                = host_msd_fatfs
BOARD               = frdmk64f


#-----------------------------------------------------------
# load tool settings
#-----------------------------------------------------------
include tools/$(TOOL).mak


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
INCLUDE += $(USB_ROOTDIR)/example/host/msd/msd_fatfs/mqx
INCLUDE += $(USB_ROOTDIR)/example/host/msd/msd_fatfs/mqx/mfs
endif
ifeq ($(CONFIG),release)
INCLUDE += $(USB_ROOTDIR)/example/host/msd/msd_fatfs/mqx
INCLUDE += $(USB_ROOTDIR)/example/host/msd/msd_fatfs/mqx/mfs
endif



#-----------------------------------------------------------
# common 'app' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/example/host/msd/msd_fatfs/main.c
SOURCES += $(USB_ROOTDIR)/example/host/msd/msd_fatfs/mqx/command_lists.c
SOURCES += $(USB_ROOTDIR)/example/host/msd/msd_fatfs/mqx/msd_mfs_demo.c
SOURCES += $(USB_ROOTDIR)/example/host/msd/msd_fatfs/mqx/shell_task.c
SOURCES += $(USB_ROOTDIR)/example/host/msd/msd_fatfs/mqx/usb_file.c

#-----------------------------------------------------------
# common 'app_mfs' sources
#-----------------------------------------------------------
SOURCES += $(USB_ROOTDIR)/example/host/msd/msd_fatfs/mqx/mfs/usbmfs.c



#----------------------------------------------------------
# include partial makefiles
#----------------------------------------------------------
include $(USB_ROOTDIR)/build/common/make/global.mak
-include $(USB_ROOTDIR)/build/$(BOARD)/make/tools/$(TOOL).mak
include $(USB_ROOTDIR)/build/common/make/verify.mak
include $(USB_ROOTDIR)/build/common/make/app-process.mak
#----------------------------------------------------------
