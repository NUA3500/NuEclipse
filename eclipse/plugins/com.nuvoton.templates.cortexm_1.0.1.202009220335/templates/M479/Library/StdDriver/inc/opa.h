/**************************************************************************//**
 * @file     opa.h
 * @version  V3.00
 * @brief    M479 series OPA driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __OPA_H__
#define __OPA_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup OPA_Driver OPA Driver
  @{
*/

/** @addtogroup OPA_EXPORTED_CONSTANTS OPA Exported Constants
  @{
*/
/* OPA register offset */
#define OPA_CTL     0x00   /*!< OP Amplifier Control Register */
#define OPA_MODE    0x01   /*!< OPA power mode */
#define OPA0_PGA    0x02   /*!< OPA0 PGA gain control */
#define OPA1_PGA    0x03   /*!< OPA1 PGA gain control */
#define OPA2_PGA    0x04   /*!< OPA2 PGA gain control */
#define OPA3_PGA    0x05   /*!< OPA3 PGA gain control */
#define OPA_CALCTL  0x10   /*!< OP Amplifier Calibration Control Register */
#define OPA_CALST   0x11   /*!< OP Amplifier Calibration Status Register */
#define OPA_CALRES  0x12   /*!< OP Amplifier Calibration Result Register */
#define OPA_TRIMCTL 0x13   /*!< OP Amplifier Trim Control Register */
#define OPA_OP0NNT  0x20   /*!< OP Amplifier Calibration 0 NN Trim */
#define OPA_OP0NPT  0x21   /*!< OP Amplifier Calibration 0 NP Trim */
#define OPA_OP0PNT  0x22   /*!< OP Amplifier Calibration 0 PN Trim */
#define OPA_OP0PPT  0x23   /*!< OP Amplifier Calibration 0 PP Trim */
#define OPA_OP1NNT  0x30   /*!< OP Amplifier Calibration 1 NN Trim */
#define OPA_OP1NPT  0x31   /*!< OP Amplifier Calibration 1 NP Trim */
#define OPA_OP1PNT  0x32   /*!< OP Amplifier Calibration 1 PN Trim */
#define OPA_OP1PPT  0x33   /*!< OP Amplifier Calibration 1 PP Trim */
#define OPA_OP2NNT  0x40   /*!< OP Amplifier Calibration 2 NN Trim */
#define OPA_OP2NPT  0x41   /*!< OP Amplifier Calibration 2 NP Trim */
#define OPA_OP2PNT  0x42   /*!< OP Amplifier Calibration 2 PN Trim */
#define OPA_OP2PPT  0x43   /*!< OP Amplifier Calibration 2 PP Trim */
#define OPA_OP3NNT  0x50   /*!< OP Amplifier Calibration 3 NN Trim */
#define OPA_OP3NPT  0x51   /*!< OP Amplifier Calibration 3 NP Trim */
#define OPA_OP3PNT  0x52   /*!< OP Amplifier Calibration 3 PN Trim */
#define OPA_OP3PPT  0x53   /*!< OP Amplifier Calibration 3 PP Trim */

#define OPA_CALIBRATION_RV_1_2_AVDD                   (0UL)     /*!< OPA calibration reference voltage select 1/2 AVDD  */
#define OPA_CALIBRATION_RV_H_L_VCM                    (1UL)     /*!< OPA calibration reference voltage select from high vcm to low vcm */


#define OPA0        BIT0    /*!< OP Amplifier 0 */
#define OPA1        BIT1    /*!< OP Amplifier 1 */
#define OPA2        BIT2    /*!< OP Amplifier 2 */
#define OPA3        BIT3    /*!< OP Amplifier 3 */

#define OPA_GAIN_NORMAL     (0UL)   /*!< OP Amplifier Gain set to normal */
#define OPA_GAIN_X1         (1UL)   /*!< OP Amplifier Gain x1            */
#define OPA_GAIN_X2         (2UL)   /*!< OP Amplifier Gain x2            */
#define OPA_GAIN_X4         (3UL)   /*!< OP Amplifier Gain x4            */
#define OPA_GAIN_X8         (4UL)   /*!< OP Amplifier Gain x8            */
#define OPA_GAIN_X16        (5UL)   /*!< OP Amplifier Gain x16           */
#define OPA_GAIN_X32        (6UL)   /*!< OP Amplifier Gain x32           */

#define OPA_POWER_NORMAL    (0UL)   /*!< OP Amplifier normal power mode  */
#define OPA_POWER_LOW       (1UL)   /*!< OP Amplifier low power mode     */

/*@}*/ /* end of group OPA_EXPORTED_CONSTANTS */

/** @addtogroup OPA_EXPORTED_FUNCTIONS OPA Exported Functions
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/* Define OPA functions prototype                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
void OPA_POWER_ON(uint32_t u32OpaNum);
void OPA_POWER_DOWN(uint32_t u32OpaNum);
void OPA_Open(uint32_t u32OpaNum, uint32_t u32Mode);
void OPA_Close(uint32_t u32OpaNum);
int32_t OPA_Calibration(uint32_t u32OpaNum, uint32_t u32RefVol);
void OPA_SetAmplifierGain(uint32_t u32OpaNum, uint32_t u32OPA_Gain);


/*@}*/ /* end of group OPA_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group OPA_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __OPA_H__ */

