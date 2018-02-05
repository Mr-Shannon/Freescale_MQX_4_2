#-----------------------------------------------------------
# libraries
#-----------------------------------------------------------

LIBRARIES_NODEPS += $(LIBRARY_ROOTDIR)/$(CONFIG)/bsp/bsp.lib(vectors.o)
LIBRARIES_NODEPS += $(LIBRARY_ROOTDIR)/$(CONFIG)/psp/psp.lib(linker_symbols.o)
RT_PATHS += $(TOOLCHAIN_ROOTDIR)/ARM/ARMCC/lib/
INCLUDE += $(TOOLCHAIN_ROOTDIR)/ARM/ARMCC/include






