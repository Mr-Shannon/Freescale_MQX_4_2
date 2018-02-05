#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
INCLUDE += $(MQX_ROOTDIR)/mqx/source/psp/cortex_m/compiler/gcc_cw
INCLUDE += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/EWL_C/include
INCLUDE += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/EWL_Runtime/include
endif
ifeq ($(CONFIG),release)
INCLUDE += $(MQX_ROOTDIR)/mqx/source/psp/cortex_m/compiler/gcc_cw
INCLUDE += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/EWL_C/include
INCLUDE += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/EWL_Runtime/include
endif




#-----------------------------------------------------------
# 'debug' configuration settings
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
AS_FLAGS += -fmessage-length=0 -c 
endif
#-----------------------------------------------------------
# 'release' configuration settings
#-----------------------------------------------------------
ifeq ($(CONFIG),release)
AS_FLAGS += -fmessage-length=0 -c 
endif


