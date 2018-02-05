#-----------------------------------------------------------
# libraries
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk60d100m.kds/debug/bsp/bsp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk60d100m.kds/debug/psp/psp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk60d100m.kds/debug/mfs/mfs.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk60d100m.kds/debug/shell/shell.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/toolchain/lib/gcc/arm-none-eabi/$(GCC_VERSION)/armv7e-m/libgcc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/toolchain/arm-none-eabi/lib/armv7e-m/libc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/toolchain/arm-none-eabi/lib/armv7e-m/libsupc++.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/toolchain/arm-none-eabi/lib/armv7e-m/libm.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/toolchain/arm-none-eabi/lib/armv7e-m/libnosys.a
endif
ifeq ($(CONFIG),release)
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk60d100m.kds/release/bsp/bsp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk60d100m.kds/release/psp/psp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk60d100m.kds/release/mfs/mfs.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk60d100m.kds/release/shell/shell.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/toolchain/lib/gcc/arm-none-eabi/$(GCC_VERSION)/armv7e-m/libgcc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/toolchain/arm-none-eabi/lib/armv7e-m/libc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/toolchain/arm-none-eabi/lib/armv7e-m/libsupc++.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/toolchain/arm-none-eabi/lib/armv7e-m/libm.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/toolchain/arm-none-eabi/lib/armv7e-m/libnosys.a
endif


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
INCLUDE += $(MQX_ROOTDIR)/lib/twrk60d100m.kds/debug/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/twrk60d100m.kds/debug
INCLUDE += $(MQX_ROOTDIR)/lib/twrk60d100m.kds/debug/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk60d100m.kds/debug/psp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk60d100m.kds/debug/mfs
INCLUDE += $(MQX_ROOTDIR)/lib/twrk60d100m.kds/debug/shell
INCLUDE += $(TOOLCHAIN_ROOTDIR)/toolchain/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include
INCLUDE += $(TOOLCHAIN_ROOTDIR)/toolchain/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include-fixed
INCLUDE += $(TOOLCHAIN_ROOTDIR)/toolchain/arm-none-eabi/include
endif
ifeq ($(CONFIG),release)
INCLUDE += $(MQX_ROOTDIR)/lib/twrk60d100m.kds/release/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/twrk60d100m.kds/release
INCLUDE += $(MQX_ROOTDIR)/lib/twrk60d100m.kds/release/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk60d100m.kds/release/psp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk60d100m.kds/release/mfs
INCLUDE += $(MQX_ROOTDIR)/lib/twrk60d100m.kds/release/shell
INCLUDE += $(TOOLCHAIN_ROOTDIR)/toolchain/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include
INCLUDE += $(TOOLCHAIN_ROOTDIR)/toolchain/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include-fixed
INCLUDE += $(TOOLCHAIN_ROOTDIR)/toolchain/arm-none-eabi/include
endif






