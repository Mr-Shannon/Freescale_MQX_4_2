#------------------------------------------------------------
# use specific TOOLCHAIN_ROOTDIR if not set in global.mak
#------------------------------------------------------------
#TOOLCHAIN_ROOTDIR = C:/FREESC~1/KDS_1.0
GCC_VERSION ?=4.8.4


#------------------------------------------------------------
# toolchain settings for windows
#
# XX_PROCESS macros:
# $(1) - output file path
# $(2) - list of object files
# $(3) - file contains list of object files
#------------------------------------------------------------
ifeq ($(HOSTENV),WINDOWS)

AS = $(TOOLCHAIN_ROOTDIR)/toolchain/bin/arm-none-eabi-gcc.exe 
CC = $(TOOLCHAIN_ROOTDIR)/toolchain/bin/arm-none-eabi-gcc.exe 
CX = $(TOOLCHAIN_ROOTDIR)/toolchain/bin/arm-none-eabi-gcc.exe 
AR = $(TOOLCHAIN_ROOTDIR)/toolchain/bin/arm-none-eabi-ar.exe 
LD = $(TOOLCHAIN_ROOTDIR)/toolchain/bin/arm-none-eabi-gcc.exe 

AS_PROCESS = $(AS) $(AS_FLAGS) $(addprefix -D,$(AS_DEFINE)) $(addprefix -I,$(INCLUDE)) $(addprefix -I,$(RT_INCLUDE)) -c $(2) -o $(1) 
CC_PROCESS = $(CC) $(CC_FLAGS) $(addprefix -D,$(CC_DEFINE)) $(addprefix -I,$(INCLUDE)) $(addprefix -I,$(RT_INCLUDE)) -MD -MF $(DEPENDS_DIR)/$(notdir $(basename $(1))).d -c $(2) -o $(1) 
CX_PROCESS = $(CX) $(CX_FLAGS) $(addprefix -D,$(CX_DEFINE)) $(addprefix -I,$(INCLUDE)) $(addprefix -I,$(RT_INCLUDE)) -MD -MF $(DEPENDS_DIR)/$(notdir $(basename $(1))).d -c $(2) -o $(1) 
AR_PROCESS = $(call SED,s/\\/\//g <$(3) >$(3)2) & $(AR) $(AR_FLAGS) -r $(1) @"$(3)2" 
LD_PROCESS = $(call SED,s/\\/\//g <$(3) >$(3)2) & $(LD) $(LD_FLAGS) @"$(3)2" -T$(LINKER_FILE) -o $(1) \
-Xlinker -Map=$(basename $(1)).map \
-Xlinker --start-group \
$(LIBRARIES) $(RT_LIBRARIES) \
-Xlinker --end-group \

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

AS = $(TOOLCHAIN_ROOTDIR)/toolchain/bin/arm-none-eabi-gcc 
CC = $(TOOLCHAIN_ROOTDIR)/toolchain/bin/arm-none-eabi-gcc 
CX = $(TOOLCHAIN_ROOTDIR)/toolchain/bin/arm-none-eabi-gcc 
AR = $(TOOLCHAIN_ROOTDIR)/toolchain/bin/arm-none-eabi-ar 
LD = $(TOOLCHAIN_ROOTDIR)/toolchain/bin/arm-none-eabi-gcc 

AS_PROCESS = $(AS) $(AS_FLAGS) $(addprefix -D,$(AS_DEFINE)) $(addprefix -I,$(INCLUDE)) $(addprefix -I,$(RT_INCLUDE)) -c $(2) -o $(1) 
CC_PROCESS = $(CC) $(CC_FLAGS) $(addprefix -D,$(CC_DEFINE)) $(addprefix -I,$(INCLUDE)) $(addprefix -I,$(RT_INCLUDE)) -MD -MF $(DEPENDS_DIR)/$(notdir $(basename $(1))).d -c $(2) -o $(1) 
CX_PROCESS = $(CC) $(CX_FLAGS) $(addprefix -D,$(CX_DEFINE)) $(addprefix -I,$(INCLUDE)) $(addprefix -I,$(RT_INCLUDE)) -MD -MF $(DEPENDS_DIR)/$(notdir $(basename $(1))).d -c $(2) -o $(1) 
AR_PROCESS = $(AR) $(AR_FLAGS) -r $(1) @"$(3)" 
LD_PROCESS = $(LD) $(LD_FLAGS) @"$(3)" -T$(LINKER_FILE) -o $(1) \
-Xlinker -Map=$(basename $(1)).map \
-Xlinker --start-group \
$(LIBRARIES) $(RT_LIBRARIES) \
-Xlinker --end-group \

endif


#------------------------------------------------------------
# tool extensions 
#------------------------------------------------------------
LIBRARY_EXT     = a
APPLICATION_EXT = elf


#------------------------------------------------------------
# libraries tool options 
#------------------------------------------------------------
ifeq ($(TYPE),library)

# common settings
AS_FLAGS += -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Xassembler --no-warn -std=gnu99 -Wall -mthumb -gdwarf-2 -gstrict-dwarf -g2 
CC_FLAGS += -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fno-strict-aliasing -Wno-missing-braces -std=gnu99 -nostdinc -ffunction-sections -fdata-sections -Wall -mthumb -gdwarf-2 -gstrict-dwarf -g2 
CX_FLAGS += -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fno-strict-aliasing -Wno-missing-braces -nostdinc -nostdinc++ -fno-exceptions -ffunction-sections -fdata-sections -Wall -mthumb -gdwarf-2 -gstrict-dwarf -g2 
CC_DEFINE += _AEABI_LC_CTYPE=C __STRICT_ANSI__=1 
CX_DEFINE += _AEABI_LC_CTYPE=C __STRICT_ANSI__=1 


ifeq ($(CONFIG),debug)
CC_FLAGS += -O0 
CX_FLAGS += -O0 
AS_DEFINE += _DEBUG=1 
CC_DEFINE += _DEBUG=1 
CX_DEFINE += _DEBUG=1 
endif
ifeq ($(CONFIG),release)
CC_FLAGS += -Os 
CX_FLAGS += -Os 
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
AS_FLAGS += -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Xassembler --no-warn -std=gnu99 -Wall -mthumb -gdwarf-2 -gstrict-dwarf -g2 
CC_FLAGS += -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fno-strict-aliasing -Wno-missing-braces -std=gnu99 -nostdinc -ffunction-sections -fdata-sections -Wall -mthumb -gdwarf-2 -gstrict-dwarf -g2 
CX_FLAGS += -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fno-strict-aliasing -Wno-missing-braces -nostdinc -nostdinc++ -fno-exceptions -ffunction-sections -fdata-sections -Wall -mthumb -gdwarf-2 -gstrict-dwarf -g2 
LD_FLAGS += -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=gnu99 -nostartfiles -nodefaultlibs -nostdlib -Xlinker --gc-sections -Xlinker -cref -Xlinker -static -mthumb -gdwarf-2 -gstrict-dwarf -Xlinker -z -Xlinker muldefs -g2 
CC_DEFINE += _AEABI_LC_CTYPE=C __STRICT_ANSI__=1 
CX_DEFINE += _AEABI_LC_CTYPE=C __STRICT_ANSI__=1 


ifeq ($(CONFIG),debug)
CC_FLAGS += -O0 
CX_FLAGS += -O0 
AS_DEFINE += _DEBUG=1 
CC_DEFINE += _DEBUG=1 
CX_DEFINE += _DEBUG=1 
endif
ifeq ($(CONFIG),release)
CC_FLAGS += -Os 
CX_FLAGS += -Os 
AS_DEFINE += NDEBUG=1 
CC_DEFINE += NDEBUG=1 
CX_DEFINE += NDEBUG=1 
endif

endif






