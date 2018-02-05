#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
INCLUDE += $(MQX_ROOTDIR)/mqx/source/psp/cortex_m/compiler/rv_ds5
INCLUDE += $(TOOLCHAIN_ROOTDIR)/include
endif
ifeq ($(CONFIG),release)
INCLUDE += $(MQX_ROOTDIR)/mqx/source/psp/cortex_m/compiler/rv_ds5
INCLUDE += $(TOOLCHAIN_ROOTDIR)/include
endif






