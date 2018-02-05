#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
INCLUDE += $(MQX_ROOTDIR)/mqx/source/psp/cortex_m/compiler/rv_uv4
INCLUDE += $(TOOLCHAIN_ROOTDIR)/ARM/ARMCC/include
endif
ifeq ($(CONFIG),release)
INCLUDE += $(MQX_ROOTDIR)/mqx/source/psp/cortex_m/compiler/rv_uv4
INCLUDE += $(TOOLCHAIN_ROOTDIR)/ARM/ARMCC/include
endif






