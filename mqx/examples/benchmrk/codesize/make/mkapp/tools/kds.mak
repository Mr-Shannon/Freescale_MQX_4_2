#-----------------------------------------------------------
# libraries
#-----------------------------------------------------------

LIBRARIES += $(TOOLCHAIN_ROOTDIR)/toolchain/lib/gcc/arm-none-eabi/$(GCC_VERSION)/m4/libgcc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/toolchain/arm-none-eabi/lib/m4/libc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/toolchain/arm-none-eabi/lib/m4/libsupc++.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/toolchain/arm-none-eabi/lib/m4/libm.a

#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------

INCLUDE += $(TOOLCHAIN_ROOTDIR)/toolchain/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include
INCLUDE += $(TOOLCHAIN_ROOTDIR)/toolchain/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include-fixed
INCLUDE += $(TOOLCHAIN_ROOTDIR)/toolchain/arm-none-eabi/include




