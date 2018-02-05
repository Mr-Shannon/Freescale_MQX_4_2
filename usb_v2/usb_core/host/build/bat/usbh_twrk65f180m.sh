#!/usr/bin/env bash

# expect forward slash paths
ROOTDIR="${1}"
OUTPUTDIR="${2}"
TOOL="${3}"
OS="${4}"
TARGET="${5}"

mkdir -p ${2}

# copy common files
cp -f "${ROOTDIR}/usb_core/include/usb.h" "${OUTPUTDIR}/usb.h"
cp -f "${ROOTDIR}/usb_core/include/compiler.h" "${OUTPUTDIR}/compiler.h"
cp -f "${ROOTDIR}/usb_core/include/types.h" "${OUTPUTDIR}/types.h"
cp -f "${ROOTDIR}/usb_core/include/usb_desc.h" "${OUTPUTDIR}/usb_desc.h"
cp -f "${ROOTDIR}/usb_core/include/usb_error.h" "${OUTPUTDIR}/usb_error.h"
cp -f "${ROOTDIR}/usb_core/include/usb_misc.h" "${OUTPUTDIR}/usb_misc.h"
cp -f "${ROOTDIR}/usb_core/include/usb_opt.h" "${OUTPUTDIR}/usb_opt.h"
cp -f "${ROOTDIR}/usb_core/include/usb_types.h" "${OUTPUTDIR}/usb_types.h"
cp -f "${ROOTDIR}/adapter/sources/adapter.h" "${OUTPUTDIR}/adapter.h"
cp -f "${ROOTDIR}/adapter/sources/adapter_types.h" "${OUTPUTDIR}/adapter_types.h"
cp -f "${ROOTDIR}/usb_core/host/include/twrk65f180m/usb_host_config.h" "${OUTPUTDIR}/usb_host_config.h"
cp -f "${ROOTDIR}/usb_core/host/include/usb_host_stack_interface.h" "${OUTPUTDIR}/usb_host_stack_interface.h"
cp -f "${ROOTDIR}/usb_core/host/sources/classes/hid/usb_host_hid.h" "${OUTPUTDIR}/usb_host_hid.h"
cp -f "${ROOTDIR}/usb_core/host/sources/classes/hub/usb_host_hub.h" "${OUTPUTDIR}/usb_host_hub.h"
cp -f "${ROOTDIR}/usb_core/host/sources/classes/cdc/usb_host_cdc.h" "${OUTPUTDIR}/usb_host_cdc.h"
cp -f "${ROOTDIR}/usb_core/host/sources/classes/audio/usb_host_audio.h" "${OUTPUTDIR}/usb_host_audio.h"
cp -f "${ROOTDIR}/usb_core/host/sources/classes/hub/usb_host_hub_sm.h" "${OUTPUTDIR}/usb_host_hub_sm.h"
cp -f "${ROOTDIR}/usb_core/host/sources/classes/msd/usb_host_msd_bo.h" "${OUTPUTDIR}/usb_host_msd_bo.h"
cp -f "${ROOTDIR}/usb_core/host/sources/classes/msd/usb_host_msd_ufi.h" "${OUTPUTDIR}/usb_host_msd_ufi.h"
cp -f "${ROOTDIR}/usb_core/host/sources/classes/phdc/usb_host_phdc.h" "${OUTPUTDIR}/usb_host_phdc.h"


# cw10 files
if [ "${TOOL}" = "cw10" ]; then
:
fi
# iar files
if [ "${TOOL}" = "iar" ]; then
:
fi
# cw10gcc files
if [ "${TOOL}" = "cw10gcc" ]; then
:
fi
# uv4 files
if [ "${TOOL}" = "uv4" ]; then
:
fi

# mqx files
if [ "${OS}" = "mqx" ]; then
cp -f "${ROOTDIR}/adapter/sources/mqx/adapter_mqx.h" "${OUTPUTDIR}/adapter_mqx.h"
cp -f "${ROOTDIR}/adapter/sources/mqx/adapter_cfg.h" "${OUTPUTDIR}/adapter_cfg.h"
fi

# bm files
if [ "${OS}" = "bm" ]; then
cp -f "${ROOTDIR}/adapter/sources/bm/adapter_bm.h" "${OUTPUTDIR}/adapter_bm.h"
cp -f "${ROOTDIR}/adapter/sources/bm/adapter_cfg.h" "${OUTPUTDIR}/adapter_cfg.h"
fi

# sdk files
if [ "${OS}" = "sdk" ]; then
cp -f "${ROOTDIR}/adapter/sources/sdk/adapter_sdk.h" "${OUTPUTDIR}/adapter_sdk.h"
cp -f "${ROOTDIR}/adapter/sources/sdk/adapter_cfg.h" "${OUTPUTDIR}/adapter_cfg.h"
fi

