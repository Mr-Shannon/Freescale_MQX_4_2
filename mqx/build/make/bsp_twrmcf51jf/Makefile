#----------------------------------------------------------
# setup variables
#----------------------------------------------------------
MQX_ROOTDIR             = $(abspath ../../../..)
TYPE                    = library
NAME                    = bsp
BOARD                   = twrmcf51jf
LIBRARY_ROOTDIR         = $(MQX_ROOTDIR)/lib/$(BOARD).$(TOOL)
LIBRARY_DIR             = $(LIBRARY_ROOTDIR)/$(CONFIG)/bsp
LIBRARY_FILE            = $(LIBRARY_DIR)/bsp.$(LIBRARY_EXT)
POSTBUILD_CMD           = $(if $(findstring $(HOSTENV),WINDOWS),$(MQX_ROOTDIR)/mqx/build/bat/bsp_twrmcf51jf.bat $(MQX_ROOTDIR) $(LIBRARY_DIR) $(TOOL),$(MQX_ROOTDIR)/mqx/build/bat/bsp_twrmcf51jf.sh $(MQX_ROOTDIR) $(LIBRARY_DIR) $(TOOL))


#-----------------------------------------------------------
# load tool settings
#-----------------------------------------------------------
-include tools/$(TOOL).mak


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
INCLUDE += $(MQX_ROOTDIR)/mqx/source/psp/coldfire
INCLUDE += $(MQX_ROOTDIR)/config/twrmcf51jf
INCLUDE += $(MQX_ROOTDIR)/mqx/source/include
INCLUDE += $(MQX_ROOTDIR)/config/common
INCLUDE += $(TOOLCHAIN_ROOTDIR)/MCU/ColdFire_Support/ewl/EWL_C/include
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/adc/kadc
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/adc
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/cm
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx/freescale
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx/amd
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx/fujitsu
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx/spansion
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx/atmel
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx/istrata
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/flashx/sharp
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/gpio/mcf51jf
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/gpio
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/hmi
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/hmi/TSS/shared
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/hwtimer
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/i2c
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/i2c/polled
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/i2c/int
INCLUDE += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf51jf
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/enet
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/int_ctrl
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/io_mem
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/io_null
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pipe
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/lpm
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/lwgpio
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pcb
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pcb/mqxa
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pccard
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/pcflash
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/sdcard/sdcard_spi
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/sdcard
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/serial
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/spi_legacy
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/spi_legacy/int
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/spi_legacy/polled
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/tfs
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/timer
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/usb
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/usb_dcd
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/usb_dcd/polled
INCLUDE += $(MQX_ROOTDIR)/mqx/source/io/usb_dcd/int
INCLUDE += $(MQX_ROOTDIR)/mqx/source/tad


SOURCES += $(MQX_ROOTDIR)/mqx/source/io/adc/kadc/adc_mcf51jf.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/adc/kadc/adc_kadc.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/adc/kadc/adt_kpdb.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/adc/adc.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/cm/cm.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/flashx/freescale/flash_mcf51jf.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/flashx/freescale/flash_ftfl.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/flashx/flashx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/gpio/mcf51jf/io_gpio_mcf51jf.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/gpio/io_gpio.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/hmi/btnled.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/hmi/hmi_client.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/hmi/hmi_lwgpio_provider.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/hmi/hmi_tss_provider.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/hmi/TSS/shared/TSS_Freemaster.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/hmi/TSS/shared/TSS_Sensor.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/hmi/TSS/shared/TSS_SensorGPIO.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/hmi/TSS/shared/TSS_SensorTSI.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/hmi/TSS/shared/TSS_SensorTSIL.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/hmi/TSS/shared/TSS_SystemSetupData.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/hwtimer/hwtimer_lpt.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/hwtimer/hwtimer_cfplus.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/hwtimer/hwtimer.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/i2c/i2c_mcf51jf.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/i2c/polled/i2c_pol_ki2c.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/i2c/int/i2c_int_ki2c_legacy.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/i2c/polled/i2c_pol.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/i2c/int/i2c_int.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf51jf/bsp_cm.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf51jf/init_adc.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf51jf/init_cfcard.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf51jf/init_flashx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf51jf/init_gpio.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf51jf/init_hw.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf51jf/init_hmi.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf51jf/init_i2c.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf51jf/init_lpm.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf51jf/init_sdcard.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf51jf/init_spi.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf51jf/init_uart.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf51jf/init_usb_dcd.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf51jf/init_usb.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf51jf/init_bsp.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf51jf/mqx_init.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf51jf/mqx_main.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf51jf/vectors.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/int_ctrl/int_ctrl_mcfplus.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/io_mem/io_mem.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/io_null/io_null.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/pipe/io_pipe.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/lpm/lpm_cfplus.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/lpm/lpm.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/lwgpio/lwgpio_mcf51jf.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/lwgpio/lwgpio.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/pcb/io_pcb2.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/pcb/io_pcb.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/pcb/mqxa/pcb_mqxa.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/pccard/pccardflexbus.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/pcflash/apcflash.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/sdcard/sdcard_spi/sdcard_spi.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/sdcard/sdcard.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/serial/serl_mcf51jf.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/serial/int/serl_int_kuart.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/serial/polled/serl_pol_kuart.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/serial/io_sinit.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/serial/polled/serl_pol.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/serial/int/serl_int.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/spi_legacy/spi_mcf51jf.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/spi_legacy/int/spi_int_spi16.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/spi_legacy/polled/spi_pol_spi16.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/spi_legacy/int/spi_int.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/spi_legacy/polled/spi_pol.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/tfs/tfs.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/timer/timer_mcf51jf.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/timer/timer_mtim16.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/timer/timer_pscaler.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/usb/usb_mcf51jf.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/usb/usb_mcf51jf_device.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/usb/usb_install.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/usb_dcd/usb_dcd_mcf51jf.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/usb_dcd/polled/usb_dcd_pol_kn.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/usb_dcd/int/usb_dcd_int_kn.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/usb_dcd/polled/usb_dcd_pol.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/usb_dcd/int/usb_dcd_int.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf51jf/cw/boot.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/bsp/twrmcf51jf/cw/cw.c


#----------------------------------------------------------
# load global settings
#----------------------------------------------------------
include $(MQX_ROOTDIR)/build/common/make/global.mak
-include $(MQX_ROOTDIR)/build/$(BOARD)/make/tools/$(TOOL).mak
include $(MQX_ROOTDIR)/build/common/make/verify.mak
include $(MQX_ROOTDIR)/build/common/make/lib-process.mak

