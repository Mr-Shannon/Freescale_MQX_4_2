#----------------------------------------------------------
# setup required variables 
#----------------------------------------------------------
MQX_ROOTDIR         = $(abspath ../../../../../..)
LIBRARY_ROOTDIR     = $(MQX_ROOTDIR)/lib/$(BOARD).$(TOOL)
APPLICATION_DIR     = ./$(TOOL)/$(LOADNAME)_$(CONFIG)
APPLICATION_FILE    = $(APPLICATION_DIR)/$(NAME)_$(BOARD).$(APPLICATION_EXT)
LINKER_FILE         = $(call GET_BSP_LINKER_FILE)
TYPE                = application
NAME                = httpsrv
BOARD               = twrmcf52259


#-----------------------------------------------------------
# load tool settings
#-----------------------------------------------------------
-include tools/$(TOOL).mak


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
INCLUDE += $(TOOLCHAIN_ROOTDIR)/MCU/ColdFire_Support/ewl/EWL_C/include
INCLUDE += $(MQX_ROOTDIR)/rtcs/examples/httpsrv

SOURCES += $(MQX_ROOTDIR)/rtcs/examples/httpsrv/cgi.c
SOURCES += $(MQX_ROOTDIR)/rtcs/examples/httpsrv/httpsrv_main.c
SOURCES += $(MQX_ROOTDIR)/rtcs/examples/httpsrv/tfs_data.c
SOURCES += $(MQX_ROOTDIR)/rtcs/examples/httpsrv/example_plugins.c


#----------------------------------------------------------
# include partial makefiles
#----------------------------------------------------------
include $(MQX_ROOTDIR)/build/common/make/global.mak
-include $(MQX_ROOTDIR)/build/$(BOARD)/make/tools/$(TOOL).mak
include $(MQX_ROOTDIR)/build/common/make/verify.mak
include $(MQX_ROOTDIR)/build/common/make/app-process.mak
#----------------------------------------------------------
