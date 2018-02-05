#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
INCLUDE += $(MQX_ROOTDIR)/mqx/source/psp/cortex_m/compiler/gcc_cw
INCLUDE += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/EWL_C/include
INCLUDE += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/EWL_Runtime/include
endif
ifeq ($(CONFIG),release)
INCLUDE += $(MQX_ROOTDIR)/mqx/source/psp/cortex_m/compiler/gcc_cw
INCLUDE += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/EWL_C/include
INCLUDE += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/EWL_Runtime/include
endif


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/cortex_m/compiler/gcc_cw/comp.c


#-----------------------------------------------------------
# 'debug' configuration settings
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
AS_FLAGS += -fmessage-length=0 -c 
AS_DEFINE += MQX_DISABLE_CONFIG_CHECK=1 
CC_DEFINE += MQX_DISABLE_CONFIG_CHECK=1 
CX_DEFINE += MQX_DISABLE_CONFIG_CHECK=1 
endif
#-----------------------------------------------------------
# 'release' configuration settings
#-----------------------------------------------------------
ifeq ($(CONFIG),release)
AS_FLAGS += -fmessage-length=0 -c 
AS_DEFINE += MQX_DISABLE_CONFIG_CHECK=1 
CC_DEFINE += MQX_DISABLE_CONFIG_CHECK=1 
CX_DEFINE += MQX_DISABLE_CONFIG_CHECK=1 
endif


