#----------------------------------------------------------
# setup required variables 
#----------------------------------------------------------
MQX_ROOTDIR         = $(abspath ../../../../..)
LIBRARY_ROOTDIR     = $(MQX_ROOTDIR)/lib/$(BOARD).$(TOOL)
APPLICATION_DIR     = ./$(TOOL)/$(LOADNAME)_$(CONFIG)
APPLICATION_FILE    = $(APPLICATION_DIR)/$(NAME)_$(BOARD).$(APPLICATION_EXT)
LINKER_FILE         = $(call GET_BSP_LINKER_FILE)
TYPE                = application
NAME                = web_hvac_v2
BOARD               = svf522revb_a5


#-----------------------------------------------------------
# load tool settings
#-----------------------------------------------------------
-include tools/$(TOOL).mak


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
INCLUDE += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include
INCLUDE += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include-fixed
INCLUDE += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/include
INCLUDE += $(MQX_ROOTDIR)/demo/web_hvac_v2

SOURCES += $(MQX_ROOTDIR)/demo/web_hvac_v2/command_lists.c
SOURCES += $(MQX_ROOTDIR)/demo/web_hvac_v2/hvac_io.c
SOURCES += $(MQX_ROOTDIR)/demo/web_hvac_v2/hvac_shell_commands.c
SOURCES += $(MQX_ROOTDIR)/demo/web_hvac_v2/hvac_task.c
SOURCES += $(MQX_ROOTDIR)/demo/web_hvac_v2/hvac_util.c
SOURCES += $(MQX_ROOTDIR)/demo/web_hvac_v2/logging_task.c
SOURCES += $(MQX_ROOTDIR)/demo/web_hvac_v2/rtcs.c
SOURCES += $(MQX_ROOTDIR)/demo/web_hvac_v2/shell_task.c
SOURCES += $(MQX_ROOTDIR)/demo/web_hvac_v2/switch_task.c
SOURCES += $(MQX_ROOTDIR)/demo/web_hvac_v2/tasks.c
SOURCES += $(MQX_ROOTDIR)/demo/web_hvac_v2/usb_file.c
SOURCES += $(MQX_ROOTDIR)/demo/web_hvac_v2/usb_task.c
SOURCES += $(MQX_ROOTDIR)/demo/web_hvac_v2/cgi_hvac.c
SOURCES += $(MQX_ROOTDIR)/demo/web_hvac_v2/cgi_index.c
SOURCES += $(MQX_ROOTDIR)/demo/web_hvac_v2/tfs_data.c
SOURCES += $(MQX_ROOTDIR)/demo/web_hvac_v2/usbmfs.c


#----------------------------------------------------------
# include partial makefiles
#----------------------------------------------------------
include $(MQX_ROOTDIR)/build/common/make/global.mak
-include $(MQX_ROOTDIR)/build/$(BOARD)/make/tools/$(TOOL).mak
include $(MQX_ROOTDIR)/build/common/make/verify.mak
include $(MQX_ROOTDIR)/build/common/make/app-process.mak
#----------------------------------------------------------
