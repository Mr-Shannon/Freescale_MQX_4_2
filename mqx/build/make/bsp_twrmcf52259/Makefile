#----------------------------------------------------------
# setup variables
#----------------------------------------------------------
MQX_ROOTDIR             = $(abspath ../../../..)
TYPE                    = library
NAME                    = bsp
BOARD                   = twrmcf52259
LIBRARY_ROOTDIR         = $(MQX_ROOTDIR)/lib/$(BOARD).$(TOOL)
LIBRARY_DIR             = $(LIBRARY_ROOTDIR)/$(CONFIG)/bsp
LIBRARY_FILE            = $(LIBRARY_DIR)/bsp.$(LIBRARY_EXT)
POSTBUILD_CMD           = $(if $(findstring $(HOSTENV),WINDOWS),$(MQX_ROOTDIR)/mqx/build/bat/bsp_twrmcf52259.bat $(MQX_ROOTDIR) $(LIBRARY_DIR) $(TOOL),$(MQX_ROOTDIR)/mqx/build/bat/bsp_twrmcf52259.sh $(MQX_ROOTDIR) $(LIBRARY_DIR) $(TOOL))


#-----------------------------------------------------------
# load tool settings
#-----------------------------------------------------------
-include tools/$(TOOL).mak


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
INCLUDE += $(MQX_ROOTDIR)/mqx/source/psp/coldfire
INCLUDE += $(MQX_ROOTDIR)/config/twrmcf52259
INCLUDE += $(MQX_ROOTDIR)/mqx/source/include
INCLUDE += $(MQX_ROOTDIR)/config/common
INCLUDE += $(TOOLCHAIN_ROOTDIR)/MCU/ColdFire_Support/ewl/EWL_C/include
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/adc/mcf522xx
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/adc
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/enet/mcf5xxx_fec
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/enet/phy
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/enet
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx/freescale
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx/amd
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx/fujitsu
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx/spansion
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx/atmel
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx/istrata
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx/sharp
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/can/flexcan
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/gpio/mcf5225
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/gpio
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/i2c
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/i2c/polled
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/i2c/int
INCLUDE += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf52259
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/int_ctrl
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/io_mem
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/io_null
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pipe
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/lwgpio
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pcb
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pcb/mqxa
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pccard
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pcflash
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/rtc
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/sdcard/sdcard_spi
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/sdcard
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/serial
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/spi_legacy
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/spi_legacy/int
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/spi_legacy/polled
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/tchres
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/tfs
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/timer
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/usb
INCLUDE += $(MQX_ROOTDIR)/mqx/source/tad


SOURCES += $(MQX_ROOTDIR)/mqx/source/io/adc/mcf522xx/adc_mcf522xx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/adc/mcf522xx/adt_pit_mcf522xx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/adc/adc.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/mcf5xxx_fec/mcf5225_fec.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/mcf5xxx_fec/mcf5xxx_fec_init.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/mcf5xxx_fec/mcf5xxx_fec_join.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/mcf5xxx_fec/mcf5xxx_fec_mii.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/mcf5xxx_fec/mcf5xxx_fec_receive.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/mcf5xxx_fec/mcf5xxx_fec_rejoin.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/mcf5xxx_fec/mcf5xxx_fec_send.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/mcf5xxx_fec/mcf5xxx_fec_stop.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/mcf5xxx_fec/mcf5xxx_fec_util.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/phy/phy_ksz8041.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/enaddr.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/enclose.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/enerr.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/eninit.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/enjoin.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/enleave.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/enmediactl.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/enopen.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/enrecv.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/ensend.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/enstat.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/enstop.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/enutil.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/flashx/freescale/flash_mcf5225.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/flashx/freescale/flash_mcf52xx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/flashx/flashx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/can/flexcan/flexcan_mcf5225.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/can/flexcan/flexcan.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/can/flexcan/flexcan_int.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/gpio/mcf5225/io_gpio_mcf5225.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/gpio/io_gpio.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/i2c/i2c_mcf5225.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/i2c/polled/i2c_pol_mcf52xx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/i2c/int/i2c_int_mcf52xx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/i2c/polled/i2c_pol.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/i2c/int/i2c_int.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf52259/bsp_init.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf52259/enet_ini.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf52259/gpio_init.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf52259/init_cfcard.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf52259/init_flashx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf52259/init_i2c0.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf52259/init_i2c1.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf52259/init_sdcard0.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf52259/init_spi0.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf52259/init_tchres.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf52259/init_uart0.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf52259/init_uart1.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf52259/init_uart2.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf52259/init_usb.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf52259/init_bsp.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf52259/mqx_init.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf52259/mqx_main.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf52259/vectors.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/int_ctrl/int_ctrl_mcf5225.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/io_mem/io_mem.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/io_null/io_null.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/pipe/io_pipe.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/lwgpio/lwgpio_mcf5225.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/lwgpio/lwgpio.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/pcb/io_pcb2.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/pcb/io_pcb.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/pcb/mqxa/pcb_mqxa.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/pccard/pccardflexbus.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/pcflash/apcflash.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/rtc/rtc_mcf5225.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/rtc/rtc_mcf52xx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/sdcard/sdcard_spi/sdcard_spi.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/sdcard/sdcard.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/serial/serl_mcf5225.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/serial/int/serl_int_mcf52xx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/serial/polled/serl_pol_mcf52xx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/serial/io_sinit.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/serial/polled/serl_pol.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/serial/int/serl_int.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/spi_legacy/spi_mcf5225_qspi.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/spi_legacy/int/spi_int_mcf5xxx_qspi.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/spi_legacy/polled/spi_pol_mcf5xxx_qspi.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/spi_legacy/int/spi_int.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/spi_legacy/polled/spi_pol.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/tchres/tchres.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/tfs/tfs.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/timer/timer_mcf5225.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/timer/timer_pit.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/usb/usb_mcf5225.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/usb/usb_mcf5225_device.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/usb/usb_install.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf52259/cw/boot.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf52259/cw/cw.c


#----------------------------------------------------------
# load global settings
#----------------------------------------------------------
include $(MQX_ROOTDIR)/build/common/make/global.mak
-include $(MQX_ROOTDIR)/build/$(BOARD)/make/tools/$(TOOL).mak
include $(MQX_ROOTDIR)/build/common/make/verify.mak
include $(MQX_ROOTDIR)/build/common/make/lib-process.mak

