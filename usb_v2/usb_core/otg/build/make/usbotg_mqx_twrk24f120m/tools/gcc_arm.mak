#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
INCLUDE += $(USB_ROOTDIR)/../lib/twrk24f120m.gcc_arm/debug/bsp/Generated_Code
INCLUDE += $(USB_ROOTDIR)/../lib/twrk24f120m.gcc_arm/debug/bsp/Sources
INCLUDE += $(USB_ROOTDIR)/../lib/twrk24f120m.gcc_arm/debug
INCLUDE += $(USB_ROOTDIR)/../lib/twrk24f120m.gcc_arm/debug/bsp
INCLUDE += $(USB_ROOTDIR)/../lib/twrk24f120m.gcc_arm/debug/psp
endif
ifeq ($(CONFIG),release)
INCLUDE += $(USB_ROOTDIR)/../lib/twrk24f120m.gcc_arm/release/bsp/Generated_Code
INCLUDE += $(USB_ROOTDIR)/../lib/twrk24f120m.gcc_arm/release/bsp/Sources
INCLUDE += $(USB_ROOTDIR)/../lib/twrk24f120m.gcc_arm/release
INCLUDE += $(USB_ROOTDIR)/../lib/twrk24f120m.gcc_arm/release/bsp
INCLUDE += $(USB_ROOTDIR)/../lib/twrk24f120m.gcc_arm/release/psp
endif


#-----------------------------------------------------------
# runtime search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
RT_INCLUDE += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include
RT_INCLUDE += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include-fixed
RT_INCLUDE += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/include
endif
ifeq ($(CONFIG),release)
RT_INCLUDE += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include
RT_INCLUDE += $(TOOLCHAIN_ROOTDIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include-fixed
RT_INCLUDE += $(TOOLCHAIN_ROOTDIR)/arm-none-eabi/include
endif




#-----------------------------------------------------------
# 'debug' configuration settings
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
CC_DEFINE += USBCFG_OTG=1 
endif


#-----------------------------------------------------------
# 'release' configuration settings
#-----------------------------------------------------------
ifeq ($(CONFIG),release)
CC_DEFINE += USBCFG_OTG=1 
endif


