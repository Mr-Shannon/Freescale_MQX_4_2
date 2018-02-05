#-----------------------------------------------------------
# libraries
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk70f120m.uv4/debug/bsp/bsp.lib
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk70f120m.uv4/debug/psp/psp.lib
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk70f120m.uv4/debug/rtcs/rtcs.lib
LIBRARIES_NODEPS += $(MQX_ROOTDIR)/lib/twrk70f120m.uv4/debug/bsp/bsp.lib(vectors.o)
LIBRARIES_NODEPS += $(MQX_ROOTDIR)/lib/twrk70f120m.uv4/debug/psp/psp.lib(linker_symbols.o)
RT_PATHS += $(TOOLCHAIN_ROOTDIR)/ARM/ARMCC/lib/
endif
ifeq ($(CONFIG),release)
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk70f120m.uv4/release/bsp/bsp.lib
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk70f120m.uv4/release/psp/psp.lib
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk70f120m.uv4/release/rtcs/rtcs.lib
LIBRARIES_NODEPS += $(MQX_ROOTDIR)/lib/twrk70f120m.uv4/release/bsp/bsp.lib(vectors.o)
LIBRARIES_NODEPS += $(MQX_ROOTDIR)/lib/twrk70f120m.uv4/release/psp/psp.lib(linker_symbols.o)
RT_PATHS += $(TOOLCHAIN_ROOTDIR)/ARM/ARMCC/lib/
endif


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.uv4/debug/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.uv4/debug
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.uv4/debug/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.uv4/debug/psp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.uv4/debug/rtcs
INCLUDE += $(TOOLCHAIN_ROOTDIR)/ARM/ARMCC/include
endif
ifeq ($(CONFIG),release)
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.uv4/release/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.uv4/release
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.uv4/release/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.uv4/release/psp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.uv4/release/rtcs
INCLUDE += $(TOOLCHAIN_ROOTDIR)/ARM/ARMCC/include
endif






