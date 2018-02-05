#-----------------------------------------------------------
# libraries
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
LIBRARIES += $(MQX_ROOTDIR)/lib/svf522revb_a5.gcc_arm/debug/bsp/bsp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/svf522revb_a5.gcc_arm/debug/psp/psp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/svf522revb_a5.gcc_arm/debug/mcc/mcc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/armv7-ar/thumb/fpu/libgcc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7-ar/thumb/fpu/libc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7-ar/thumb/fpu/libsupc++.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7-ar/thumb/fpu/libm.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7-ar/thumb/fpu/libnosys.a
endif
ifeq ($(CONFIG),release)
LIBRARIES += $(MQX_ROOTDIR)/lib/svf522revb_a5.gcc_arm/release/bsp/bsp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/svf522revb_a5.gcc_arm/release/psp/psp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/svf522revb_a5.gcc_arm/release/mcc/mcc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/armv7-ar/thumb/fpu/libgcc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7-ar/thumb/fpu/libc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7-ar/thumb/fpu/libsupc++.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7-ar/thumb/fpu/libm.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7-ar/thumb/fpu/libnosys.a
endif


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
INCLUDE += $(MQX_ROOTDIR)/lib/svf522revb_a5.gcc_arm/debug
INCLUDE += $(MQX_ROOTDIR)/lib/svf522revb_a5.gcc_arm/debug/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/svf522revb_a5.gcc_arm/debug/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/svf522revb_a5.gcc_arm/debug/psp
INCLUDE += $(MQX_ROOTDIR)/lib/svf522revb_a5.gcc_arm/debug/mcc
INCLUDE += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include
INCLUDE += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include-fixed
INCLUDE += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/include
endif
ifeq ($(CONFIG),release)
INCLUDE += $(MQX_ROOTDIR)/lib/svf522revb_a5.gcc_arm/release
INCLUDE += $(MQX_ROOTDIR)/lib/svf522revb_a5.gcc_arm/release/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/svf522revb_a5.gcc_arm/release/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/svf522revb_a5.gcc_arm/release/psp
INCLUDE += $(MQX_ROOTDIR)/lib/svf522revb_a5.gcc_arm/release/mcc
INCLUDE += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include
INCLUDE += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include-fixed
INCLUDE += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/include
endif






