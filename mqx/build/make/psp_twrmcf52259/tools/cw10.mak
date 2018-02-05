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
AS_DEFINE += MQX_DISABLE_CONFIG_CHECK=1 
CC_DEFINE += MQX_DISABLE_CONFIG_CHECK=1 
CX_DEFINE += MQX_DISABLE_CONFIG_CHECK=1 
endif
#-----------------------------------------------------------
# 'release' configuration settings
#-----------------------------------------------------------
ifeq ($(CONFIG),release)
AS_FLAGS += -prefix $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_regabi.h 
CC_FLAGS += -prefix $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_regabi.h 
CX_FLAGS += -prefix $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_regabi.h 
AS_DEFINE += MQX_DISABLE_CONFIG_CHECK=1 
CC_DEFINE += MQX_DISABLE_CONFIG_CHECK=1 
CX_DEFINE += MQX_DISABLE_CONFIG_CHECK=1 
endif


