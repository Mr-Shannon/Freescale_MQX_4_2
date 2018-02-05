#----------------------------------------------------------
# setup required variables 
#----------------------------------------------------------
MQX_ROOTDIR         = $(abspath ../../../../../..)
LIBRARY_ROOTDIR     = $(MQX_ROOTDIR)/lib/$(BOARD).$(TOOL)
APPLICATION_DIR     = ./$(TOOL)/$(LOADNAME)_$(CONFIG)
APPLICATION_FILE    = $(APPLICATION_DIR)/$(NAME)_$(BOARD).$(APPLICATION_EXT)
LINKER_FILE         = $(call GET_BSP_LINKER_FILE)
TYPE                = application
NAME                = sem
BOARD               = svf522revb_a5


#-----------------------------------------------------------
# load tool settings
#-----------------------------------------------------------
-include tools/$(TOOL).mak


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
INCLUDE += $(MQX_ROOTDIR)/mqx/examples/sem

SOURCES += $(MQX_ROOTDIR)/mqx/examples/sem/main.c
SOURCES += $(MQX_ROOTDIR)/mqx/examples/sem/read.c
SOURCES += $(MQX_ROOTDIR)/mqx/examples/sem/ttl.c
SOURCES += $(MQX_ROOTDIR)/mqx/examples/sem/write.c


#----------------------------------------------------------
# include partial makefiles
#----------------------------------------------------------
include $(MQX_ROOTDIR)/build/common/make/global.mak
-include $(MQX_ROOTDIR)/build/$(BOARD)/make/tools/$(TOOL).mak
include $(MQX_ROOTDIR)/build/common/make/verify.mak
include $(MQX_ROOTDIR)/build/common/make/app-process.mak
#----------------------------------------------------------
