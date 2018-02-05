#-----------------------------------------------------------
# libraries
#-----------------------------------------------------------
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/armv7e-m/libgcc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7e-m/libc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7e-m/libsupc++.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7e-m/libm.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7e-m/libnosys.a

#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
INCLUDE += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include
INCLUDE += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include-fixed
INCLUDE += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/include
