#-----------------------------------------------------------
# libraries
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
LIBRARIES += $(MQX_ROOTDIR)/lib/twrvf65gs10_a5.iar/debug/bsp/bsp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrvf65gs10_a5.iar/debug/psp/psp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrvf65gs10_a5.iar/debug/mfs/mfs.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrvf65gs10_a5.iar/debug/shell/shell.a
endif
ifeq ($(CONFIG),release)
LIBRARIES += $(MQX_ROOTDIR)/lib/twrvf65gs10_a5.iar/release/bsp/bsp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrvf65gs10_a5.iar/release/psp/psp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrvf65gs10_a5.iar/release/mfs/mfs.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrvf65gs10_a5.iar/release/shell/shell.a
endif


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
INCLUDE += $(MQX_ROOTDIR)/lib/twrvf65gs10_a5.iar/debug/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/twrvf65gs10_a5.iar/debug
INCLUDE += $(MQX_ROOTDIR)/lib/twrvf65gs10_a5.iar/debug/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/twrvf65gs10_a5.iar/debug/psp
INCLUDE += $(MQX_ROOTDIR)/lib/twrvf65gs10_a5.iar/debug/mfs
INCLUDE += $(MQX_ROOTDIR)/lib/twrvf65gs10_a5.iar/debug/shell
endif
ifeq ($(CONFIG),release)
INCLUDE += $(MQX_ROOTDIR)/lib/twrvf65gs10_a5.iar/release/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/twrvf65gs10_a5.iar/release
INCLUDE += $(MQX_ROOTDIR)/lib/twrvf65gs10_a5.iar/release/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/twrvf65gs10_a5.iar/release/psp
INCLUDE += $(MQX_ROOTDIR)/lib/twrvf65gs10_a5.iar/release/mfs
INCLUDE += $(MQX_ROOTDIR)/lib/twrvf65gs10_a5.iar/release/shell
endif






