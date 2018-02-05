#-----------------------------------------------------------
# libraries
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk40d100m.gcc_arm/debug/bsp/bsp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk40d100m.gcc_arm/debug/psp/psp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk40d100m.gcc_arm/debug/mfs/mfs.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk40d100m.gcc_arm/debug/shell/shell.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/armv7e-m/libgcc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7e-m/libc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7e-m/libsupc++.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7e-m/libm.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7e-m/libnosys.a
endif
ifeq ($(CONFIG),release)
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk40d100m.gcc_arm/release/bsp/bsp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk40d100m.gcc_arm/release/psp/psp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk40d100m.gcc_arm/release/mfs/mfs.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk40d100m.gcc_arm/release/shell/shell.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/armv7e-m/libgcc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7e-m/libc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7e-m/libsupc++.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7e-m/libm.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7e-m/libnosys.a
endif


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
INCLUDE += $(MQX_ROOTDIR)/lib/twrk40d100m.gcc_arm/debug/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/twrk40d100m.gcc_arm/debug
INCLUDE += $(MQX_ROOTDIR)/lib/twrk40d100m.gcc_arm/debug/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk40d100m.gcc_arm/debug/psp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk40d100m.gcc_arm/debug/mfs
INCLUDE += $(MQX_ROOTDIR)/lib/twrk40d100m.gcc_arm/debug/shell
INCLUDE += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include
INCLUDE += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include-fixed
INCLUDE += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/include
endif
ifeq ($(CONFIG),release)
INCLUDE += $(MQX_ROOTDIR)/lib/twrk40d100m.gcc_arm/release/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/twrk40d100m.gcc_arm/release
INCLUDE += $(MQX_ROOTDIR)/lib/twrk40d100m.gcc_arm/release/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk40d100m.gcc_arm/release/psp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk40d100m.gcc_arm/release/mfs
INCLUDE += $(MQX_ROOTDIR)/lib/twrk40d100m.gcc_arm/release/shell
INCLUDE += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include
INCLUDE += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include-fixed
INCLUDE += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/include
endif






