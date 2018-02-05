#----------------------------------------------------------
# setup variables
#----------------------------------------------------------
MQX_ROOTDIR             = $(abspath ../../../..)
TYPE                    = library
NAME                    = ffs
BOARD                   = twrmcf54418
LIBRARY_ROOTDIR         = $(MQX_ROOTDIR)/lib/$(BOARD).$(TOOL)
LIBRARY_DIR             = $(LIBRARY_ROOTDIR)/$(CONFIG)/ffs
LIBRARY_FILE            = $(LIBRARY_DIR)/ffs.$(LIBRARY_EXT)
POSTBUILD_CMD           = $(if $(findstring $(HOSTENV),WINDOWS),$(MQX_ROOTDIR)/ffs/build/bat/ffs_twrmcf54418.bat $(MQX_ROOTDIR) $(LIBRARY_DIR) $(TOOL),$(MQX_ROOTDIR)/ffs/build/bat/ffs_twrmcf54418.sh $(MQX_ROOTDIR) $(LIBRARY_DIR) $(TOOL))


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
INCLUDE += $(MQX_ROOTDIR)/ffs/source/wearleveling/buffer_manager
INCLUDE += $(MQX_ROOTDIR)/ffs/source/wearleveling/common
INCLUDE += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/common
INCLUDE += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/data_drive
INCLUDE += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/mapper
INCLUDE += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/media
INCLUDE += $(MQX_ROOTDIR)/ffs/source
INCLUDE += $(MQX_ROOTDIR)/ffs/source/wearleveling/hal
INCLUDE += $(MQX_ROOTDIR)/ffs/source/wearleveling/nfc_wl
INCLUDE += $(MQX_ROOTDIR)/ffs/source/wearleveling/rtos/mqx
INCLUDE += $(MQX_ROOTDIR)/ffs/source/wearleveling
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


SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/buffer_manager/media_buffer_manager.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/buffer_manager/media_buffer_manager_init.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/common/double_list.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/common/red_black_tree.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/common/wlru.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/common/ddi_block.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/common/deferred_task.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/common/ddi_metadata.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/common/ddi_page.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/common/page_order_map.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/data_drive/ddi_nand_data_drive_erase.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/data_drive/ddi_nand_data_drive_get_info.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/data_drive/ddi_nand_data_drive_init.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/data_drive/ddi_nand_data_drive_read_sector.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/data_drive/ddi_nand_data_drive_set_info.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/data_drive/ddi_nand_ndd_flush.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/data_drive/ddi_nand_ndd_write_sector.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/data_drive/ddi_nand_nssm_get_entry.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/data_drive/nonsequential_sectors_map.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi_ldl/ddi_ldl_drive_get_info.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi_ldl/ddi_ldl_init.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi_ldl/ddi_ldl_iterator.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi_ldl/ddi_ldl_read.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi_ldl/ddi_ldl_util.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi_ldl/ddi_ldl_write.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/mapper/ddi_nand_mapper_get_info.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/mapper/ddi_nand_mapper_utilities.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/mapper/ddi_nand_mapper_zone_map_cache_lookup.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/mapper/mapper.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/mapper/persistent_map.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/mapper/persistent_phy_map.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/mapper/phy_map.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/mapper/zone_map_cache.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/mapper/zone_map_section_page.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/media/bad_block_table.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/media/ddi_nand_media_allocate.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/media/ddi_nand_media_discover.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/media/ddi_nand_media_get_info.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/media/ddi_nand_media_init.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/media/ddi_nand_media_regions.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi/media/ddi_nand_media_shutdown.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/nandflash_wl.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/nandflash_wl_init.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/hal/ddi_nand_hal_common.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/hal/ddi_nand_hal_globals.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/hal/ddi_nand_hal_init.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/hal/ddi_nand_hal_nfcphymedia.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/nfc_wl/nfc_wl.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/nfc_wl/nfc_wl_dma.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/rtos/mqx/deferred_task_queue.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/rtos/mqx/errcode.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/rtos/mqx/mem_management.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/rtos/mqx/simple_mutex.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/rtos/mqx/simple_timer.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/ddi_nand_media_definition.cpp
SOURCES += $(MQX_ROOTDIR)/ffs/source/wearleveling/wl_common.cpp


#----------------------------------------------------------
# load global settings
#----------------------------------------------------------
include $(MQX_ROOTDIR)/build/common/make/global.mak
-include $(MQX_ROOTDIR)/build/$(BOARD)/make/tools/$(TOOL).mak
include $(MQX_ROOTDIR)/build/common/make/verify.mak
include $(MQX_ROOTDIR)/build/common/make/lib-process.mak

