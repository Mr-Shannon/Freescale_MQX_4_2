#----------------------------------------------------------
# setup required variables 
#----------------------------------------------------------
MQX_ROOTDIR         = $(abspath ../../../../../..)
LIBRARY_ROOTDIR     = $(MQX_ROOTDIR)/lib/$(BOARD).$(TOOL)
APPLICATION_DIR     = ./$(TOOL)/$(LOADNAME)_$(CONFIG)
APPLICATION_FILE    = $(APPLICATION_DIR)/$(NAME)_$(BOARD).$(APPLICATION_EXT)
LINKER_FILE         = $(call GET_BSP_LINKER_FILE)
TYPE                = application
NAME                = sai_dma_demo
BOARD               = twrk65f180m


#-----------------------------------------------------------
# load tool settings
#-----------------------------------------------------------
-include tools/$(TOOL).mak


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
INCLUDE += $(MQX_ROOTDIR)/mqx/examples/sai_dma_demo

SOURCES += $(MQX_ROOTDIR)/mqx/examples/sai_dma_demo/log_messages.c
SOURCES += $(MQX_ROOTDIR)/mqx/examples/sai_dma_demo/main.c
SOURCES += $(MQX_ROOTDIR)/mqx/examples/sai_dma_demo/sgtl5000.c
SOURCES += $(MQX_ROOTDIR)/mqx/examples/sai_dma_demo/sh_audio.c
SOURCES += $(MQX_ROOTDIR)/mqx/examples/sai_dma_demo/wav.c


#----------------------------------------------------------
# include partial makefiles
#----------------------------------------------------------
include $(MQX_ROOTDIR)/build/common/make/global.mak
-include $(MQX_ROOTDIR)/build/$(BOARD)/make/tools/$(TOOL).mak
include $(MQX_ROOTDIR)/build/common/make/verify.mak
include $(MQX_ROOTDIR)/build/common/make/app-process.mak
#----------------------------------------------------------
