#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
endif
ifeq ($(CONFIG),release)
endif




#-----------------------------------------------------------
# 'debug' configuration settings
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
AS_FLAGS += -prefix $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_regabi.h 
CC_FLAGS += -prefix $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_regabi.h 
CX_FLAGS += -prefix $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_regabi.h 
endif
#-----------------------------------------------------------
# 'release' configuration settings
#-----------------------------------------------------------
ifeq ($(CONFIG),release)
AS_FLAGS += -prefix $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_regabi.h 
CC_FLAGS += -prefix $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_regabi.h 
CX_FLAGS += -prefix $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_regabi.h 
endif


