/**HEADER********************************************************************
* 
* Copyright (c) 2010, 2013 - 2014 Freescale Semiconductor;
* All Rights Reserved
*
*************************************************************************** 
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR 
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
* THE POSSIBILITY OF SUCH DAMAGE.
*
**************************************************************************
*
* $FileName: usb_otg_max3353.c$
* $Version : 
* $Date    : 
*
* Comments : This file contains the implementation of the OTG functions using 
*            the MAX3353 circuit
*
*         
*****************************************************************************/
#include "usb.h"
#include "usb_otg_private.h"
#include "adapter.h"
#include "i2c.h"
#include "usb_otg.h"
#include "usb_otg_max3353.h"
uint32_t u32ID=0;

/* Private functions prototypes *********************************************/

static uint8_t      _usb_otg_max3353_CheckifPresent(void* f_ptr);
static uint8_t      _usb_otg_max3353_Init(void* f_ptr);
static bool         _usb_otg_max3353_WriteReg(void* f_ptr, uint8_t regAdd , uint8_t regValue);
static bool         _usb_otg_max3353_ReadReg(void* f_ptr, uint8_t regAdd , uint8_t* p_regValue);
static void         _usb_otg_max3353_enable_disable(void* f_ptr, bool enable);
static uint8_t      _usb_otg_max3353_get_status(void* f_ptr);
static uint8_t      _usb_otg_max3353_get_interrupts(void* f_ptr);
static void         _usb_otg_max3353_set_VBUS(void* f_ptr, bool enable);
static void         _usb_otg_max3353_set_pdowns(void* f_ptr, uint8_t bitfield);
extern void*        bsp_usb_otg_get_peripheral_init_param(uint8_t controller_id);
extern void         bsp_usb_otg_max3353_clear_pin_int_flag(void);
extern void         bsp_usb_otg_max3353_set_pin_int(bool level ,bool enable);

/* Private functions definitions *********************************************/
/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _usb_otg_max3353_CheckifPresent
* Returned Value   :
* Comments         : Check if MAX3353 is present
*    
*
*END*----------------------------------------------------------------------*/
static uint8_t _usb_otg_max3353_CheckifPresent
(
    void* f_ptr
)
{
    uint8_t  u8Counter;
    uint8_t  ch_read;

    for(u8Counter=0;u8Counter<4;u8Counter++)
    {
        u32ID=u32ID<<8;
        _usb_otg_max3353_ReadReg(f_ptr, u8Counter , &ch_read); 
        u32ID |= ch_read;
    }
    if(u32ID!=MAX3353_MID)
    {
        return(MAX3353_NOT_PRESENT);
    }

    u32ID=0;
    for(u8Counter=4;u8Counter<8;u8Counter++)
    {
        u32ID=u32ID<<8;
        _usb_otg_max3353_ReadReg(f_ptr, u8Counter , &ch_read);
        u32ID |= ch_read;
    }
    if(u32ID!=MAX3353_PID)
    {
        return(MAX3353_NOT_PRESENT);
    }
    return(MAX3353_OK);
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _usb_otg_max3353_Init
* Returned Value   :
* Comments         : Initialize max3353
*    
*
*END*----------------------------------------------------------------------*/
static uint8_t _usb_otg_max3353_Init
(
    void* f_ptr
)
{
    if(_usb_otg_max3353_CheckifPresent(f_ptr))
    {
        return(MAX3353_NOT_PRESENT);
    }

    /* Enable Charge pump for VBUs detection */ 
    _usb_otg_max3353_WriteReg(f_ptr,MAX3353_REG_CTRL_2,0x80);

    /* Set Rising edge for VBUS detection */
    _usb_otg_max3353_WriteReg(f_ptr,MAX3353_REG_INT_EDGE,VBUS_VALID_ED_MASK);

    /* Activate ID (GND and float) & SESSION Interrupts */
    _usb_otg_max3353_WriteReg(f_ptr,MAX3353_REG_INT_MASK,ID_FLOAT_EN_MASK|ID_GND_EN_MASK|VBUS_VALID_EN_MASK|SESSION_SESSEND_EN_MASK);

    return(MAX3353_OK);
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _usb_otg_max3353_WriteReg
* Returned Value   :
* Comments         : Write data to max3353 register
*    
*
*END*----------------------------------------------------------------------*/
static bool _usb_otg_max3353_WriteReg
(
    void* f_ptr, 
    uint8_t regAdd, 
    uint8_t regValue
)
{
    bool    ret_val = TRUE;
    int32_t status;
    int32_t param;
    int32_t result;
    uint8_t buff[2]; 
    
    buff[0] = regAdd;
    buff[1] = regValue;
    /* Check bus*/
    status = ioctl (f_ptr, IO_IOCTL_I2C_GET_BUS_AVAILABILITY, &param);
    if( status != I2C_OK )
    {
        return FALSE;
    }
    if (param & I2C_BUS_BUSY)
    {
        return FALSE;
    }
    
    /* Send I2C slave address to bus*/
    /* Initiate start and send I2C bus address */
    (void)fwrite (buff, 1, 0, f_ptr);
    status = ioctl (f_ptr, IO_IOCTL_FLUSH_OUTPUT, &param);
    if((status != I2C_OK) || param )
    {
        /* param != 0 means no ack received */
        status = ioctl (f_ptr, IO_IOCTL_I2C_STOP, NULL); 
        return FALSE;
    }
    /* Send data to MAX3353*/
    result = fwrite (buff, 1, 2, f_ptr);
    if(result != 2)
    {
        ret_val = FALSE;
    }
    /* Wait for completion */
    result = fflush (f_ptr);
    if (MQX_OK != result)
    {
        ret_val = FALSE;
    }
    /* Send stop signal */
    status = ioctl (f_ptr, IO_IOCTL_I2C_STOP, NULL);
    if(status != I2C_OK)
    {
        ret_val = FALSE;
    }
    return ret_val;
    
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _usb_otg_max3353_ReadReg
* Returned Value   :
* Comments         : Read data from max3353 register
*    
*
*END*----------------------------------------------------------------------*/
static bool _usb_otg_max3353_ReadReg
(
    void*       f_ptr,
    uint8_t     regAdd, 
    uint8_t*    p_regValue
)
{
    bool    ret_val = TRUE;
    int32_t status;
    int32_t param;
    int32_t result;
    uint8_t buff[1]; 

    buff[0] = regAdd;
    
    status = ioctl (f_ptr, IO_IOCTL_I2C_GET_BUS_AVAILABILITY, &param);
    if( status != I2C_OK )
    {
        return FALSE;
    }
    if (param & I2C_BUS_BUSY)
    {
        return FALSE;
    }
    /* Initiate start and send I2C bus address */
    (void)fwrite (buff, 1, 0, f_ptr);
    status = ioctl (f_ptr, IO_IOCTL_FLUSH_OUTPUT, &param);
    if((status != I2C_OK) || param )
    {
        /* param != 0 means no ack received */
        status = ioctl (f_ptr, IO_IOCTL_I2C_STOP, NULL); 
        return FALSE;
    }
    result = fwrite (buff, 1, 1, f_ptr);
    if(result != 1)
    {
        ret_val = FALSE;
    }
    /* Wait for completion */
    result = fflush (f_ptr);
    if (MQX_OK != result)
    {
        ret_val = FALSE;
    }
    if(ret_val == FALSE)
    {
        status = ioctl (f_ptr, IO_IOCTL_I2C_STOP, NULL);
        return ret_val;
    }
    status = ioctl (f_ptr, IO_IOCTL_I2C_REPEATED_START, NULL);
    if( status != I2C_OK )
    {
        ret_val = FALSE;
    }
    param = 1;
    status = ioctl (f_ptr, IO_IOCTL_I2C_SET_RX_REQUEST, &param);
    if( status != I2C_OK )
    {
        ret_val = FALSE;
    }  
    result = fread (p_regValue, 1, 1, f_ptr);
    if(result != 1)
    {
        ret_val = FALSE;
    }
    status = ioctl (f_ptr, IO_IOCTL_I2C_STOP, NULL);
    if(status != I2C_OK)
    {
        ret_val = FALSE;
    }

    return ret_val;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _usb_otg_max3353_enable_disable
* Returned Value   :
* Comments         : Enable/disable MAX3353
*    
*
*END*----------------------------------------------------------------------*/
static void _usb_otg_max3353_enable_disable
(
    void*   f_ptr,
    bool    enable
)
{
    volatile uint8_t max3353_data;

    _usb_otg_max3353_Init(f_ptr);
    if(enable)
    {
        max3353_data = 0x02;
        while(_usb_otg_max3353_WriteReg(f_ptr, MAX3353_REG_CTRL_1, max3353_data) == FALSE){}   
        max3353_data = 0x1F; /* Enable interrupts */
        while(_usb_otg_max3353_WriteReg(f_ptr, MAX3353_REG_INT_MASK, max3353_data) == FALSE){}
        max3353_data = 0x00;  /* Enable module. */
    }
    else
    {
        max3353_data = 1;  /* Activate shutdown */
    }

    /* Enable/Disable module */
    while(_usb_otg_max3353_WriteReg(f_ptr, MAX3353_REG_CTRL_2, max3353_data) == FALSE){}

    /* Read the latch to clear any pending interrupts */
    (void)_usb_otg_max3353_get_interrupts(f_ptr);  
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _usb_otg_max3353_get_status
* Returned Value   : unsigned char, meaning the status of MAX3353
* Comments         : Get MAX3353 status
*    
*
*END*----------------------------------------------------------------------*/
static uint8_t _usb_otg_max3353_get_status
(
    void* f_ptr
)
{
    uint8_t status;
    uint8_t edge, new_edge;

    while(_usb_otg_max3353_ReadReg(f_ptr, MAX3353_REG_STATUS, &status) == FALSE){}

    /* Handle here the edge detection in SessionValid and VBus valid */
    /* Read the current edge */
    while(_usb_otg_max3353_ReadReg(f_ptr, MAX3353_REG_INT_EDGE, &edge) == FALSE){}

    new_edge = (uint8_t)((~(status)) & 0x03);
    if(new_edge != edge)
    {      
        /* Write the new edges */
        while(_usb_otg_max3353_WriteReg(f_ptr, MAX3353_REG_INT_EDGE, new_edge) == FALSE){}
    }
    return status;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _usb_otg_max3353_get_interrupts
* Returned Value   : unsigned char meaning interrupts
* Comments         : Read interrupts from MAX3353
*    
*
*END*----------------------------------------------------------------------*/
static uint8_t _usb_otg_max3353_get_interrupts
(
    void* f_ptr
)
{
    uint8_t data;
    
    while(_usb_otg_max3353_ReadReg(f_ptr, MAX3353_REG_INT_LATCH, &data) == FALSE){}    
    
    return data;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _usb_otg_max3353_set_VBUS
* Returned Value   :
* Comments         : Set VBUS for MAX3353
*    
*
*END*----------------------------------------------------------------------*/
static void _usb_otg_max3353_set_VBUS
(
    void* f_ptr, 
    bool enable
)
{
    volatile uint8_t max3353_data;
    
    if(enable)
    {
        max3353_data = OTG_CTRL_2_VBUS_DRV;/* connect VBUS to the charge pump */
    }
    else
    {
        max3353_data = OTG_CTRL_2_VBUS_DISCHG;/* disconnect the charge pump and  activate the 5k pull down resistor */
    }
    
    /* Enable/Disable module */
    while(_usb_otg_max3353_WriteReg(f_ptr, MAX3353_REG_CTRL_2, max3353_data) == FALSE){}

}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _usb_otg_max3353_set_pdowns
* Returned Value   :
* Comments         : Set pull-downs for MAX3353
*    
*
*END*----------------------------------------------------------------------*/
static void _usb_otg_max3353_set_pdowns(void* f_ptr, uint8_t bitfield)
{
    volatile uint8_t max3353_data;
    
    max3353_data =  OTG_CTRL_1_IRQ_PUSH_PULL;
    
    if(bitfield & OTG_CTRL_PDOWN_DP)
    {
        max3353_data |= OTG_CTRL_1_PDOWN_DP;
    }
    
    if(bitfield & OTG_CTRL_PDOWN_DM)
    {
        max3353_data |= OTG_CTRL_1_PDOWN_DM;
    }
    
    while(_usb_otg_max3353_WriteReg(f_ptr, MAX3353_REG_CTRL_1, max3353_data) == FALSE){}
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _usb_otg_max3353_isr
* Returned Value   :
* Comments         : 
*    
*
*END*----------------------------------------------------------------------*/
static void _usb_otg_max3353_isr
(
    void* otg_max3353_call_ptr
) 
{
    usb_otg_state_struct_t * usb_otg_struct_ptr = ( (usb_otg_max3353_call_struct_t *)otg_max3353_call_ptr)->otg_handle_ptr;
    
    bsp_usb_otg_max3353_clear_pin_int_flag();    
    OS_Event_set(usb_otg_struct_ptr->otg_isr_event, USB_OTG_MAX3353_ISR_EVENT);
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _usb_otg_max3353_preinit
* Returned Value   :
* Comments         : 
*    
*
*END*----------------------------------------------------------------------*/
usb_status usb_otg_max3353_preinit
(
    void*                      uplayer_handle,
    void** handle
)
{
    usb_otg_max3353_call_struct_t *    max3353_call_struct_ptr;
    
    max3353_call_struct_ptr =  (usb_otg_max3353_call_struct_t*)OS_Mem_alloc_zero(sizeof(usb_otg_max3353_call_struct_t));
    if (max3353_call_struct_ptr == NULL)
    {
        *handle = NULL;
        return USBERR_ALLOC;
    }
    max3353_call_struct_ptr->otg_handle_ptr = uplayer_handle;
    *handle = (void*)max3353_call_struct_ptr;
    
    return USB_OK;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : usb_otg_max3353_init
* Returned Value   :
* Comments         : 
*    
*
*END*----------------------------------------------------------------------*/
usb_status usb_otg_max3353_init
(
    void* handle
)
{  
    usb_otg_max3353_call_struct_t * otg_max3353_call_ptr = (usb_otg_max3353_call_struct_t*)handle;
    void* f_ptr = NULL;
    usb_otg_state_struct_t *    usb_otg_struct_ptr  = ( (usb_otg_max3353_call_struct_t *)otg_max3353_call_ptr)->otg_handle_ptr;
    int32_t param;
    int32_t status;

    otg_max3353_call_ptr->init_param_ptr = (usb_otg_max3353_init_struct_t*)bsp_usb_otg_get_peripheral_init_param(USB_OTG_PERIPHERAL_MAX3353);

    f_ptr = fopen (otg_max3353_call_ptr->init_param_ptr->i2c_dev_id, NULL);
    if(f_ptr == NULL)
    {
        return USBERR_ERROR;    
    }
    otg_max3353_call_ptr->i2c_f_ptr = f_ptr;
    param = 100000;
    status = ioctl (f_ptr, IO_IOCTL_I2C_SET_BAUD, &param);
    if(status != I2C_OK)
    {
        return USBERR_ERROR;
    }
    status = ioctl (f_ptr, IO_IOCTL_I2C_SET_MASTER_MODE, NULL);
    if(status != I2C_OK)
    {
        return USBERR_ERROR;
    }
    param = otg_max3353_call_ptr->init_param_ptr->i2c_address;
    status = ioctl (f_ptr, IO_IOCTL_I2C_SET_DESTINATION_ADDRESS, &param);
    if(status != I2C_OK)
    {
        return USBERR_ERROR;
    }
    bsp_usb_otg_max3353_set_pin_int(FALSE, TRUE);    
 
    OS_Event_set(usb_otg_struct_ptr->otg_isr_event, USB_OTG_MAX3353_ISR_EVENT);
    _usb_otg_max3353_enable_disable(f_ptr,TRUE);
    if (!(OS_install_isr(otg_max3353_call_ptr->init_param_ptr->int_vector, _usb_otg_max3353_isr, otg_max3353_call_ptr)))
    {
        return USBERR_INSTALL_ISR;
    }
    OS_intr_init(otg_max3353_call_ptr->init_param_ptr->int_vector,otg_max3353_call_ptr->init_param_ptr->priority,0,TRUE);
    return USB_OK;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : usb_otg_max3353_shut_down
* Returned Value   :
* Comments         : 
*    
*
*END*----------------------------------------------------------------------*/
usb_status usb_otg_max3353_shut_down
(
    void* handle
)
{
    usb_otg_max3353_call_struct_t * otg_max3353_call_ptr = (usb_otg_max3353_call_struct_t*)handle;
    usb_otg_state_struct_t *    usb_otg_struct_ptr  = ((usb_otg_max3353_call_struct_t *)otg_max3353_call_ptr)->otg_handle_ptr;

    bsp_usb_otg_max3353_set_pin_int(FALSE, FALSE);        
    _usb_otg_max3353_enable_disable(otg_max3353_call_ptr->i2c_f_ptr,FALSE);
    OS_Event_clear(usb_otg_struct_ptr->otg_isr_event, USB_OTG_MAX3353_ISR_EVENT);
    fclose(otg_max3353_call_ptr->i2c_f_ptr);
    return USB_OK;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : usb_otg_max3353_get_status
* Returned Value   :
* Comments         : 
*    
*
*END*----------------------------------------------------------------------*/
usb_status usb_otg_max3353_get_status
(
    void* handle
)
{
    usb_otg_max3353_call_struct_t * otg_max3353_call_ptr = (usb_otg_max3353_call_struct_t*)handle;
    uint8_t status;
    void* f_ptr;
    usb_otg_state_struct_t *    usb_otg_struct_ptr  = otg_max3353_call_ptr->otg_handle_ptr; 
    usb_otg_status_t *          otg_status_ptr      = &usb_otg_struct_ptr->otg_status;

    f_ptr = otg_max3353_call_ptr->i2c_f_ptr;
    /* read the active interrupts from the controller and the current status */
    while(_usb_otg_max3353_get_interrupts(f_ptr)){}
    status = _usb_otg_max3353_get_status(f_ptr);
    /* check the status indications */         
    /* ID status update */
    otg_status_ptr->id = (uint8_t)((status & OTG_STAT_ID_FLOAT) ? TRUE : FALSE);
    /* V_BUS_VALID status update */
    otg_status_ptr->vbus_valid = (uint8_t)((status & OTG_STAT_VBUS_VALID) ? TRUE : FALSE);
    /* SESS_VALID status update */
    otg_status_ptr->sess_valid = (uint8_t)((status & OTG_STAT_SESS_VALID) ? TRUE : FALSE);
    /* SESS_END status update */
    otg_status_ptr->sess_end = (uint8_t)((status & OTG_STAT_SESS_END) ? TRUE : FALSE);

    if(_usb_otg_max3353_get_interrupts(f_ptr) != 0)  
    {
        OS_Event_set(usb_otg_struct_ptr->otg_isr_event, USB_OTG_MAX3353_ISR_EVENT);  
    }  

    return USB_OK;
}
/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : usb_otg_max3353_set_vbus
* Returned Value   :
* Comments         : 
*    
*
*END*----------------------------------------------------------------------*/
usb_status usb_otg_max3353_set_vbus
(
    void* handle,
    bool enable
)
{
    usb_otg_max3353_call_struct_t * otg_max3353_call_ptr = (usb_otg_max3353_call_struct_t*)handle;
    _usb_otg_max3353_set_VBUS(otg_max3353_call_ptr->i2c_f_ptr,enable);
    return USB_OK;
}
/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : usb_otg_max3353_set_pull_downs
* Returned Value   :
* Comments         : 
*    
*
*END*----------------------------------------------------------------------*/
usb_status usb_otg_max3353_set_pull_downs
(
    void* handle, 
    uint8_t bitfield
)
{
    usb_otg_max3353_call_struct_t * otg_max3353_call_ptr = (usb_otg_max3353_call_struct_t*)handle;
    _usb_otg_max3353_set_pdowns(otg_max3353_call_ptr->i2c_f_ptr, bitfield);
    return USB_OK;
}
/* EOF */
