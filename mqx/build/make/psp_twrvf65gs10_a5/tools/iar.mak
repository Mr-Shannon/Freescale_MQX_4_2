#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
INCLUDE += $(MQX_ROOTDIR)/mqx/source/psp/cortex_a/compiler/iar
endif
ifeq ($(CONFIG),release)
INCLUDE += $(MQX_ROOTDIR)/mqx/source/psp/cortex_a/compiler/iar
endif


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/cortex_a/compiler/iar/comp.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/cortex_a/compiler/iar/kernel_symbols.S


#-----------------------------------------------------------
# 'debug' configuration settings
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
AS_DEFINE += PSP_HAS_SUPPORT_STRUCT=1 MQX_DISABLE_CONFIG_CHECK=1 
CC_DEFINE += PSP_HAS_SUPPORT_STRUCT=1 MQX_DISABLE_CONFIG_CHECK=1 
CX_DEFINE += PSP_HAS_SUPPORT_STRUCT=1 MQX_DISABLE_CONFIG_CHECK=1 
endif
#-----------------------------------------------------------
# 'release' configuration settings
#-----------------------------------------------------------
ifeq ($(CONFIG),release)
AS_DEFINE += PSP_HAS_SUPPORT_STRUCT=1 MQX_DISABLE_CONFIG_CHECK=1 
CC_DEFINE += PSP_HAS_SUPPORT_STRUCT=1 MQX_DISABLE_CONFIG_CHECK=1 
CX_DEFINE += PSP_HAS_SUPPORT_STRUCT=1 MQX_DISABLE_CONFIG_CHECK=1 
endif


