#----------------------------------------------------------
# setup required variables 
#----------------------------------------------------------
MQX_ROOTDIR         = $(abspath ../../../../../..)
LIBRARY_ROOTDIR     = $(MQX_ROOTDIR)/lib/$(BOARD).$(TOOL)
APPLICATION_DIR     = ./$(TOOL)/$(LOADNAME)_$(CONFIG)
APPLICATION_FILE    = $(APPLICATION_DIR)/$(NAME)_$(BOARD).$(APPLICATION_EXT)
LINKER_FILE         = $(call GET_BSP_LINKER_FILE)
TYPE                = application
NAME                = iperf
BOARD               = twrk65f180m


#-----------------------------------------------------------
# load tool settings
#-----------------------------------------------------------
-include tools/$(TOOL).mak


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
INCLUDE += $(MQX_ROOTDIR)/rtcs/examples/iperf

SOURCES += $(MQX_ROOTDIR)/rtcs/examples/iperf/iperf.c
SOURCES += $(MQX_ROOTDIR)/rtcs/examples/iperf/iperf_api.c
SOURCES += $(MQX_ROOTDIR)/rtcs/examples/iperf/iperf_client_api.c
SOURCES += $(MQX_ROOTDIR)/rtcs/examples/iperf/iperf_error.c
SOURCES += $(MQX_ROOTDIR)/rtcs/examples/iperf/iperf_server_api.c
SOURCES += $(MQX_ROOTDIR)/rtcs/examples/iperf/iperf_tcp.c
SOURCES += $(MQX_ROOTDIR)/rtcs/examples/iperf/iperf_udp.c
SOURCES += $(MQX_ROOTDIR)/rtcs/examples/iperf/iperf_util.c
SOURCES += $(MQX_ROOTDIR)/rtcs/examples/iperf/ilocale.c
SOURCES += $(MQX_ROOTDIR)/rtcs/examples/iperf/main.c
SOURCES += $(MQX_ROOTDIR)/rtcs/examples/iperf/net.c
SOURCES += $(MQX_ROOTDIR)/rtcs/examples/iperf/itimer.c
SOURCES += $(MQX_ROOTDIR)/rtcs/examples/iperf/units.c


#----------------------------------------------------------
# include partial makefiles
#----------------------------------------------------------
include $(MQX_ROOTDIR)/build/common/make/global.mak
-include $(MQX_ROOTDIR)/build/$(BOARD)/make/tools/$(TOOL).mak
include $(MQX_ROOTDIR)/build/common/make/verify.mak
include $(MQX_ROOTDIR)/build/common/make/app-process.mak
#----------------------------------------------------------
