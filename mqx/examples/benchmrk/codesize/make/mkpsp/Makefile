# root directory
override MQX_ROOTDIR = $(abspath ../../../../../..)

# libraries are built to an alternate folder
override LIBRARY_ROOTDIR = $(MQX_ROOTDIR)/mqx/examples/benchmrk/codesize/output/lib/$(BOARD).$(MAPFMT)/$(CODESIZE_CFG)

# the first include search path for our own user_config.h
INCLUDE += $(MQX_ROOTDIR)/mqx/examples/benchmrk/codesize/config/$(CODESIZE_CFG)

# default configuration for codesize benchmark
CONFIG = release

ifneq ($(TOOLCHAIN_DIR),)
TOOLCHAIN_ROOTDIR = $(TOOLCHAIN_DIR)
endif

# master makefile
-include $(MQX_ROOTDIR)/mqx/build/make/psp_$(BOARD)/tools/$(TOOL).mak
-include $(MQX_ROOTDIR)/mqx/build/make/psp_$(BOARD)/Makefile