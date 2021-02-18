/**************************************************************************//**
 * @file     system_M471M_R1_S.c
 * @version  V0.10
 * $Revision: 11 $
 * $Date: 15/09/02 10:02a $
 * @brief    CMSIS Cortex-M4 Core Peripheral Access Layer Source File for M471M_R1_S
 *
 * @note
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include "M471M_R1_S.h"


/*----------------------------------------------------------------------------
  DEFINES
 *----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock  = __SYSTEM_CLOCK;    /*!< System Clock Frequency (Core Clock)*/
uint32_t CyclesPerUs      = (__HSI / 1000000); /* Cycles per micro second */
uint32_t PllClock         = __HSI;             /*!< PLL Output Clock Frequency         */
uint32_t gau32ClkSrcTbl[] = {__HXT, __LXT, 0, __LIRC, 0, 0, 0, __HIRC};

/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate(void)             /* Get Core Clock Frequency      */
{
}

/**
 * Initialize the system
 *
 * @param  None
 * @return None
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void SystemInit(void)
{
    /* ToDo: add code to initialize the system
             do not use global variables because this function is called before
             reaching pre-main. RW section maybe overwritten afterwards.          */

    SYS_UnlockReg();
    /* One-time POR18 */
    if((SYS->PDID >> 12) == 0x945)
    {
        M32(GCR_BASE+0x14) |= BIT7;
    }
    /* Force to use INV type with HXT */
    CLK->PWRCTL &= ~CLK_PWRCTL_HXTSELTYP_Msk;
    SYS_LockReg();


#ifdef EBI_INIT
    extern void SYS_Init();
    extern void EBI_Init();

    SYS_UnlockReg();
    SYS_Init();
    EBI_Init();
    SYS_LockReg();
#endif

    /* FPU settings ------------------------------------------------------------*/
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10 * 2) |               /* set CP10 Full Access */
                   (3UL << 11 * 2));               /* set CP11 Full Access */
#endif

}

