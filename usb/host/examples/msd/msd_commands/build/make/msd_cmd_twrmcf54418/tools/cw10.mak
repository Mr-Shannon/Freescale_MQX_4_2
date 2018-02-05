#-----------------------------------------------------------
# libraries
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
LIBRARIES += $(MQX_ROOTDIR)/lib/twrmcf54418.cw10/debug/bsp/bsp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrmcf54418.cw10/debug/psp/psp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrmcf54418.cw10/debug/usb/usbh.a
RT_PATHS += $(TOOLCHAIN_ROOTDIR)/MCU/ColdFire_Support/ewl/lib
endif
ifeq ($(CONFIG),release)
LIBRARIES += $(MQX_ROOTDIR)/lib/twrmcf54418.cw10/release/bsp/bsp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrmcf54418.cw10/release/psp/psp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrmcf54418.cw10/release/usb/usbh.a
RT_PATHS += $(TOOLCHAIN_ROOTDIR)/MCU/ColdFire_Support/ewl/lib
endif


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
INCLUDE += $(MQX_ROOTDIR)/lib/twrmcf54418.cw10/debug/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/twrmcf54418.cw10/debug
INCLUDE += $(MQX_ROOTDIR)/lib/twrmcf54418.cw10/debug/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/twrmcf54418.cw10/debug/psp
INCLUDE += $(MQX_ROOTDIR)/lib/twrmcf54418.cw10/debug/usb
endif
ifeq ($(CONFIG),release)
INCLUDE += $(MQX_ROOTDIR)/lib/twrmcf54418.cw10/release/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/twrmcf54418.cw10/release
INCLUDE += $(MQX_ROOTDIR)/lib/twrmcf54418.cw10/release/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/twrmcf54418.cw10/release/psp
INCLUDE += $(MQX_ROOTDIR)/lib/twrmcf54418.cw10/release/usb
endif






