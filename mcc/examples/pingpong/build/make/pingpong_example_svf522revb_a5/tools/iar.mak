#-----------------------------------------------------------
# libraries
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
LIBRARIES += $(MQX_ROOTDIR)/lib/svf522revb_a5.iar/debug/bsp/bsp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/svf522revb_a5.iar/debug/psp/psp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/svf522revb_a5.iar/debug/mcc/mcc.a
endif
ifeq ($(CONFIG),release)
LIBRARIES += $(MQX_ROOTDIR)/lib/svf522revb_a5.iar/release/bsp/bsp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/svf522revb_a5.iar/release/psp/psp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/svf522revb_a5.iar/release/mcc/mcc.a
endif


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
INCLUDE += $(MQX_ROOTDIR)/lib/svf522revb_a5.iar/debug
INCLUDE += $(MQX_ROOTDIR)/lib/svf522revb_a5.iar/debug/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/svf522revb_a5.iar/debug/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/svf522revb_a5.iar/debug/psp
INCLUDE += $(MQX_ROOTDIR)/lib/svf522revb_a5.iar/debug/mcc
endif
ifeq ($(CONFIG),release)
INCLUDE += $(MQX_ROOTDIR)/lib/svf522revb_a5.iar/release
INCLUDE += $(MQX_ROOTDIR)/lib/svf522revb_a5.iar/release/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/svf522revb_a5.iar/release/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/svf522revb_a5.iar/release/psp
INCLUDE += $(MQX_ROOTDIR)/lib/svf522revb_a5.iar/release/mcc
endif






