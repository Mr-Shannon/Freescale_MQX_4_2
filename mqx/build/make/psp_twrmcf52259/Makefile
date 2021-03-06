#----------------------------------------------------------
# setup variables
#----------------------------------------------------------
MQX_ROOTDIR             = $(abspath ../../../..)
TYPE                    = library
NAME                    = psp
BOARD                   = twrmcf52259
LIBRARY_ROOTDIR         = $(MQX_ROOTDIR)/lib/$(BOARD).$(TOOL)
LIBRARY_DIR             = $(LIBRARY_ROOTDIR)/$(CONFIG)/psp
LIBRARY_FILE            = $(LIBRARY_DIR)/psp.$(LIBRARY_EXT)
POSTBUILD_CMD           = $(if $(findstring $(HOSTENV),WINDOWS),$(MQX_ROOTDIR)/mqx/build/bat/psp_twrmcf52259.bat $(MQX_ROOTDIR) $(LIBRARY_DIR) $(TOOL),$(MQX_ROOTDIR)/mqx/build/bat/psp_twrmcf52259.sh $(MQX_ROOTDIR) $(LIBRARY_DIR) $(TOOL))


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
INCLUDE += $(MQX_ROOTDIR)/mqx/source/tad
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


SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/cf_assert.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/dispatch.S
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/int_gkis.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/int_inst.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/int_kisr.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/int_pvta.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/int_sr.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/int_unx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/int_vtab.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/int_xcpt.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/ipsum.S
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/mem_copy.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/mem_zero.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_dati.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_gmse.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_hoti.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_iinit.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_lswp.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_mat1.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_mat2.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_mat3.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_miti.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_mstf.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_msti.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_nsti.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_psti.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_seti.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_supp.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_tiad.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_tida.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_tihr.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_timn.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_tims.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_tinm.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_tins.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_tiol.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_tipr.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_tips.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_tise.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_tisu.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_tius.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_tkti.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/psp_usti.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/sc_irdyq.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/stack_bu.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/stack_de.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/stack_st.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/event.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_clre.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_dopr.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_fclos.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_feof.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_ferr.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_fflsh.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_fgetc.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_fgetl.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_fgets.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_fopen.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_fp.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_fprt.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_fputc.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_fputs.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_fscan.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_fseek.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_fstat.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_ftell.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_fung.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_ioctl.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_misc.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_pntf.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_read.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_scanf.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_scanl.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_spr.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_sscan.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_util.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_vpr.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/fio/io_write.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/io_init.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/io_inst.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/io_instx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/io_ghand.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/io_shand.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/io/io_uinst.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/ipc.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/idletask.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/inittask.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/int.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/lwsem.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/mem.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/mqx.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/sched.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/task.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/time.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/taskq.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/klog.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/log.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/lwevent.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/lwlog.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/lwmem.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/lwmsgq.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/lwtimer.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/msg.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/msgq.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/msgpool.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/mutex.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/name.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/partition.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/queue.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/sem.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/psp/coldfire/mcf5225.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/string/strnlen.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/string/str_utos.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/tad/tad.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/timer.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/tlsf.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/tlsf_adaptation.c
SOURCES += $(MQX_ROOTDIR)/mqx/source/kernel/watchdog.c


#----------------------------------------------------------
# load global settings
#----------------------------------------------------------
include $(MQX_ROOTDIR)/build/common/make/global.mak
-include $(MQX_ROOTDIR)/build/$(BOARD)/make/tools/$(TOOL).mak
include $(MQX_ROOTDIR)/build/common/make/verify.mak
include $(MQX_ROOTDIR)/build/common/make/lib-process.mak

