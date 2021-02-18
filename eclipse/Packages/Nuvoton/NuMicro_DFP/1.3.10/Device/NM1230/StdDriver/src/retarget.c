/**************************************************************************//**
 * @file     retarget.c
 * @version  V3.00
 * $Revision: 2 $
 * $Date: 17/05/04 9:34a $
 * @brief    NM1230 Series Debug Port and Semihost Setting Source File
 *
 * @note
 * Copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/


#include <stdio.h>
#include "NM1230Series.h"

#if defined ( __CC_ARM   )
#if (__ARMCC_VERSION < 400000)
#else
/* Insist on keeping widthprec, to avoid X propagation by benign code in C-lib */
#pragma import _printf_widthprec
#endif
#endif

/*---------------------------------------------------------------------------------------------------------*/
/* Global variables                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
#if !(defined(__ICCARM__) && (__VER__ >= 6010000))
struct __FILE {
    int handle; /* Add whatever you need here */
};
#endif
FILE __stdout;
FILE __stdin;

enum { r0, r1, r2, r3, r12, lr, pc, psr};

void stackDump(uint32_t stack[])
{
	printf("r0  = 0x%x\n", stack[r0]);
	printf("r1  = 0x%x\n", stack[r1]);
	printf("r2  = 0x%x\n", stack[r2]);
	printf("r3  = 0x%x\n", stack[r3]);
	printf("r12 = 0x%x\n", stack[r12]);
	printf("lr  = 0x%x\n", stack[lr]);
	printf("pc  = 0x%x\n", stack[pc]);
	printf("psr = 0x%x\n", stack[psr]);
} 

void Hard_Fault_Handler(uint32_t stack[])
{     
    printf("In Hard Fault Handler\n");

    stackDump(stack);
	
	//Chip Reset
	//SYS_UnlockReg();
	//SYS->IPRSTC1 |= SYS_IPRSTC1_CHIP_RST_Msk;

    while(1);
}

/*---------------------------------------------------------------------------------------------------------*/
/* Routine to write a char                                                                                 */
/*---------------------------------------------------------------------------------------------------------*/

#if defined(DEBUG_ENABLE_SEMIHOST)
/* The static buffer is used to speed up the semihost */
static char g_buf[16];
static char g_buf_len = 0;

# if defined(__ICCARM__)


/**
 * @brief    This HardFault handler is implemented to support semihost
 *
 * @param    None
 *
 * @returns  None
 *
 * @details  This function is implement to support semihost message print.
 *
 */
void HardFault_Handler(void)
{
    asm("MOV     R0, lr        \n"
        "LSLS    R0, #29       \n"        //; Check bit 2
        "BMI     SP_is_PSP     \n"        //; previous stack is PSP
        "MRS     R0, MSP       \n"        //; previous stack is MSP, read MSP
        "B       SP_Read_Ready \n"
        "SP_is_PSP:            \n"
        "MRS     R0, PSP       \n"        //; Read PSP
        "SP_Read_Ready:        \n"
        "LDR     R1, [R0, #24] \n"        //; Get previous PC
        "LDRH    R3, [R1]      \n"        //; Get instruction
        "LDR     R2, [pc, #8]  \n"        //; The specific BKPT instruction
        "CMP     R3, R2        \n"        //; Test if the instruction at previous PC is BKPT
        "BNE     HardFault_Handler_Ret\n" //; Not BKPT
        "ADDS    R1, #4        \n"        //; Skip BKPT and next line
        "STR     R1, [R0, #24] \n"        //; Save previous PC
        "BX      lr            \n"        //; Return
        "DCD     0xBEAB        \n"        //; BKPT instruction code
        "HardFault_Handler_Ret:\n"
        "MOVS    r0, #4                        \n"
        "MOV     r1, LR                        \n"
        "TST     r0, r1                        \n"
        "BEQ     Stack_Use_MSP                 \n" 
        "MRS     R0, PSP                       \n" //; stack use PSP 
        "B       Get_LR_and_Branch             \n" 
        "Stack_Use_MSP:                        \n" 
        "MRS     R0, MSP                       \n" //; stack use MSP 
        "Get_LR_and_Branch:                    \n" 
        "MOV     R1, LR                        \n" //; LR current value 
        "B Hard_Fault_Handler        \n"         
       );

    /* TODO: Implement your own hard fault handler here. */
    while(1);
}

/**
 *
 * @brief      The function to process semihosted command
 * @param[in]  n32In_R0  : semihost register 0
 * @param[in]  n32In_R1  : semihost register 1
 * @param[out] pn32Out_R0: semihost register 0
 * @retval     0: No ICE debug
 * @retval     1: ICE debug
 *
 */
int32_t SH_DoCommand(int32_t n32In_R0, int32_t n32In_R1, int32_t *pn32Out_R0)
{
    asm("BKPT   0xAB    \n"       //; This instruction will cause ICE trap or system HardFault
        "B      SH_ICE  \n"
        "SH_HardFault:  \n"       //; Captured by HardFault
        "MOVS   R0, #0  \n"       //; Set return value to 0
        "BX     lr      \n"       //; Return
        "SH_ICE:        \n"       //; Captured by ICE
        "CMP    R2, #0  \n"
        "BEQ    SH_End  \n"
        "STR    R0, [R2]\n"       //; Save the return value to *pn32Out_R0
        "SH_End:        \n");

    return 1;                 //; Return 1 when it is trap by ICE

}


# else

/**
 * @brief    This HardFault handler is implemented to support semihost
 *
 * @param    None
 *
 * @returns  None
 *
 * @details  This function is implement to support semihost message print.
 *
 */
__asm int32_t HardFault_Handler(void)
{

    MOV     R0, LR
    LSLS    R0, #29               //; Check bit 2
    BMI     SP_is_PSP             //; previous stack is PSP
    MRS     R0, MSP               //; previous stack is MSP, read MSP
    B       SP_Read_Ready
SP_is_PSP
    MRS     R0, PSP               //; Read PSP

SP_Read_Ready
    LDR     R1, [R0, #24]         //; Get previous PC
    LDRH    R3, [R1]              //; Get instruction
    LDR     R2, =0xBEAB           //; The specific BKPT instruction
    CMP     R3, R2                //; Test if the instruction at previous PC is BKPT
    BNE     HardFault_Handler_Ret //; Not BKPT
    
    ADDS    R1, #4                //; Skip BKPT and next line
    STR     R1, [R0, #24]         //; Save previous PC
    
    BX      LR                    //; Return
HardFault_Handler_Ret
    
    /* TODO: Implement your own hard fault handler here. */
    MOVS    r0, #4 
    MOV     r1, LR 
    TST     r0, r1 
    BEQ     Stack_Use_MSP 
    MRS     R0, PSP ;stack use PSP 
    B       Get_LR_and_Branch 
Stack_Use_MSP 
    MRS     R0, MSP ; stack use MSP 
Get_LR_and_Branch 
    MOV     R1, LR ; LR current value 
    LDR     R2,=__cpp(Hard_Fault_Handler) 
    BX      R2  
        
    B       .
    
    ALIGN
}

/**
 *
 * @brief      The function to process semihosted command
 * @param[in]  n32In_R0  : semihost register 0
 * @param[in]  n32In_R1  : semihost register 1
 * @param[out] pn32Out_R0: semihost register 0
 * @retval     0: No ICE debug
 * @retval     1: ICE debug
 *
 */
__asm int32_t SH_DoCommand(int32_t n32In_R0, int32_t n32In_R1, int32_t *pn32Out_R0)
{
    BKPT   0xAB          //; Wait ICE or HardFault
    //; ICE will step over BKPT directly
    //; HardFault will step BKPT and the next line
    B      SH_ICE

SH_HardFault             //; Captured by HardFault
    MOVS   R0, #0        //; Set return value to 0
    BX     lr            //; Return

SH_ICE                   //; Captured by ICE
    //; Save return value
    CMP    R2, #0
    BEQ    SH_End
    STR    R0, [R2]      //; Save the return value to *pn32Out_R0

SH_End
    MOVS   R0, #1        //; Set return value to 1
    BX     lr            //; Return
}
#endif


#else

# if defined(__ICCARM__)

/**
 * @brief    This HardFault handler is implemented to show r0, r1, r2, r3, r12, lr, pc, psr 
 *
 * @param    None
 *
 * @returns  None
 *
 * @details  This function is implement to print r0, r1, r2, r3, r12, lr, pc, psr.
 *
 */
void HardFault_Handler(void)
{
    asm("MOVS    r0, #4                        \n"
        "MOV     r1, LR                        \n"
        "TST     r0, r1                        \n"
        "BEQ     Stack_Use_MSP                 \n" 
        "MRS     R0, PSP                       \n" //; stack use PSP 
        "B       Get_LR_and_Branch             \n" 
        "Stack_Use_MSP:                        \n" 
        "MRS     R0, MSP                       \n" //; stack use MSP 
        "Get_LR_and_Branch:                    \n" 
        "MOV     R1, LR                        \n" //; LR current value 
        "B Hard_Fault_Handler                  \n" 
       );
     
    while(1);
}

# else

/**
 * @brief    This HardFault handler is implemented to show r0, r1, r2, r3, r12, lr, pc, psr
 *
 * @param    None
 *
 * @returns  None
 *
 * @details  This function is implement to print r0, r1, r2, r3, r12, lr, pc, psr
 *
 */
__asm int32_t HardFault_Handler(void)
{
    MOVS    r0, #4 
    MOV     r1, LR 
    TST     r0, r1 
    BEQ     Stack_Use_MSP 
    MRS     R0, PSP ;stack use PSP 
    B       Get_LR_and_Branch 
Stack_Use_MSP 
    MRS     R0, MSP ; stack use MSP 
Get_LR_and_Branch 
    MOV     R1, LR ; LR current value 
    LDR     R2,=__cpp(Hard_Fault_Handler) 
    BX      R2                  
}

#endif

#endif


/**
 * @brief       Routine to send a char
 *
 * @param[in]   ch  Character to be written to debug port
 *
 * @returns     Send value from UART debug port
 *
 * @details     Send a target char to UART debug port .
 */
#ifndef NONBLOCK_PRINTF
void SendChar_ToUART(int ch)
{
    while(DEBUG_PORT->BUFSTS & UUART_BUFSTS_TXFULL_Msk);
    
    DEBUG_PORT->TXDAT = ch;
    if(ch == '\n')
    {
        while(DEBUG_PORT->BUFSTS & UUART_BUFSTS_TXFULL_Msk);
        DEBUG_PORT->TXDAT = '\r';
    }		
}
#else
/* Non-block implement of send char */
#define BUF_SIZE    2048
void SendChar_ToUART(int ch)
{
    static uint8_t u8Buf[BUF_SIZE] = {0};
    static int32_t i32Head = 0;
    static int32_t i32Tail = 0;
    int32_t i32Tmp;
    
    /* Only flush the data in buffer to UART when ch == 0 */
    if(ch)
    {
        // Push char
        i32Tmp = i32Head+1;
        if(i32Tmp > BUF_SIZE) i32Tmp = 0;
        if(i32Tmp != i32Tail)
        {
            u8Buf[i32Head] = ch;
            i32Head = i32Tmp;
        }
        
        if(ch == '\n')
        {
            i32Tmp = i32Head+1;
            if(i32Tmp > BUF_SIZE) i32Tmp = 0;
            if(i32Tmp != i32Tail)
            {
                u8Buf[i32Head] = '\r';
                i32Head = i32Tmp;
            }
        }
    }
    else
    {
        if(i32Tail == i32Head)
            return;
    }
    
    // pop char
    do
    {
        i32Tmp = i32Tail + 1;
        if(i32Tmp > BUF_SIZE) i32Tmp = 0;
        
        if((DEBUG_PORT->BUFSTS & UUART_BUFSTS_TXFULL_Msk) == 0)
        {
            DEBUG_PORT->TXDAT = u8Buf[i32Tail];
            i32Tail = i32Tmp;
        }
        else
            break; // FIFO full
    }while(i32Tail != i32Head);
}
#endif
/**
 * @brief       Routine to send a char
 *
 * @param[in]   ch  Character to be written to debug port
 *
 * @returns     Send value from UART debug port or semihost
 *
 * @details     Send a target char to UART debug port or semihost.
 */
void SendChar(int ch)
{
#if defined(DEBUG_ENABLE_SEMIHOST)
    g_buf[g_buf_len++] = ch;
    g_buf[g_buf_len] = '\0';
    if(g_buf_len + 1 >= sizeof(g_buf) || ch == '\n' || ch == '\0') {
        /* Send the char */
        if(SH_DoCommand(0x04, (int)g_buf, NULL) != 0) {
            g_buf_len = 0;
            return;
        } else {
            int i;

            for(i=0; i<g_buf_len; i++)
                SendChar_ToUART(g_buf[i]);
            g_buf_len = 0;
        }
    }
#else
    SendChar_ToUART(ch);
#endif
}

/**
 * @brief    Routine to get a char
 *
 * @param    None
 *
 * @returns  Get value from UART debug port or semihost
 *
 * @details  Wait UART debug port or semihost to input a char.
 */
char GetChar(void)
{
#ifdef DEBUG_ENABLE_SEMIHOST
# if defined ( __CC_ARM   )
    int nRet;
    while(SH_DoCommand(0x101, 0, &nRet) != 0) {
        if(nRet != 0) {
            SH_DoCommand(0x07, 0, &nRet);
            return (char)nRet;
        }
    }
# else
    int nRet;
    while(SH_DoCommand(0x7, 0, &nRet) != 0) {
        if(nRet != 0)
            return (char)nRet;
    }
# endif
    return (0);
#else

    while (1) {
        if((DEBUG_PORT->BUFSTS & UUART_BUFSTS_RXEMPTY_Msk) == 0)  {
            return (DEBUG_PORT->RXDAT);
        }
    }

#endif
}

/**
 * @brief    Check any char input from UART
 *
 * @param    None
 *
 * @retval   1: No any char input
 * @retval   0: Have some char input
 *
 * @details  Check UART RSR RX EMPTY or not to determine if any char input from UART
 */

int kbhit(void)
{
    return !((DEBUG_PORT->BUFSTS & UUART_BUFSTS_RXEMPTY_Msk) == 0);
	
}
/**
 * @brief    Check if debug message finished
 *
 * @param    None
 *
 * @retval   1: Message is finished
 * @retval   0: Message is transmitting.
 *
 * @details  Check if message finished (FIFO empty of debug port)
 */

int IsDebugFifoEmpty(void)
{
    return ((DEBUG_PORT->BUFSTS & UUART_BUFSTS_TXEMPTY_Msk) != 0);

}

/**
 * @brief       C library retargetting
 *
 * @param[in]   ch  Character to be written to debug port
 *
 * @returns  None
 *
 * @details  Check if message finished (FIFO empty of debug port)
 */

void _ttywrch(int ch)
{
    SendChar(ch);
    return;
}


/**
 * @brief      Write character to stream
 *
 * @param[in]  ch       Character to be written. The character is passed as its int promotion.
 * @param[in]  stream   Pointer to a FILE object that identifies the stream where the character is to be written.
 *
 * @returns    If there are no errors, the same character that has been written is returned.
 *             If an error occurs, EOF is returned and the error indicator is set (see ferror).
 *
 * @details    Writes a character to the stream and advances the position indicator.\n
 *             The character is written at the current position of the stream as indicated \n
 *             by the internal position indicator, which is then advanced one character.
 *
 * @note       The above descriptions are copied from http://www.cplusplus.com/reference/clibrary/cstdio/fputc/.
 *
 *
 */

int fputc(int ch, FILE *stream)
{
    SendChar(ch);
    return ch;
}


/**
 * @brief      Get character from UART debug port or semihosting input
 *
 * @param[in]  stream   Pointer to a FILE object that identifies the stream on which the operation is to be performed.
 *
 * @returns    The character read from UART debug port or semihosting
 *
 * @details    For get message from debug port or semihosting.
 *
 */

int fgetc(FILE *stream)
{
    return (GetChar());
}

/**
 * @brief      Check error indicator
 *
 * @param[in]  stream   Pointer to a FILE object that identifies the stream.
 *
 * @returns    If the error indicator associated with the stream was set, the function returns a nonzero value.
 *             Otherwise, it returns a zero value.
 *
 * @details    Checks if the error indicator associated with stream is set, returning a value different
 *             from zero if it is. This indicator is generally set by a previous operation on the stream that failed.
 *
 * @note       The above descriptions are copied from http://www.cplusplus.com/reference/clibrary/cstdio/ferror/.
 *
 */
#if 1
int ferror(FILE *stream)
{
    return EOF;
}
#endif
#ifdef DEBUG_ENABLE_SEMIHOST
# ifdef __ICCARM__
void __exit(int return_code)
{

    /* Check if link with ICE */
    if(SH_DoCommand(0x18, 0x20026, NULL) == 0) {
        /* Make sure all message is print out */
        while(IsDebugFifoEmpty() == 0);
    }
label:
    goto label;  /* endless loop */
}
# else
void _sys_exit(int return_code)
{

    /* Check if link with ICE */
    if(SH_DoCommand(0x18, 0x20026, NULL) == 0) {
        /* Make sure all message is print out */
        while(IsDebugFifoEmpty() == 0);
    }
label:
    goto label;  /* endless loop */
}
# endif
#endif





