#------------------------------------------------------------
# use specific TOOLCHAIN_ROOTDIR if not set in global.mak
#------------------------------------------------------------
#TOOLCHAIN_ROOTDIR = C:/PROGRA~1/FREESC~1/CWMCUV~1.1

#------------------------------------------------------------
# toolchain settings for windows
#
# XX_PROCESS macros:
# $(1) - output file path
# $(2) - list of object files
# $(3) - file contains list of object files
#------------------------------------------------------------
ifeq ($(HOSTENV),WINDOWS)

AS = $(TOOLCHAIN_ROOTDIR)/MCU/ColdFire_Tools/Command_Line_Tools/mwasmmcf.exe 
CC = $(TOOLCHAIN_ROOTDIR)/MCU/ColdFire_Tools/Command_Line_Tools/mwccmcf.exe 
CX = $(TOOLCHAIN_ROOTDIR)/MCU/ColdFire_Tools/Command_Line_Tools/mwccmcf.exe 
AR = $(TOOLCHAIN_ROOTDIR)/MCU/ColdFire_Tools/Command_Line_Tools/mwldmcf.exe 
LD = $(TOOLCHAIN_ROOTDIR)/MCU/ColdFire_Tools/Command_Line_Tools/mwldmcf.exe 

AS_PROCESS = $(AS) $(2) -o $(1) $(AS_FLAGS) $(addprefix -D,$(AS_DEFINE)) $(addprefix -I,$(INCLUDE)) $(addprefix -I,$(RT_INCLUDE)) 
CC_PROCESS = $(CC) $(2) -o $(1) $(CC_FLAGS) $(addprefix -D,$(CC_DEFINE)) $(addprefix -I,$(INCLUDE)) $(addprefix -I,$(RT_INCLUDE)) -MDfile $(DEPENDS_DIR)/$(notdir $(basename $(1))).d 
CX_PROCESS = $(CX) $(2) -o $(1) $(CX_FLAGS) $(addprefix -D,$(CX_DEFINE)) $(addprefix -I,$(INCLUDE)) $(addprefix -I,$(RT_INCLUDE)) -MDfile $(DEPENDS_DIR)/$(notdir $(basename $(1))).d 
AR_PROCESS = $(AR) $(AR_FLAGS) -library @"$(3)" -o $(1) 
LD_PROCESS = $(LD) $(LD_FLAGS) -application @"$(3)" \
$(LIBRARIES) \
$(addprefix -L,$(RT_PATHS)) \
$(addprefix -l,$(RT_LIBRARIES)) \
$(LINKER_FILE) -o $(1) 

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
$(error "no cw10 settings for unix")
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
AS_FLAGS += -proc 51JF -sym full -msgstyle parseable -nosyspath 
CC_FLAGS += -proc 51JF -fp soft -char unsigned -sym full -msgstyle parseable -nostdinc -nosyspath -enc ascii -opt space -inline on -align coldfire -model farCode -model farData -a6 -nocoloring -sdata 0 -Cpp_Exceptions off -RTTI off -enum int -str nopool -str reuse -ipa off -lang c99 -warn illpragmas -warn unwanted -warn missingreturn -warn extracomma -warn emptydecl -requireprotos -noscheduling -nopeephole 
CX_FLAGS += -proc 51JF -fp soft -char unsigned -sym full -msgstyle parseable -nostdinc -nosyspath -enc ascii -opt space -inline on -align coldfire -model farCode -model farData -a6 -nocoloring -sdata 0 -Cpp_Exceptions off -RTTI off -enum int -str nopool -str reuse -ipa off -lang c++ -warn illpragmas -warn unwanted -warn missingreturn -warn extracomma -warn emptydecl -requireprotos -noscheduling -nopeephole 
AR_FLAGS += -proc 51JF -library -sym full -msgstyle parseable -nostdlib -map -srec -sreclength 80 -sreceol dos -keep off -w on 
AS_DEFINE += _EWL_C99=1 _EMBEDDED_WARRIOR_CTYPE=0 _EWL_FLOATING_POINT=1 __CODEWARRIOR__=1 
CC_DEFINE += _EWL_C99=1 _EMBEDDED_WARRIOR_CTYPE=0 _EWL_FLOATING_POINT=1 __CODEWARRIOR__=1 
CX_DEFINE += _EWL_C99=1 _EMBEDDED_WARRIOR_CTYPE=0 _EWL_FLOATING_POINT=1 __CODEWARRIOR__=1 


ifeq ($(CONFIG),debug)
CC_FLAGS += -opt level=0 
CX_FLAGS += -opt level=0 
AS_DEFINE += _DEBUG=1 
CC_DEFINE += _DEBUG=1 
CX_DEFINE += _DEBUG=1 
endif
ifeq ($(CONFIG),release)
CC_FLAGS += -opt level=4 
CX_FLAGS += -opt level=4 
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
AS_FLAGS += -proc 51JF -sym full -msgstyle parseable -nosyspath 
CC_FLAGS += -proc 51JF -fp soft -char unsigned -sym full -msgstyle parseable -nostdinc -nosyspath -enc ascii -opt space -inline on -align coldfire -model farCode -model farData -a6 -nocoloring -sdata 0 -Cpp_Exceptions off -RTTI off -enum int -str nopool -str reuse -ipa off -lang c99 -warn illpragmas -warn unwanted -warn missingreturn -warn extracomma -warn emptydecl -requireprotos -noscheduling -nopeephole 
CX_FLAGS += -proc 51JF -fp soft -char unsigned -sym full -msgstyle parseable -nostdinc -nosyspath -enc ascii -opt space -inline on -align coldfire -model farCode -model farData -a6 -nocoloring -sdata 0 -Cpp_Exceptions off -RTTI off -enum int -str nopool -str reuse -ipa off -lang c++ -warn illpragmas -warn unwanted -warn missingreturn -warn extracomma -warn emptydecl -requireprotos -noscheduling -nopeephole 
LD_FLAGS += -proc 51JF -sym full -msgstyle parseable -lavender model=c9x ,print=int ,scan=int ,io=raw -nostdlib -m ___boot -map -map closure -srec -sreclength 80 -sreceol dos -w off 
AS_DEFINE += _EWL_C99=1 _EMBEDDED_WARRIOR_CTYPE=0 _EWL_FLOATING_POINT=1 __CODEWARRIOR__=1 
CC_DEFINE += _EWL_C99=1 _EMBEDDED_WARRIOR_CTYPE=0 _EWL_FLOATING_POINT=1 __CODEWARRIOR__=1 
CX_DEFINE += _EWL_C99=1 _EMBEDDED_WARRIOR_CTYPE=0 _EWL_FLOATING_POINT=1 __CODEWARRIOR__=1 


ifeq ($(CONFIG),debug)
CC_FLAGS += -opt level=0 
CX_FLAGS += -opt level=0 
AS_DEFINE += _DEBUG=1 
CC_DEFINE += _DEBUG=1 
CX_DEFINE += _DEBUG=1 
endif
ifeq ($(CONFIG),release)
CC_FLAGS += -opt level=4 
CX_FLAGS += -opt level=4 
AS_DEFINE += NDEBUG=1 
CC_DEFINE += NDEBUG=1 
CX_DEFINE += NDEBUG=1 
endif

endif






