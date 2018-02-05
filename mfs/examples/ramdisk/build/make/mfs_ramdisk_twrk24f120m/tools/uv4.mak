#-----------------------------------------------------------
# libraries
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/debug/bsp/bsp.lib
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/debug/psp/psp.lib
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/debug/mfs/mfs.lib
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/debug/shell/shell.lib
LIBRARIES_NODEPS += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/debug/bsp/bsp.lib(vectors.o)
LIBRARIES_NODEPS += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/debug/psp/psp.lib(linker_symbols.o)
RT_PATHS += $(TOOLCHAIN_ROOTDIR)/ARM/ARMCC/lib/
endif
ifeq ($(CONFIG),release)
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/release/bsp/bsp.lib
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/release/psp/psp.lib
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/release/mfs/mfs.lib
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/release/shell/shell.lib
LIBRARIES_NODEPS += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/release/bsp/bsp.lib(vectors.o)
LIBRARIES_NODEPS += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/release/psp/psp.lib(linker_symbols.o)
RT_PATHS += $(TOOLCHAIN_ROOTDIR)/ARM/ARMCC/lib/
endif


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
INCLUDE += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/debug/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/debug
INCLUDE += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/debug/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/debug/psp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/debug/mfs
INCLUDE += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/debug/shell
INCLUDE += $(TOOLCHAIN_ROOTDIR)/ARM/ARMCC/include
endif
ifeq ($(CONFIG),release)
INCLUDE += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/release/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/release
INCLUDE += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/release/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/release/psp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/release/mfs
INCLUDE += $(MQX_ROOTDIR)/lib/twrk24f120m.uv4/release/shell
INCLUDE += $(TOOLCHAIN_ROOTDIR)/ARM/ARMCC/include
endif






