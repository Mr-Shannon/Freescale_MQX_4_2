#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
INCLUDE += $(MQX_ROOTDIR)/mqx/source/psp/cortex_m/compiler/gcc_arm
INCLUDE += $(TOOLCHAIN_ROOTDIR)/toolchain/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include
INCLUDE += $(TOOLCHAIN_ROOTDIR)/toolchain/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include-fixed
INCLUDE += $(TOOLCHAIN_ROOTDIR)/toolchain/arm-none-eabi/include
endif
ifeq ($(CONFIG),release)
INCLUDE += $(MQX_ROOTDIR)/mqx/source/psp/cortex_m/compiler/gcc_arm
INCLUDE += $(TOOLCHAIN_ROOTDIR)/toolchain/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include
INCLUDE += $(TOOLCHAIN_ROOTDIR)/toolchain/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include-fixed
INCLUDE += $(TOOLCHAIN_ROOTDIR)/toolchain/arm-none-eabi/include
endif


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/cortex_m/compiler/gcc_arm/comp.c


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


