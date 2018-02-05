#ifndef __hidkeyboard_h__
#define __hidkeyboard_h__
/*HEADER**********************************************************************
*
* Copyright 2008 Freescale Semiconductor, Inc.
* Copyright 1989-2008 ARC International
*
* This software is owned or controlled by Freescale Semiconductor.
* Use of this software is governed by the Freescale MQX RTOS License
* distributed with this Material.
* See the MQX_RTOS_LICENSE file distributed for more details.
*
* Brief License Summary:
* This software is provided in source form for you to use free of charge,
* but it is not open source software. You are allowed to use this software
* but you cannot redistribute it or derivative works of it in source form.
* The software may be used only in connection with a product containing
* a Freescale microprocessor, microcontroller, or digital signal processor.
* See license agreement file for full license terms including other
* restrictions.
*****************************************************************************
*
* Comments:
*
*   This file contains keyboard-application types and definitions.
*
*
*END************************************************************************/

#ifdef __USB_OTG__
#include "otgapi.h"
#include "devapi.h"
#else
#include "hostapi.h"
#endif
#include "audio_speaker.h"

/***************************************
**
** Application-specific definitions
*/

/* Used to initialize USB controller */
#define MAX_FRAME_SIZE           1024

#define  HID_KEYBOARD_BUFFER_SIZE    1

#define USB_Keyboard_Event_CTRL 0x01
#define USB_Keyboard_Event_DATA 0x02
/*
** Following structs contain all states and pointers
** used by the application to control/operate devices.
*/

typedef struct usb_keyboard_device_struct {
    uint32_t                          DEV_STATE;  /* Attach/detach state */
    _usb_device_instance_handle      DEV_HANDLE;
    _usb_interface_descriptor_handle INTF_HANDLE;
    CLASS_CALL_STRUCT                CLASS_INTF; /* Class-specific info */
} USB_KEYBOARD_DEVICE_STRUCT, * USB_KEYBOARD_DEVICE_STRUCT_PTR;


/* Alphabetical list of Function Prototypes */

#ifdef __cplusplus
extern "C" {
#endif

    void usb_host_hid_keyboard_recv_callback(_usb_pipe_handle, void *, unsigned char *, uint32_t,
    uint32_t);
    void usb_host_hid_keyboard_ctrl_callback(_usb_pipe_handle, void *, unsigned char *, uint32_t,
    uint32_t);
    void usb_host_hid_keyboard_event(_usb_device_instance_handle,
    _usb_interface_descriptor_handle, uint32_t);

#ifdef __cplusplus
}
#endif


#endif

/* EOF */
