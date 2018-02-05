#------------------------------------------------------------
# use specific TOOLCHAIN_ROOTDIR if not set in global.mak
#------------------------------------------------------------
#TOOLCHAIN_ROOTDIR = C:/PROGRA~1/IARSYS~1/EMBEDD~1.0

#------------------------------------------------------------
# toolchain settings for windows
#
# XX_PROCESS macros:
# $(1) - output file path
# $(2) - list of object files
# $(3) - file contains list of object files
#------------------------------------------------------------
ifeq ($(HOSTENV),WINDOWS)

AS = $(TOOLCHAIN_ROOTDIR)/ARM/BIN/iasmarm.exe 
CC = $(TOOLCHAIN_ROOTDIR)/ARM/BIN/iccarm.exe 
CX = $(TOOLCHAIN_ROOTDIR)/ARM/BIN/iccarm.exe 
AR = $(TOOLCHAIN_ROOTDIR)/ARM/BIN/iarchive.exe 
LD = $(TOOLCHAIN_ROOTDIR)/ARM/BIN/ilinkarm.exe 

AS_PROCESS = $(AS) $(2) -o $(1) $(AS_FLAGS) $(addprefix -D,$(AS_DEFINE)) $(addprefix -I,$(INCLUDE)) $(addprefix -I,$(RT_INCLUDE)) 
CC_PROCESS = $(CC) $(2) -o $(1) $(CC_FLAGS) $(addprefix -D,$(CC_DEFINE)) $(addprefix -I,$(INCLUDE)) $(addprefix -I,$(RT_INCLUDE)) --dependencies=m $(DEPENDS_DIR)
CX_PROCESS = $(CX) $(2) -o $(1) $(CX_FLAGS) $(addprefix -D,$(CX_DEFINE)) $(addprefix -I,$(INCLUDE)) $(addprefix -I,$(RT_INCLUDE)) --dependencies=m $(DEPENDS_DIR)
AR_PROCESS = $(AR) $(AR_FLAGS) --create -f $(3) -o $(1)
LD_PROCESS = $(LD) --map $(basename $(1)).map $(LIBRARIES) $(LD_FLAGS) --config $(LINKER_FILE) -f $(3) -o $(1)

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
$(error "no iar settings for unix")
endif


#------------------------------------------------------------
# tool extensions 
#------------------------------------------------------------
LIBRARY_EXT     = a
APPLICATION_EXT = out


#------------------------------------------------------------
# libraries tool options 
#------------------------------------------------------------
ifeq ($(TYPE),library)

# common settings
AS_FLAGS += --cpu Cortex-A5.neon --fpu VFPv4 -s -M'<>' -w+ -r -j -S 
CC_FLAGS += --cpu=Cortex-A5.neon --fpu=VFPv4 --diag_suppress Pa082,Pe186 --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa --no_clustering --no_scheduling --endian=little -e --use_c++_inline --silent --vla --debug 
CX_FLAGS += --cpu=Cortex-A5.neon --fpu=VFPv4 --diag_suppress Pa082,Pe186 --no_cse --no_unroll --no_code_motion --no_tbaa --no_clustering --no_scheduling --endian=little -e --c++ --silent --debug 


ifeq ($(CONFIG),debug)
CC_FLAGS += -On 
CX_FLAGS += -On 
AS_DEFINE += _DEBUG=1 
CC_DEFINE += _DEBUG=1 
CX_DEFINE += _DEBUG=1 
endif
ifeq ($(CONFIG),release)
CC_FLAGS += -Oh 
CX_FLAGS += -Oh 
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
AS_FLAGS += --cpu Cortex-A5.neon --fpu VFPv4 -s -M'<>' -w+ -r -j -S 
CC_FLAGS += --cpu=Cortex-A5.neon --fpu=VFPv4 --diag_suppress Pa082,Pe186 --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa --no_clustering --no_scheduling --endian=little -e --use_c++_inline --silent --vla --debug 
CX_FLAGS += --cpu=Cortex-A5.neon --fpu=VFPv4 --diag_suppress Pa082,Pe186 --no_cse --no_unroll --no_code_motion --no_tbaa --no_clustering --no_scheduling --endian=little -e --c++ --silent --debug 
LD_FLAGS += --entry __boot --redirect __iar_dlmalloc=malloc --redirect __iar_dlcalloc=calloc --redirect __iar_dlfree=free 


ifeq ($(CONFIG),debug)
CC_FLAGS += -On 
CX_FLAGS += -On 
AS_DEFINE += _DEBUG=1 
CC_DEFINE += _DEBUG=1 
CX_DEFINE += _DEBUG=1 
endif
ifeq ($(CONFIG),release)
CC_FLAGS += -Oh 
CX_FLAGS += -Oh 
AS_DEFINE += NDEBUG=1 
CC_DEFINE += NDEBUG=1 
CX_DEFINE += NDEBUG=1 
endif

endif






