#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
INCLUDE += $(MQX_ROOTDIR)/mqx/source/psp/cortex_m/compiler/rv_uv4
INCLUDE += $(TOOLCHAIN_ROOTDIR)/ARM/ARMCC/include
endif
ifeq ($(CONFIG),release)
INCLUDE += $(MQX_ROOTDIR)/mqx/source/psp/cortex_m/compiler/rv_uv4
INCLUDE += $(TOOLCHAIN_ROOTDIR)/ARM/ARMCC/include
endif


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/cortex_m/compiler/rv_uv4/comp.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/cortex_m/compiler/rv_uv4/linker_symbols.S


#-----------------------------------------------------------
# 'debug' configuration settings
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
AS_DEFINE += MQX_DISABLE_CONFIG_CHECK=1 
CC_DEFINE += MQX_DISABLE_CONFIG_CHECK=1 
CX_DEFINE += MQX_DISABLE_CONFIG_CHECK=1 
endif
#-----------------------------------------------------------
# 'release' configuration settings
#-----------------------------------------------------------
ifeq ($(CONFIG),release)
AS_DEFINE += MQX_DISABLE_CONFIG_CHECK=1 
CC_DEFINE += MQX_DISABLE_CONFIG_CHECK=1 
CX_DEFINE += MQX_DISABLE_CONFIG_CHECK=1 
endif


