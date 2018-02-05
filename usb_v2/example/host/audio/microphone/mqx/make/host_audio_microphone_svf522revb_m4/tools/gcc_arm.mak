#-----------------------------------------------------------
# libraries
#-----------------------------------------------------------
ifeq ($(CONFIG),release)
LIBRARIES += $(USB_ROOTDIR)/output/svf522revb_m4.gcc_arm/release/usbh/mqx/libusbh_mqx.a
LIBRARIES += $(USB_ROOTDIR)/../lib/svf522revb_m4.gcc_arm/release/bsp/bsp.a
LIBRARIES += $(USB_ROOTDIR)/../lib/svf522revb_m4.gcc_arm/release/psp/psp.a
LIBRARIES += $(USB_ROOTDIR)/../lib/svf522revb_m4.gcc_arm/release/mfs/mfs.a
LIBRARIES += $(USB_ROOTDIR)/../lib/svf522revb_m4.gcc_arm/release/shell/shell.a
endif


#-----------------------------------------------------------
# runtime libraries
#-----------------------------------------------------------
ifeq ($(CONFIG),release)
RT_LIBRARIES += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/armv7e-m/fpu/libgcc.a
RT_LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7e-m/fpu/libc.a
RT_LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7e-m/fpu/libsupc++.a
RT_LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7e-m/fpu/libm.a
RT_LIBRARIES += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/lib/armv7e-m/fpu/libnosys.a
endif


#-----------------------------------------------------------
# runtime library paths
#-----------------------------------------------------------


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),release)
INCLUDE += $(USB_ROOTDIR)/output/svf522revb_m4.gcc_arm/release/usbh/mqx
INCLUDE += $(USB_ROOTDIR)/../lib/svf522revb_m4.gcc_arm/release/bsp/Generated_Code
INCLUDE += $(USB_ROOTDIR)/../lib/svf522revb_m4.gcc_arm/release/bsp/Sources
INCLUDE += $(USB_ROOTDIR)/../lib/svf522revb_m4.gcc_arm/release
INCLUDE += $(USB_ROOTDIR)/../lib/svf522revb_m4.gcc_arm/release/bsp
INCLUDE += $(USB_ROOTDIR)/../lib/svf522revb_m4.gcc_arm/release/psp
INCLUDE += $(USB_ROOTDIR)/../lib/svf522revb_m4.gcc_arm/release/mfs
INCLUDE += $(USB_ROOTDIR)/../lib/svf522revb_m4.gcc_arm/release/shell
endif


#-----------------------------------------------------------
# runtime search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),release)
RT_INCLUDE += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include-fixed
RT_INCLUDE += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include
RT_INCLUDE += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/include
endif





