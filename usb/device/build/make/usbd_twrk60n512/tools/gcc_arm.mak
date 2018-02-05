#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
INCLUDE += $(MQX_ROOTDIR)/mqx/source/psp/cortex_m/compiler/gcc_arm
INCLUDE += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include
INCLUDE += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include-fixed
INCLUDE += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/include
endif
ifeq ($(CONFIG),release)
INCLUDE += $(MQX_ROOTDIR)/mqx/source/psp/cortex_m/compiler/gcc_arm
INCLUDE += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include
INCLUDE += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include-fixed
INCLUDE += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/include
endif






