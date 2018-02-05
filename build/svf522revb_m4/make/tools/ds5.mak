#------------------------------------------------------------
# use specific TOOLCHAIN_ROOTDIR if not set in global.mak
#------------------------------------------------------------
#TOOLCHAIN_ROOTDIR = C:/PROGRA~1/DS-5

#------------------------------------------------------------
# toolchain settings for windows
#
# XX_PROCESS macros:
# $(1) - output file path
# $(2) - list of object files
# $(3) - file contains list of object files
#------------------------------------------------------------
ifeq ($(HOSTENV),WINDOWS)

AS = $(TOOLCHAIN_ROOTDIR)/sw/ARMCompiler5.05u1/bin/armasm.exe 
CC = $(TOOLCHAIN_ROOTDIR)/sw/ARMCompiler5.05u1/bin/armcc.exe 
CX = $(TOOLCHAIN_ROOTDIR)/sw/ARMCompiler5.05u1/bin/armcc.exe 
AR = $(TOOLCHAIN_ROOTDIR)/sw/ARMCompiler5.05u1/bin/armar.exe 
LD = $(TOOLCHAIN_ROOTDIR)/sw/ARMCompiler5.05u1/bin/armlink.exe 

AS_PROCESS = $(AS) $(AS_FLAGS) --cpreproc_opts='$(addprefix -D,$(AS_DEFINE))' $(addprefix -I,$(INCLUDE)) $(addprefix -I,$(RT_INCLUDE)) $(2) -o $(1) 
CC_PROCESS = $(CC) $(CC_FLAGS) $(addprefix -D,$(CC_DEFINE)) $(addprefix -I,$(INCLUDE)) $(addprefix -I,$(RT_INCLUDE)) -c $(2) -o $(1) 
CX_PROCESS = $(CX) $(CX_FLAGS) $(addprefix -D,$(CX_DEFINE)) $(addprefix -I,$(INCLUDE)) $(addprefix -I,$(RT_INCLUDE)) -c $(2) -o $(1) 
AR_PROCESS = $(AR) $(AR_FLAGS) -r $(1) --via=$(3) 
LD_PROCESS = $(LD) $(LD_FLAGS) --list=$(basename $(1)).map --via=$(3) \
--scatter=$(LINKER_FILE) \
$(addprefix --libpath=,$(RT_PATHS)) \
$(LIBRARIES) $(LIBRARIES_NODEPS)\
-o $(1) 

endif


#------------------------------------------------------------
# toolchain settings for unix
#
# XX_PROCESS macros:
# $(1) - output file path
# $(2) - list of object files
# $(3) - file contains list of object files
#------------------------------------------------------------
ifeq ($(HOSTENV),UNIX)

AS = $(TOOLCHAIN_ROOTDIR)/sw/ARMCompiler5.05u1/bin/armasm 
CC = $(TOOLCHAIN_ROOTDIR)/sw/ARMCompiler5.05u1/bin/armcc 
CX = $(TOOLCHAIN_ROOTDIR)/sw/ARMCompiler5.05u1/bin/armcc 
AR = $(TOOLCHAIN_ROOTDIR)/sw/ARMCompiler5.05u1/bin/armar 
LD = $(TOOLCHAIN_ROOTDIR)/sw/ARMCompiler5.05u1/bin/armlink 

AS_PROCESS = $(AS) $(AS_FLAGS) --cpreproc_opts='$(addprefix -D,$(AS_DEFINE))' $(addprefix -I,$(INCLUDE)) $(addprefix -I,$(RT_INCLUDE)) $(2) -o $(1) 
CC_PROCESS = $(CC) $(CC_FLAGS) $(addprefix -D,$(CC_DEFINE)) $(addprefix -I,$(INCLUDE)) $(addprefix -I,$(RT_INCLUDE)) -c $(2) -o $(1) 
CX_PROCESS = $(CX) $(CX_FLAGS) $(addprefix -D,$(CX_DEFINE)) $(addprefix -I,$(INCLUDE)) $(addprefix -I,$(RT_INCLUDE)) -c $(2) -o $(1) 
AR_PROCESS = $(AR) $(AR_FLAGS) -r $(1) --via=$(3) 
LD_PROCESS = $(LD) $(LD_FLAGS) --list=$(basename $(1)).map --via=$(3) \
--scatter=$(LINKER_FILE) \
$(addprefix --libpath=,$(RT_PATHS)) \
$(LIBRARIES) $(LIBRARIES_NODEPS)\
-o $(1) 

endif

#------------------------------------------------------------
# tool extensions 
#------------------------------------------------------------
LIBRARY_EXT     = a
APPLICATION_EXT = axf


#------------------------------------------------------------
# libraries tool options 
#------------------------------------------------------------
ifeq ($(TYPE),library)

# common settings
AS_FLAGS += --cpu=Cortex-M4 --fpu=FPv4-SP --cpreproc --apcs=/interwork -g 
CC_FLAGS += --cpu=Cortex-M4 --fpu=FPv4-SP --diag_suppress=1296,186 --c99 --thumb --apcs=/interwork -g 
CX_FLAGS += --cpu=Cortex-M4 --fpu=FPv4-SP --diag_suppress=1296,186,368 --cpp --thumb --apcs=/interwork -g 


ifeq ($(CONFIG),debug)
CC_FLAGS += -O0 
CX_FLAGS += -O0 
AS_DEFINE += _DEBUG=1 
CC_DEFINE += _DEBUG=1 
CX_DEFINE += _DEBUG=1 
endif
ifeq ($(CONFIG),release)
CC_FLAGS += -O3 
CX_FLAGS += -O3 
AS_DEFINE += NDEBUG=1 
CC_DEFINE += NDEBUG=1 
CX_DEFINE += NDEBUG=1 
endif
endif


#------------------------------------------------------------
# application tool options 
#------------------------------------------------------------
ifeq ($(TYPE),application)

# common settings
AS_FLAGS += --cpu=Cortex-M4 --fpu=FPv4-SP --cpreproc --apcs=/interwork -g 
CC_FLAGS += --cpu=Cortex-M4 --fpu=FPv4-SP --diag_suppress=1296,186 --c99 --thumb --apcs=/interwork -g 
CX_FLAGS += --cpu=Cortex-M4 --fpu=FPv4-SP --diag_suppress=1296,186,368 --cpp --thumb --apcs=/interwork -g 
LD_FLAGS += --cpu=Cortex-M4 --fpu=FPv4-SP --keep linker_symbols.o(KERNEL_DATA_START) --keep linker_symbols.o(KERNEL_DATA_END) --keep linker_symbols.o(BOOT_STACK) --keep vectors.o(.vectors_rom) --diag_suppress=6314,6329 --info debug,sizes,totals,unused,veneers --map --symbols --entry __boot --debug 


ifeq ($(CONFIG),debug)
CC_FLAGS += -O0 
CX_FLAGS += -O0 
AS_DEFINE += _DEBUG=1 
CC_DEFINE += _DEBUG=1 
CX_DEFINE += _DEBUG=1 
endif
ifeq ($(CONFIG),release)
CC_FLAGS += -O3 
CX_FLAGS += -O3 
AS_DEFINE += NDEBUG=1 
CC_DEFINE += NDEBUG=1 
CX_DEFINE += NDEBUG=1 
endif

endif






