/**HEADER********************************************************************
* 
* Copyright (c) 2013 - 2015 Freescale Semiconductor;
* All Rights Reserved
*
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
* Comments:  
*
*END************************************************************************/
#include "adapter.h"
#include "usb.h"
#include "usb_host_config.h"
#include "usb_misc.h"
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
#include "MVF61NS151MK50.h"
#endif

extern uint8_t soc_get_usb_vector_number(uint8_t controller_id);
extern uint32_t soc_get_usb_base_address(uint8_t controller_id);
#ifdef __cplusplus
extern "C" {
#endif
extern _WEAK_FUNCTION(usb_status bsp_usb_host_board_init(uint8_t controller_id));
#ifdef __cplusplus
           }
#endif
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX) || (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM) || (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)
#define BSP_USB_INT_LEVEL                (3)


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : bsp_usb_host_soc_init
* Returned Value   : USB status
* Comments         :
*    This function performs BSP-specific I/O initialization related to USB
*
*END*----------------------------------------------------------------------*/
static usb_status bsp_usb_host_soc_init
(
   int32_t controller_id
)
{
    usb_status ret = 0;
    /* Setup clocking and PLL */
    CCM_CLPCR &= ~CCM_CLPCR_SBYOS_MASK; //on-chip oscillator on (by default after reset)
    //Setup 3V0 regulator
    ANADIG_REG_3P0 |= ANADIG_REG_3P0_ENABLE_BO_MASK;
    ANADIG_REG_3P0 |= ANADIG_REG_3P0_ENABLE_LINREG_MASK;
    while(!( ANADIG_REG_3P0 & ANADIG_REG_3P0_OK_VDD3P0_MASK))
    { /* wait till regulator output is in steady state */ }

    if (USB_CONTROLLER_EHCI_0 == controller_id)
    {
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
        /* For USB0 */
        // enable USB0 clock gate
        CCM_CCGR1 |= CCM_CCGR1_CG4(0x3);

        ANADIG_PLL3_CTRL &= ~ANADIG_PLL3_CTRL_BYPASS_CLK_SRC_MASK; //the source of clock is 24MHz XTAL CLK
        ANADIG_PLL3_CTRL &= ~ANADIG_PLL3_CTRL_BYPASS_MASK; //do not bypass the PLL
        ANADIG_PLL3_CTRL |= ANADIG_PLL3_CTRL_POWER_MASK; //power the USB0 PLL
        ANADIG_PLL3_CTRL |= ANADIG_PLL3_CTRL_EN_USB_CLKS_MASK; //start clocking PHY UTMI peripheral

        /* Setup PHY0 peripheral with UTMI interface */
        USBPHY0_CTRL_CLR = USBPHY_CTRL_SFTRST_MASK | USBPHY_CTRL_CLKGATE_MASK; //leave the reset state on PHY and run clocks
        USBPHY0_DEBUG_CLR = USBPHY_DEBUG_CLKGATE_MASK;
        USBPHY0_CTRL_SET = USBPHY_CTRL_ENUTMILEVEL3_MASK | USBPHY_CTRL_ENUTMILEVEL2_MASK;

        USBPHY0_IP_SET = (3 << 17); //enable bugfix for resume signaling

        USBPHY0_PWD = 0; //switch PHY from standby to normal operation
#endif
    }
    else if (USB_CONTROLLER_EHCI_1 == controller_id)
    {
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
        /* For USB1 */
        // enable USB1 clock gate
        CCM_CCGR7 |= CCM_CCGR7_CG4(0x3);

        ANADIG_PLL7_CTRL &= ~ANADIG_PLL7_CTRL_BYPASS_CLK_SRC_MASK; //the source of clock is 24MHz XTAL CLK
        ANADIG_PLL7_CTRL &= ~ANADIG_PLL7_CTRL_BYPASS_MASK; //do not bypass the PLL
        ANADIG_PLL7_CTRL |= ANADIG_PLL7_CTRL_POWER_MASK; //power the USB1 PLL
        ANADIG_PLL7_CTRL |= ANADIG_PLL7_CTRL_EN_USB_CLKS_MASK; //power the USB1 PHY

        /* Setup PHY1 peripheral with UTMI interface */
        USBPHY1_CTRL_CLR = USBPHY_CTRL_SFTRST_MASK | USBPHY_CTRL_CLKGATE_MASK; //leave the reset state on PHY and run clocks
        USBPHY1_DEBUG_CLR = USBPHY_DEBUG_CLKGATE_MASK;
        USBPHY1_CTRL_SET = USBPHY_CTRL_ENUTMILEVEL3_MASK | USBPHY_CTRL_ENUTMILEVEL2_MASK;

        USBPHY1_IP_SET = (3 << 17); //enable bugfix for resume signaling

        USBPHY1_PWD = 0; //switch PHY from standby to normal operation
        USBC1_CTRL |= USBC_CTRL_PM_MASK;
#endif
    }
    else
    {
        ret = USBERR_BAD_STATUS; //unknown controller
    }
    if(USB_OK == ret)
    {
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
        USB_MemMapPtr usb_ptr;
        usb_ptr = (USB_MemMapPtr)soc_get_usb_base_address(controller_id);
        USB_USBCMD_REG(usb_ptr) &= ~USB_USBCMD_RS_MASK;
        while (USB_USBCMD_REG(usb_ptr) & USB_USBCMD_RS_MASK);
        { /* delay while resetting USB controller */ }
        USB_USBCMD_REG(usb_ptr) |= USB_USBCMD_RST_MASK;
        while (USB_USBCMD_REG(usb_ptr) & USB_USBCMD_RST_MASK)
        { /* delay while resetting USB controller */ }

        USB_USBMODE_REG(usb_ptr) = USB_USBMODE_CM_MASK;
        USB_USBCMD_REG(usb_ptr) = USB_USBCMD_ASP(3) | USB_USBCMD_ITC(0);

        /* setup interrupt */
        OS_intr_init(soc_get_usb_vector_number(controller_id), BSP_USB_INT_LEVEL, 0, TRUE);
#endif
    }
    return ret;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : bsp_usb_host_board_init
* Returned Value   : USB status
* Comments         :
*    This function performs board-specific initialization related to USB
*
*END*----------------------------------------------------------------------*/
_WEAK_FUNCTION(usb_status bsp_usb_host_board_init(uint8_t controller_id))
{
    usb_status ret = USB_OK;
    
    if (USB_CONTROLLER_EHCI_0 == controller_id)
    {
#if USBCFG_HOST_PORT_NATIVE
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
        /* Setup PTD6 (control of USB0 VBUS) to power the bus */
        GPIO2_PSOR = 1 << 21; //set output level of PTD6 to "1"
        IOMUXC_RGPIO(85) = IOMUXC_SW_MUX_CTL_PAD_PAD_MUX_MODE(0) | IOMUXC_SW_MUX_CTL_PAD_PAD_SPEED(0) | IOMUXC_SW_MUX_CTL_PAD_PAD_SRE_MASK | IOMUXC_SW_MUX_CTL_PAD_PAD_DSE(3) | IOMUXC_SW_MUX_CTL_PAD_PAD_OBE_MASK;
#endif
#endif
    }
    else if (USB_CONTROLLER_EHCI_1 == controller_id)
    {
#if USBCFG_HOST_PORT_NATIVE
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
        /* Setup PTD13 (control of USB1 VBUS) to power the bus */
        GPIO2_PSOR = 1 << 28; //set output level of PTD13 to "1"
        IOMUXC_RGPIO(92) = IOMUXC_SW_MUX_CTL_PAD_PAD_MUX_MODE(0) | IOMUXC_SW_MUX_CTL_PAD_PAD_SPEED(0) | IOMUXC_SW_MUX_CTL_PAD_PAD_SRE_MASK | IOMUXC_SW_MUX_CTL_PAD_PAD_DSE(3) | IOMUXC_SW_MUX_CTL_PAD_PAD_OBE_MASK;
#endif
#endif
    }
    else
    {
        ret = USBERR_BAD_STATUS;
    }
    
    return ret;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : bsp_usb_host_init
* Returned Value   : USB status
* Comments         :
*    This function performs BSP-specific initialization related to USB
*
*END*----------------------------------------------------------------------*/
usb_status bsp_usb_host_init(uint8_t controller_id)
{
    usb_status ret = USB_OK;
    
    ret = bsp_usb_host_soc_init(controller_id);
    if (ret == USB_OK)
    {
        ret = bsp_usb_host_board_init(controller_id);
    }
    return ret;
}


#if USBCFG_EHCI_HS_DISCONNECT_ENABLE
void bsp_usb_hs_disconnect_detection_enable(uint8_t controller_id)
{
    if (controller_id == USB_CONTROLLER_KHCI_0)
    {
    }
    else if (controller_id == USB_CONTROLLER_EHCI_0)
    {
        USBPHY0_CTRL_SET = USBPHY_CTRL_ENHOSTDISCONDETECT_MASK;
    }
    else if (controller_id == USB_CONTROLLER_EHCI_1)
    {
        USBPHY1_CTRL_SET = USBPHY_CTRL_ENHOSTDISCONDETECT_MASK;
    }
    else
    {
    }
}

void bsp_usb_hs_disconnect_detection_disable(uint8_t controller_id)
{
    if (controller_id == USB_CONTROLLER_KHCI_0)
    {
    }
    else if (controller_id == USB_CONTROLLER_EHCI_0)
    {
        USBPHY0_CTRL_CLR = USBPHY_CTRL_ENHOSTDISCONDETECT_MASK;
    }
    else if (controller_id == USB_CONTROLLER_EHCI_1)
    {
        USBPHY1_CTRL_CLR = USBPHY_CTRL_ENHOSTDISCONDETECT_MASK;
    }
    else
    {
    }
}
#endif
#endif
/* EOF */
