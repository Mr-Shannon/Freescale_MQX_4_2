#-----------------------------------------------------------
# libraries
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk65f180m.iar/debug/bsp/bsp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk65f180m.iar/debug/psp/psp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk65f180m.iar/debug/rtcs/rtcs.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk65f180m.iar/debug/shell/shell.a
endif
ifeq ($(CONFIG),release)
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk65f180m.iar/release/bsp/bsp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk65f180m.iar/release/psp/psp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk65f180m.iar/release/rtcs/rtcs.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk65f180m.iar/release/shell/shell.a
endif


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
INCLUDE += $(MQX_ROOTDIR)/lib/twrk65f180m.iar/debug/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/twrk65f180m.iar/debug
INCLUDE += $(MQX_ROOTDIR)/lib/twrk65f180m.iar/debug/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk65f180m.iar/debug/psp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk65f180m.iar/debug/rtcs
INCLUDE += $(MQX_ROOTDIR)/lib/twrk65f180m.iar/debug/shell
endif
ifeq ($(CONFIG),release)
INCLUDE += $(MQX_ROOTDIR)/lib/twrk65f180m.iar/release/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/twrk65f180m.iar/release
INCLUDE += $(MQX_ROOTDIR)/lib/twrk65f180m.iar/release/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk65f180m.iar/release/psp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk65f180m.iar/release/rtcs
INCLUDE += $(MQX_ROOTDIR)/lib/twrk65f180m.iar/release/shell
endif





