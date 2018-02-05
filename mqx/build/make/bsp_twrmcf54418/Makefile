#----------------------------------------------------------
# setup variables
#----------------------------------------------------------
MQX_ROOTDIR             = $(abspath ../../../..)
TYPE                    = library
NAME                    = bsp
BOARD                   = twrmcf54418
LIBRARY_ROOTDIR         = $(MQX_ROOTDIR)/lib/$(BOARD).$(TOOL)
LIBRARY_DIR             = $(LIBRARY_ROOTDIR)/$(CONFIG)/bsp
LIBRARY_FILE            = $(LIBRARY_DIR)/bsp.$(LIBRARY_EXT)
POSTBUILD_CMD           = $(if $(findstring $(HOSTENV),WINDOWS),$(MQX_ROOTDIR)/mqx/build/bat/bsp_twrmcf54418.bat $(MQX_ROOTDIR) $(LIBRARY_DIR) $(TOOL),$(MQX_ROOTDIR)/mqx/build/bat/bsp_twrmcf54418.sh $(MQX_ROOTDIR) $(LIBRARY_DIR) $(TOOL))


#-----------------------------------------------------------
# load tool settings
#-----------------------------------------------------------
-include tools/$(TOOL).mak


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
INCLUDE += $(MQX_ROOTDIR)/mqx/source/psp/coldfire
INCLUDE += $(MQX_ROOTDIR)/config/twrmcf54418
INCLUDE += $(MQX_ROOTDIR)/mqx/source/include
INCLUDE += $(MQX_ROOTDIR)/config/common
INCLUDE += $(TOOLCHAIN_ROOTDIR)/MCU/ColdFire_Support/ewl/EWL_C/include
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/adc/mcf544xx
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/adc
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/enet/macnet
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/enet/phy
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/enet
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/esdhc
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/can/flexcan
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/gpio/mcf5441
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/gpio
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/i2c
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/i2c/polled
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/i2c/int
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/i2s
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/i2s/int
INCLUDE += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/int_ctrl
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/io_mem
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/io_null
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pipe
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/lwgpio
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/nandflash/nfc
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/nandflash
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pcb
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pcb/mqxa
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pccard
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pcflash
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/rtc
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/sdcard/sdcard_spi
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/sdcard/sdcard_esdhc
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/sdcard
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/serial
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/spi
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/tfs
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/timer
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/usb
INCLUDE += $(MQX_ROOTDIR)/mqx/source/tad


SOURCES += $(MQX_ROOTDIR)/mqx/source/io/adc/mcf544xx/adc_mcf544xx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/adc/mcf544xx/adt_pit_mcf544xx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/adc/adc.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/macnet/macnet_mcf5441.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/phy/phy_dp83xxx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/phy/phy_ksz8041.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/macnet/macnet_init.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/macnet/macnet_join.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/macnet/macnet_mii.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/macnet/macnet_receive.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/macnet/macnet_rejoin.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/macnet/macnet_send.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/macnet/macnet_stop.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/macnet/macnet_util.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/enet/macnet/macnet_1588.c
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
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/esdhc/esdhc_mcf5441.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/esdhc/esdhc.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/can/flexcan/flexcan_mcf5441.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/can/flexcan/flexcan.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/can/flexcan/flexcan_int.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/gpio/mcf5441/io_gpio_mcf5441.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/gpio/io_gpio.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/i2c/i2c_mcf5441.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/i2c/polled/i2c_pol_mcf54xx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/i2c/int/i2c_int_mcf54xx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/i2c/polled/i2c_pol.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/i2c/int/i2c_int.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/i2s/i2s_mcf5441.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/i2s/int/i2s_int_mcf54xx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/i2s/int/i2s_int.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/bootstrap.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/bsp_time.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/enet_ini.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/gpio_init.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/init_cfcard.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/init_esdhc0.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/init_nandflash.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/init_hw.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/init_i2c0.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/init_i2c5.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/init_i2s0.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/init_i2s1.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/init_sdcard0.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/init_spi0.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/init_spi1.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/init_uart0.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/init_uart2.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/init_uart4.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/init_uart5.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/init_uart6.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/init_usb.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/bsp_cm.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/init_bsp.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/mqx_init.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/mqx_main.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/vectors.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/int_ctrl/int_ctrl_mcf5441.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/io_mem/io_mem.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/io_null/io_null.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/pipe/io_pipe.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/lwgpio/lwgpio_mcf5441.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/lwgpio/lwgpio.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/nandflash/nfc/nfc_mcf5441.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/nandflash/nand_devices/MT29F2G16.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/nandflash/nfc/nfc.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/nandflash/nfc/nfc_dma.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/nandflash/nandflash.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/pcb/io_pcb2.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/pcb/io_pcb.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/pcb/mqxa/pcb_mqxa.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/pccard/pccardflexbus.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/pcflash/apcflash.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/rtc/irtc_mcf5441x.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/rtc/irtc_mcf5xxx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/sdcard/sdcard_spi/sdcard_spi.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/sdcard/sdcard_esdhc/sdcard_esdhc.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/sdcard/sdcard.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/serial/serl_mcf5441.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/serial/int/serl_int_mcf54xx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/serial/polled/serl_pol_mcf54xx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/serial/io_sinit.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/serial/polled/serl_pol.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/serial/int/serl_int.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/spi/spi_mcf5441.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/spi/spi_dspi.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/spi/spi_dspi_common.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/spi/spi.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/tfs/tfs.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/timer/timer_mcf5441.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/timer/timer_pit.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/usb/usb_mcf5441.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/usb/usb_mcf5441_device.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/usb/usb_install.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/cw/boot.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf54418/cw/cw.c


#----------------------------------------------------------
# load global settings
#----------------------------------------------------------
include $(MQX_ROOTDIR)/build/common/make/global.mak
-include $(MQX_ROOTDIR)/build/$(BOARD)/make/tools/$(TOOL).mak
include $(MQX_ROOTDIR)/build/common/make/verify.mak
include $(MQX_ROOTDIR)/build/common/make/lib-process.mak

