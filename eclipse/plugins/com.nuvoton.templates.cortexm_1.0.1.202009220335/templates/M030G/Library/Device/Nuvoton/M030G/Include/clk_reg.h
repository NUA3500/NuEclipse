/**************************************************************************//**
 * @file     clk_reg.h
 * @version  V1.00
 * @brief    CLK register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __CLK_REG_H__
#define __CLK_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup CLK System Clock Controller (CLK)
    Memory Mapped Structure for CLK Controller
@{ */

typedef struct
{
    /**
     * @var CLK_T::PWRCTL
     * Offset: 0x00  System Power-down Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2]     |HIRCEN    |HIRC Enable Bit (Write Protect)
     * |        |          |0 = Internal high speed RC oscillator (HIRC) Disabled.
     * |        |          |1 = Internal high speed RC oscillator (HIRC) Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[4]     |PDWKDLY   |Enable the Wake-up Delay Counter (Write Protect)
     * |        |          |When the chip wakes up from Power-down mode, the clock control will delay certain clock cycles to wait system clock stable.
     * |        |          |The delayed clock cycle is 512 clock cycles when chip works at internal high speed RC oscillator (HIRC).
     * |        |          |0 = Clock cycles delay Disabled.
     * |        |          |1 = Clock cycles delay Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[5]     |PDWKIEN   |Power-down Mode Wake-up Interrupt Enable Bit (Write Protect)
     * |        |          |0 = Power-down mode wake-up interrupt Disabled.
     * |        |          |1 = Power-down mode wake-up interrupt Enabled.
     * |        |          |Note1: The interrupt will occur when both PDWKIF and PDWKIEN are high.
     * |        |          |Note2: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[6]     |PDWKIF    |Power-down Mode Wake-up Interrupt Status
     * |        |          |Set by "Power-down wake-up event", it indicates that resume from Power-down mode.
     * |        |          |The flag is set if any wake-up source is occurred. Refer Power Modes and Wake-up Sources chapter.
     * |        |          |Note1: Write 1 to clear the bit to 0.
     * |        |          |Note2: This bit works only if PDWKIEN (CLK_PWRCTL[5]) set to 1.
     * |[7]     |PDEN      |System Power-down Enable (Write Protect)
     * |        |          |When this bit is set to 1, Power-down mode is enabled and chip keeps active till the CPU sleep mode is also active and then the chip enters Power-down mode.
     * |        |          |When chip wakes up from Power-down mode, this bit is auto cleared
     * |        |          |Users need to set this bit again for next Power-down.
     * |        |          |In Power-down mode, the HIRC will be disabled in this mode, but LIRC are not controlled by Power-down mode
     * |        |          |If user disable LIRC before entering power-down mode, this bit should be set after LIRC disabled 50us(1T LIRC).
     * |        |          |The clocks of peripheral are not controlled by Power-down mode, if the peripheral clock source is from LIRC.
     * |        |          |0 = Chip operating normally or chip in idle mode because of WFI command.
     * |        |          |1 = Chip enters Power-down mode instant or wait CPU sleep command WFI.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * @var CLK_T::AHBCLK
     * Offset: 0x04  AHB Devices Clock Enable Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1]     |PDMACKEN  |PDMA Controller Clock Enable Bit
     * |        |          |0 = PDMA peripheral clock Disabled.
     * |        |          |1 = PDMA peripheral clock Enabled.
     * |[2]     |ISPCKEN   |Flash ISP Controller Clock Enable Bit
     * |        |          |0 = Flash ISP peripheral clock Disabled.
     * |        |          |1 = Flash ISP peripheral clock Enabled.
     * |[7]     |CRCCKEN   |CRC Generator Controller Clock Enable Bit
     * |        |          |0 = CRC peripheral clock Disabled.
     * |        |          |1 = CRC peripheral clock Enabled.
     * @var CLK_T::APBCLK0
     * Offset: 0x08  APB Devices Clock Enable Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WDTCKEN   |Watchdog Timer Clock Enable Bit (Write Protect)
     * |        |          |0 = Watchdog timer clock Disabled.
     * |        |          |1 = Watchdog timer clock Enabled.
     * |        |          |Note1: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note2: This bit is reset by power on reset, Watchdog reset or software chip reset.
     * |[2]     |TMR0CKEN  |Timer0 Clock Enable Bit
     * |        |          |0 = Timer0 clock Disabled.
     * |        |          |1 = Timer0 clock Enabled.
     * |[3]     |TMR1CKEN  |Timer1 Clock Enable Bit
     * |        |          |0 = Timer1 clock Disabled.
     * |        |          |1 = Timer1 clock Enabled.
     * |[6]     |CLKOCKEN  |CLKO Clock Enable Bit
     * |        |          |0 = CLKO clock Disabled.
     * |        |          |1 = CLKO clock Enabled.
     * |[8]     |I2C0CKEN  |I2C0 Clock Enable Bit
     * |        |          |0 = I2C0 clock Disabled.
     * |        |          |1 = I2C0 clock Enabled.
     * |[9]     |I2C1CKEN  |I2C1 Clock Enable Bit
     * |        |          |0 = I2C1 clock Disabled.
     * |        |          |1 = I2C1 clock Enabled.
     * |[13]    |SPI0CKEN  |SPI0 Clock Enable Bit
     * |        |          |0 = SPI0 clock Disabled.
     * |        |          |1 = SPI0 clock Enabled.
     * |[16]    |UART0CKEN |UART0 Clock Enable Bit
     * |        |          |0 = UART0 clock Disabled.
     * |        |          |1 = UART0 clock Enabled.
     * |[28]    |ADCCKEN   |ADC Clock Enable Bit
     * |        |          |0 = ADC clock Disabled.
     * |        |          |1 = ADC clock Enabled.
     * @var CLK_T::APBCLK1
     * Offset: 0x0C  APB Devices Clock Enable Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[12]    |DAC01CKEN |DAC01 Clock Enable Bit
     * |        |          |0 = DAC01 clock Disabled.
     * |        |          |1 = DAC01 clock Enabled.
     * |[13]    |DAC23CKEN |DAC23 Clock Enable Bit
     * |        |          |0 = DAC23 clock Disabled.
     * |        |          |1 = DAC23 clock Enabled.
     * |[19]    |BPWM1CKEN |BPWM1 Clock Enable Bit
     * |        |          |0 = BPWM1 clock Disabled.
     * |        |          |1 = BPWM1 clock Enabled.
     * @var CLK_T::CLKSEL0
     * Offset: 0x10  Clock Source Select Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |HCLKSEL   |HCLK Clock Source Selection (Write Protect)
     * |        |          |Before clock switching, the related clock sources (both pre-select and new-select) must be turned on.
     * |        |          |111= Clock source from HIRC.
     * |        |          |Other = Reserved.
     * |        |          |Note1: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note2: Reset by power on reset.
     * |[5:3]   |STCLKSEL  |Cortex-M0 SysTick Clock Source Selection (Write Protect)
     * |        |          |If SYST_CTRL[2]=0, SysTick uses listed clock source below.
     * |        |          |011 = Clock source from HCLK/2.
     * |        |          |111 = Clock source from HIRC/2.
     * |        |          |Other = Reserved.
     * |        |          |Note1: if SysTick clock source is not from HCLK (i.e. SYST_CTRL[2] = 0), SysTick clock source must less than or equal to HCLK/2.
     * |        |          |Note2: This bit is write protected. Refer to the SYS_REGLCTL register.
     * @var CLK_T::CLKSEL1
     * Offset: 0x14  Clock Source Select Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |WDTSEL    |Watchdog Timer Clock Source Selection (Write Protect)
     * |        |          |10 = Clock source from HCLK/2048.
     * |        |          |11 = Clock source from internal low speed RC oscillator (LIRC).
     * |        |          |Note1: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note2: Will be forced to 11 when CONFIG0[31], CONFIG0[4], CONFIG0[3] are all ones.
     * |[3:2]   |WWDTSEL   |Window Watchdog Timer Clock Source Selection (Write Protect)
     * |        |          |10 = Clock source from HCLK/2048.
     * |        |          |11 = Clock source from internal low speed RC oscillator (LIRC).
     * |        |          |Others = Reserved.
     * |[6:4]   |CLKOSEL   |Clock Divider Clock Source Selection
     * |        |          |010 = Clock source from HCLK.
     * |        |          |011 = Clock source from internal high speed RC oscillator (HIRC).
     * |        |          |100 = Clock source from internal low speed RC oscillator (LIRC).
     * |        |          |101 = Clock source from internal high speed RC oscillator (HIRC).
     * |[10:8]  |TMR0SEL   |TIMER0 Clock Source Selection
     * |        |          |010 = Clock source from PCLK0.
     * |        |          |011 = Clock source from external clock T0 pin.
     * |        |          |101 = Clock source from internal low speed RC oscillator (LIRC).
     * |        |          |111 = Clock source from internal high speed RC oscillator (HIRC).
     * |[14:12] |TMR1SEL   |TIMER1 Clock Source Selection
     * |        |          |010 = Clock source from PCLK0.
     * |        |          |011 = Clock source from external clock T1 pin.
     * |        |          |101 = Clock source from internal low speed RC oscillator (LIRC).
     * |        |          |111 = Clock source from internal high speed RC oscillator (HIRC).
     * |        |          |Others = Reserved.
     * |[26:24] |UART0SEL  |UART0 Clock Source Selection
     * |        |          |011 = Clock source from internal high speed RC oscillator (HIRC).
     * |        |          |100 = Clock source from PCLK0.
     * |        |          |101 = Clock source from internal low speed RC oscillator (LIRC).
     * |        |          |Other = Reserved.
     * @var CLK_T::CLKSEL2
     * Offset: 0x18  Clock Source Select Control Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:4]   |SPI0SEL   |SPI0 Clock Source Selection
     * |        |          |10 = Clock source from PCLK1.
     * |        |          |11 = Clock source from internal high speed RC oscillator (HIRC).
     * |        |          |Others = Reserved.
     * |[21:20] |ADCSEL    |ADC Clock Source Selection
     * |        |          |10 = Clock source from PCLK1.
     * |        |          |11 = Clock source from internal high speed RC oscillator (HIRC) clock.
     * |        |          |Others = Reserved.
     * |        |          |Note1: If PLL is not supported, clock source of selection "01" will be changed to PCLK1.
     * |        |          |Note2: If HXT is not supported, clock source of selection "00" will be stopped.
     * @var CLK_T::CLKDIV0
     * Offset: 0x20  Clock Divider Number Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |HCLKDIV   |HCLK Clock Divide Number From HCLK Clock Source
     * |        |          |HCLK clock frequency = (HCLK clock source frequency) / (HCLKDIV + 1).
     * |[11:8]  |UART0DIV  |UART0 Clock Divide Number From UART0 Clock Source
     * |        |          |UART0 clock frequency = (UART0 clock source frequency) / (UART0DIV + 1).
     * |[23:16] |ADCDIV    |ADC Clock Divide Number From ADC Clock Source
     * |        |          |ADC clock frequency = (ADC clock source frequency) / (ADCDIV + 1).
     * @var CLK_T::PCLKDIV
     * Offset: 0x34  APB Clock Divider Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |APB0DIV   |APB0 Clock DIvider
     * |        |          |APB0 clock can be divided from HCLK.
     * |        |          |000 = PCLK0 = HCLK.
     * |        |          |001 = PCLK0 = 1/2 HCLK.
     * |        |          |010 = PCLK0 = 1/4 HCLK.
     * |        |          |011 = PCLK0 = 1/8 HCLK.
     * |        |          |100 = PCLK0 = 1/16 HCLK.
     * |        |          |Others = Reserved.
     * |[6:4]   |APB1DIV   |APB1 Clock DIvider
     * |        |          |APB1 clock can be divided from HCLK.
     * |        |          |000 = PCLK1 = HCLK.
     * |        |          |001 = PCLK1 = 1/2 HCLK.
     * |        |          |010 = PCLK1 = 1/4 HCLK.
     * |        |          |011 = PCLK1 = 1/8 HCLK.
     * |        |          |100 = PCLK1 = 1/16 HCLK.
     * |        |          |Others = Reserved.
     * @var CLK_T::STATUS
     * Offset: 0x50  Clock Status Monitor Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3]     |LIRCSTB   |LIRC Clock Source Stable Flag (Read Only)
     * |        |          |0 = Internal low speed RC oscillator (LIRC) clock is not stable or disabled.
     * |        |          |1 = Internal low speed RC oscillator (LIRC) clock is stable and enabled.
     * |[4]     |HIRCSTB   |HIRC Clock Source Stable Flag (Read Only)
     * |        |          |0 = Internal high speed RC oscillator (HIRC) clock is not stable or disabled.
     * |        |          |1 = Internal high speed RC oscillator (HIRC) clock is stable and enabled.
     * |[7]     |CLKSFAIL  |Clock Switching Fail Flag (Read Only)
     * |        |          |This bit is updated when software switches system clock source. If switch target clock is stable, this bit will be set to 0. If switch target clock is not stable, this bit will be set to 1.
     * |        |          |0 = Clock switching success.
     * |        |          |1 = Clock switching failure.
     * |        |          |Note: Write 1 to clear the bit to 0.
     * @var CLK_T::CLKOCTL
     * Offset: 0x60  Clock Output Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |FREQSEL   |Clock Output Frequency Selection
     * |        |          |The formula of output frequency is
     * |        |          |Fout = Fin/(2^(N+1)).
     * |        |          |Fin is the input clock frequency.
     * |        |          |Fout is the frequency of divider output clock.
     * |        |          |N is the 4-bit value of FREQSEL[3:0].
     * |[4]     |CLKOEN    |Clock Output Enable Bit
     * |        |          |0 = Clock Output function Disabled.
     * |        |          |1 = Clock Output function Enabled.
     * |[5]     |DIV1EN    |Clock Output Divide One Enable Bit
     * |        |          |0 = Clock Output will output clock with source frequency divided by FREQSEL.
     * |        |          |1 = Clock Output will output clock with source frequency.
     */
    __IO uint32_t PWRCTL;                /*!< [0x0000] System Power-down Control Register                               */
    __IO uint32_t AHBCLK;                /*!< [0x0004] AHB Devices Clock Enable Control Register                        */
    __IO uint32_t APBCLK0;               /*!< [0x0008] APB Devices Clock Enable Control Register 0                      */
    __IO uint32_t APBCLK1;               /*!< [0x000c] APB Devices Clock Enable Control Register 1                      */
    __IO uint32_t CLKSEL0;               /*!< [0x0010] Clock Source Select Control Register 0                           */
    __IO uint32_t CLKSEL1;               /*!< [0x0014] Clock Source Select Control Register 1                           */
    __IO uint32_t CLKSEL2;               /*!< [0x0018] Clock Source Select Control Register 2                           */
    __I  uint32_t RESERVE0[1];
    __IO uint32_t CLKDIV0;               /*!< [0x0020] Clock Divider Number Register 0                                  */
    __I  uint32_t RESERVE1[4];
    __IO uint32_t PCLKDIV;               /*!< [0x0034] APB Clock Divider Register                                       */
    __I  uint32_t RESERVE2[6];
    __I  uint32_t STATUS;                /*!< [0x0050] Clock Status Monitor Register                                    */
    __I  uint32_t RESERVE3[3];
    __IO uint32_t CLKOCTL;               /*!< [0x0060] Clock Output Control Register                                    */
} CLK_T;

/**
    @addtogroup CLK_CONST CLK Bit Field Definition
    Constant Definitions for CLK Controller
@{ */

#define CLK_PWRCTL_HIRCEN_Pos            (2)                                               /*!< CLK_T::PWRCTL: HIRCEN Position         */
#define CLK_PWRCTL_HIRCEN_Msk            (0x1ul << CLK_PWRCTL_HIRCEN_Pos)                  /*!< CLK_T::PWRCTL: HIRCEN Mask             */

#define CLK_PWRCTL_PDWKDLY_Pos           (4)                                               /*!< CLK_T::PWRCTL: PDWKDLY Position        */
#define CLK_PWRCTL_PDWKDLY_Msk           (0x1ul << CLK_PWRCTL_PDWKDLY_Pos)                 /*!< CLK_T::PWRCTL: PDWKDLY Mask            */

#define CLK_PWRCTL_PDWKIEN_Pos           (5)                                               /*!< CLK_T::PWRCTL: PDWKIEN Position        */
#define CLK_PWRCTL_PDWKIEN_Msk           (0x1ul << CLK_PWRCTL_PDWKIEN_Pos)                 /*!< CLK_T::PWRCTL: PDWKIEN Mask            */

#define CLK_PWRCTL_PDWKIF_Pos            (6)                                               /*!< CLK_T::PWRCTL: PDWKIF Position         */
#define CLK_PWRCTL_PDWKIF_Msk            (0x1ul << CLK_PWRCTL_PDWKIF_Pos)                  /*!< CLK_T::PWRCTL: PDWKIF Mask             */

#define CLK_PWRCTL_PDEN_Pos              (7)                                               /*!< CLK_T::PWRCTL: PDEN Position           */
#define CLK_PWRCTL_PDEN_Msk              (0x1ul << CLK_PWRCTL_PDEN_Pos)                    /*!< CLK_T::PWRCTL: PDEN Mask               */

#define CLK_AHBCLK_PDMACKEN_Pos          (1)                                               /*!< CLK_T::AHBCLK: PDMACKEN Position       */
#define CLK_AHBCLK_PDMACKEN_Msk          (0x1ul << CLK_AHBCLK_PDMACKEN_Pos)                /*!< CLK_T::AHBCLK: PDMACKEN Mask           */

#define CLK_AHBCLK_ISPCKEN_Pos           (2)                                               /*!< CLK_T::AHBCLK: ISPCKEN Position        */
#define CLK_AHBCLK_ISPCKEN_Msk           (0x1ul << CLK_AHBCLK_ISPCKEN_Pos)                 /*!< CLK_T::AHBCLK: ISPCKEN Mask            */

#define CLK_AHBCLK_CRCCKEN_Pos           (7)                                               /*!< CLK_T::AHBCLK: CRCCKEN Position        */
#define CLK_AHBCLK_CRCCKEN_Msk           (0x1ul << CLK_AHBCLK_CRCCKEN_Pos)                 /*!< CLK_T::AHBCLK: CRCCKEN Mask            */

#define CLK_APBCLK0_WDTCKEN_Pos          (0)                                               /*!< CLK_T::APBCLK0: WDTCKEN Position       */
#define CLK_APBCLK0_WDTCKEN_Msk          (0x1ul << CLK_APBCLK0_WDTCKEN_Pos)                /*!< CLK_T::APBCLK0: WDTCKEN Mask           */

#define CLK_APBCLK0_TMR0CKEN_Pos         (2)                                               /*!< CLK_T::APBCLK0: TMR0CKEN Position      */
#define CLK_APBCLK0_TMR0CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR0CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR0CKEN Mask          */

#define CLK_APBCLK0_TMR1CKEN_Pos         (3)                                               /*!< CLK_T::APBCLK0: TMR1CKEN Position      */
#define CLK_APBCLK0_TMR1CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR1CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR1CKEN Mask          */

#define CLK_APBCLK0_CLKOCKEN_Pos         (6)                                               /*!< CLK_T::APBCLK0: CLKOCKEN Position      */
#define CLK_APBCLK0_CLKOCKEN_Msk         (0x1ul << CLK_APBCLK0_CLKOCKEN_Pos)               /*!< CLK_T::APBCLK0: CLKOCKEN Mask          */

#define CLK_APBCLK0_I2C0CKEN_Pos         (8)                                               /*!< CLK_T::APBCLK0: I2C0CKEN Position      */
#define CLK_APBCLK0_I2C0CKEN_Msk         (0x1ul << CLK_APBCLK0_I2C0CKEN_Pos)               /*!< CLK_T::APBCLK0: I2C0CKEN Mask          */

#define CLK_APBCLK0_I2C1CKEN_Pos         (9)                                               /*!< CLK_T::APBCLK0: I2C1CKEN Position      */
#define CLK_APBCLK0_I2C1CKEN_Msk         (0x1ul << CLK_APBCLK0_I2C1CKEN_Pos)               /*!< CLK_T::APBCLK0: I2C1CKEN Mask          */

#define CLK_APBCLK0_SPI0CKEN_Pos         (13)                                              /*!< CLK_T::APBCLK0: SPI0CKEN Position      */
#define CLK_APBCLK0_SPI0CKEN_Msk         (0x1ul << CLK_APBCLK0_SPI0CKEN_Pos)               /*!< CLK_T::APBCLK0: SPI0CKEN Mask          */

#define CLK_APBCLK0_UART0CKEN_Pos        (16)                                              /*!< CLK_T::APBCLK0: UART0CKEN Position     */
#define CLK_APBCLK0_UART0CKEN_Msk        (0x1ul << CLK_APBCLK0_UART0CKEN_Pos)              /*!< CLK_T::APBCLK0: UART0CKEN Mask         */

#define CLK_APBCLK0_ADCCKEN_Pos          (28)                                              /*!< CLK_T::APBCLK0: ADCCKEN Position       */
#define CLK_APBCLK0_ADCCKEN_Msk          (0x1ul << CLK_APBCLK0_ADCCKEN_Pos)                /*!< CLK_T::APBCLK0: ADCCKEN Mask           */

#define CLK_APBCLK1_DAC01CKEN_Pos        (12)                                              /*!< CLK_T::APBCLK1: DAC01CKEN Position     */
#define CLK_APBCLK1_DAC01CKEN_Msk        (0x1ul << CLK_APBCLK1_DAC01CKEN_Pos)              /*!< CLK_T::APBCLK1: DAC01CKEN Mask         */

#define CLK_APBCLK1_DAC23CKEN_Pos        (13)                                              /*!< CLK_T::APBCLK1: DAC23CKEN Position     */
#define CLK_APBCLK1_DAC23CKEN_Msk        (0x1ul << CLK_APBCLK1_DAC23CKEN_Pos)              /*!< CLK_T::APBCLK1: DAC23CKEN Mask         */

#define CLK_APBCLK1_BPWM1CKEN_Pos        (19)                                              /*!< CLK_T::APBCLK1: BPWM1CKEN Position     */
#define CLK_APBCLK1_BPWM1CKEN_Msk        (0x1ul << CLK_APBCLK1_BPWM1CKEN_Pos)              /*!< CLK_T::APBCLK1: BPWM1CKEN Mask         */

#define CLK_CLKSEL0_HCLKSEL_Pos          (0)                                               /*!< CLK_T::CLKSEL0: HCLKSEL Position       */
#define CLK_CLKSEL0_HCLKSEL_Msk          (0x7ul << CLK_CLKSEL0_HCLKSEL_Pos)                /*!< CLK_T::CLKSEL0: HCLKSEL Mask           */

#define CLK_CLKSEL0_STCLKSEL_Pos         (3)                                               /*!< CLK_T::CLKSEL0: STCLKSEL Position      */
#define CLK_CLKSEL0_STCLKSEL_Msk         (0x7ul << CLK_CLKSEL0_STCLKSEL_Pos)               /*!< CLK_T::CLKSEL0: STCLKSEL Mask          */

#define CLK_CLKSEL1_WDTSEL_Pos           (0)                                               /*!< CLK_T::CLKSEL1: WDTSEL Position        */
#define CLK_CLKSEL1_WDTSEL_Msk           (0x3ul << CLK_CLKSEL1_WDTSEL_Pos)                 /*!< CLK_T::CLKSEL1: WDTSEL Mask            */

#define CLK_CLKSEL1_WWDTSEL_Pos          (2)                                               /*!< CLK_T::CLKSEL1: WWDTSEL Position       */
#define CLK_CLKSEL1_WWDTSEL_Msk          (0x3ul << CLK_CLKSEL1_WWDTSEL_Pos)                /*!< CLK_T::CLKSEL1: WWDTSEL Mask           */

#define CLK_CLKSEL1_CLKOSEL_Pos          (4)                                               /*!< CLK_T::CLKSEL1: CLKOSEL Position       */
#define CLK_CLKSEL1_CLKOSEL_Msk          (0x7ul << CLK_CLKSEL1_CLKOSEL_Pos)                /*!< CLK_T::CLKSEL1: CLKOSEL Mask           */

#define CLK_CLKSEL1_TMR0SEL_Pos          (8)                                               /*!< CLK_T::CLKSEL1: TMR0SEL Position       */
#define CLK_CLKSEL1_TMR0SEL_Msk          (0x7ul << CLK_CLKSEL1_TMR0SEL_Pos)                /*!< CLK_T::CLKSEL1: TMR0SEL Mask           */

#define CLK_CLKSEL1_TMR1SEL_Pos          (12)                                              /*!< CLK_T::CLKSEL1: TMR1SEL Position       */
#define CLK_CLKSEL1_TMR1SEL_Msk          (0x7ul << CLK_CLKSEL1_TMR1SEL_Pos)                /*!< CLK_T::CLKSEL1: TMR1SEL Mask           */

#define CLK_CLKSEL1_UART0SEL_Pos         (24)                                              /*!< CLK_T::CLKSEL1: UART0SEL Position      */
#define CLK_CLKSEL1_UART0SEL_Msk         (0x7ul << CLK_CLKSEL1_UART0SEL_Pos)               /*!< CLK_T::CLKSEL1: UART0SEL Mask          */

#define CLK_CLKSEL2_SPI0SEL_Pos          (4)                                               /*!< CLK_T::CLKSEL2: SPI0SEL Position       */
#define CLK_CLKSEL2_SPI0SEL_Msk          (0x3ul << CLK_CLKSEL2_SPI0SEL_Pos)                /*!< CLK_T::CLKSEL2: SPI0SEL Mask           */

#define CLK_CLKSEL2_ADCSEL_Pos           (20)                                              /*!< CLK_T::CLKSEL2: ADCSEL Position        */
#define CLK_CLKSEL2_ADCSEL_Msk           (0x3ul << CLK_CLKSEL2_ADCSEL_Pos)                 /*!< CLK_T::CLKSEL2: ADCSEL Mask            */

#define CLK_CLKDIV0_HCLKDIV_Pos          (0)                                               /*!< CLK_T::CLKDIV0: HCLKDIV Position       */
#define CLK_CLKDIV0_HCLKDIV_Msk          (0xful << CLK_CLKDIV0_HCLKDIV_Pos)                /*!< CLK_T::CLKDIV0: HCLKDIV Mask           */

#define CLK_CLKDIV0_UART0DIV_Pos         (8)                                               /*!< CLK_T::CLKDIV0: UART0DIV Position      */
#define CLK_CLKDIV0_UART0DIV_Msk         (0xful << CLK_CLKDIV0_UART0DIV_Pos)               /*!< CLK_T::CLKDIV0: UART0DIV Mask          */

#define CLK_CLKDIV0_ADCDIV_Pos           (16)                                              /*!< CLK_T::CLKDIV0: ADCDIV Position        */
#define CLK_CLKDIV0_ADCDIV_Msk           (0xfful << CLK_CLKDIV0_ADCDIV_Pos)                /*!< CLK_T::CLKDIV0: ADCDIV Mask            */

#define CLK_PCLKDIV_APB0DIV_Pos          (0)                                               /*!< CLK_T::PCLKDIV: APB0DIV Position       */
#define CLK_PCLKDIV_APB0DIV_Msk          (0x7ul << CLK_PCLKDIV_APB0DIV_Pos)                /*!< CLK_T::PCLKDIV: APB0DIV Mask           */

#define CLK_PCLKDIV_APB1DIV_Pos          (4)                                               /*!< CLK_T::PCLKDIV: APB1DIV Position       */
#define CLK_PCLKDIV_APB1DIV_Msk          (0x7ul << CLK_PCLKDIV_APB1DIV_Pos)                /*!< CLK_T::PCLKDIV: APB1DIV Mask           */

#define CLK_STATUS_LIRCSTB_Pos           (3)                                               /*!< CLK_T::STATUS: LIRCSTB Position        */
#define CLK_STATUS_LIRCSTB_Msk           (0x1ul << CLK_STATUS_LIRCSTB_Pos)                 /*!< CLK_T::STATUS: LIRCSTB Mask            */

#define CLK_STATUS_HIRCSTB_Pos           (4)                                               /*!< CLK_T::STATUS: HIRCSTB Position        */
#define CLK_STATUS_HIRCSTB_Msk           (0x1ul << CLK_STATUS_HIRCSTB_Pos)                 /*!< CLK_T::STATUS: HIRCSTB Mask            */

#define CLK_STATUS_CLKSFAIL_Pos          (7)                                               /*!< CLK_T::STATUS: CLKSFAIL Position       */
#define CLK_STATUS_CLKSFAIL_Msk          (0x1ul << CLK_STATUS_CLKSFAIL_Pos)                /*!< CLK_T::STATUS: CLKSFAIL Mask           */

#define CLK_CLKOCTL_FREQSEL_Pos          (0)                                               /*!< CLK_T::CLKOCTL: FREQSEL Position       */
#define CLK_CLKOCTL_FREQSEL_Msk          (0xful << CLK_CLKOCTL_FREQSEL_Pos)                /*!< CLK_T::CLKOCTL: FREQSEL Mask           */

#define CLK_CLKOCTL_CLKOEN_Pos           (4)                                               /*!< CLK_T::CLKOCTL: CLKOEN Position        */
#define CLK_CLKOCTL_CLKOEN_Msk           (0x1ul << CLK_CLKOCTL_CLKOEN_Pos)                 /*!< CLK_T::CLKOCTL: CLKOEN Mask            */

#define CLK_CLKOCTL_DIV1EN_Pos           (5)                                               /*!< CLK_T::CLKOCTL: DIV1EN Position        */
#define CLK_CLKOCTL_DIV1EN_Msk           (0x1ul << CLK_CLKOCTL_DIV1EN_Pos)                 /*!< CLK_T::CLKOCTL: DIV1EN Mask            */

/**@}*/ /* CLK_CONST */
/**@}*/ /* end of CLK register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __CLK_REG_H__ */
