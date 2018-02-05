#-----------------------------------------------------------
# libraries
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk60n512.kds/debug/bsp/bsp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk60n512.kds/debug/psp/psp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk60n512.kds/debug/usb/usbd.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/toolchain/lib/gcc/arm-none-eabi/$(GCC_VERSION)/armv7e-m/libgcc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/toolchain/arm-none-eabi/lib/armv7e-m/libc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/toolchain/arm-none-eabi/lib/armv7e-m/libsupc++.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/toolchain/arm-none-eabi/lib/armv7e-m/libm.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/toolchain/arm-none-eabi/lib/armv7e-m/libnosys.a
endif
ifeq ($(CONFIG),release)
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk60n512.kds/release/bsp/bsp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk60n512.kds/release/psp/psp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk60n512.kds/release/usb/usbd.a
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
INCLUDE += $(MQX_ROOTDIR)/lib/twrk60n512.kds/debug/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/twrk60n512.kds/debug
INCLUDE += $(MQX_ROOTDIR)/lib/twrk60n512.kds/debug/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk60n512.kds/debug/psp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk60n512.kds/debug/usb
INCLUDE += $(TOOLCHAIN_ROOTDIR)/toolchain/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include
INCLUDE += $(TOOLCHAIN_ROOTDIR)/toolchain/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include-fixed
INCLUDE += $(TOOLCHAIN_ROOTDIR)/toolchain/arm-none-eabi/include
endif
ifeq ($(CONFIG),release)
INCLUDE += $(MQX_ROOTDIR)/lib/twrk60n512.kds/release/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/twrk60n512.kds/release
INCLUDE += $(MQX_ROOTDIR)/lib/twrk60n512.kds/release/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk60n512.kds/release/psp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk60n512.kds/release/usb
INCLUDE += $(TOOLCHAIN_ROOTDIR)/toolchain/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include
INCLUDE += $(TOOLCHAIN_ROOTDIR)/toolchain/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include-fixed
INCLUDE += $(TOOLCHAIN_ROOTDIR)/toolchain/arm-none-eabi/include
endif






