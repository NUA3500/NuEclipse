/**************************************************************************//**
 * @file     system_M030G.h
 * @version  V3.00
 * $Revision: 5 $
 * $Date: 20/06/11 3:42p $
 * @brief    M030G Series System Setting Header File
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#ifndef __SYSTEM_M030G_H__
#define __SYSTEM_M030G_H__

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------------------------------------*/
/* Macro Definition                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
#ifndef DEBUG_PORT
#define DEBUG_PORT      UART0       /*!< Select Debug Port which is used for retarget.c to output debug message to UART */
#endif


/**
 *
 * @details    This is used to enable PLL to speed up booting at startup. Remove it will cause system using
 *             default clock source (External crystal or internal 22.1184MHz IRC).
 *             Enable this option will cause system booting in 72MHz(By XTAL) or 71.8848MHz(By IRC22M) according to
 *             user configuration setting in CONFIG0
 *
 */

/*----------------------------------------------------------------------------
  Define SYSCLK
 *----------------------------------------------------------------------------*/
#define __HXT       (12000000UL)    /*!< External Crystal Clock Frequency     */
#define __LIRC      (38400UL)       /*!< Internal 38.4KHz RC Oscillator Frequency */
#define __HIRC      (48000000UL)    /*!< Internal 48M RC Oscillator Frequency */
#define __LXT       (32768UL)       /*!< External Crystal Clock Frequency 32.768KHz */
#define __HSI       (48000000UL)    /*!< Default output is 48MHz for HIRC */

extern uint32_t SystemCoreClock;    /*!< System Clock Frequency (Core Clock)  */
extern uint32_t CyclesPerUs;        /*!< Cycles per micro second              */

#if USE_ASSERT
/**
 * @brief      Assert Function
 *
 * @param[in]  expr  Expression to be evaluated
 *
 * @return     None
 *
 * @details    If the expression is false, an error message will be printed out
 *             from debug port (UART0 or UART1).
 */
#define ASSERT_PARAM(expr)  { if (!(expr)) { AssertError((uint8_t*)__FILE__, __LINE__); } }

void AssertError(uint8_t* file, uint32_t line);
#else
#define ASSERT_PARAM(expr)
#endif

#define assert_param(expr)  ASSERT_PARAM(expr)


/**
 * @brief    System Initialization
 *
 * @param    None
 *
 * @return   None
 *
 * @details  The necessary initialization of system.
 */
extern void SystemInit(void);


/**
 * @brief    Update the Variable SystemCoreClock
 *
 * @param    None
 *
 * @return   None
 *
 * @details  This function is used to update the variable SystemCoreClock
 *           and must be called whenever the core clock is changed.
 */
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif

/* Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved. */
