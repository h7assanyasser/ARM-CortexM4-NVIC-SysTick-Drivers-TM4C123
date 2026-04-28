/******************************************************************************
 *
 * Module: NVIC
 *
 * File Name: NVIC.h
 *
 * Description: Header file for the ARM Cortex M4 NVIC driver
 *
 * Author: Mohamed Tarek (Edges For Training)
 *
 *******************************************************************************/

#ifndef NVIC_H_
#define NVIC_H_

/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/
#include <stdint.h>

/*******************************************************************************
 *                           Preprocessor Definitions                          *
 *******************************************************************************/

#define MEM_FAULT_PRIORITY_MASK              0x000000E0
#define MEM_FAULT_PRIORITY_BITS_POS          5

#define BUS_FAULT_PRIORITY_MASK              0x0000E000
#define BUS_FAULT_PRIORITY_BITS_POS          13

#define USAGE_FAULT_PRIORITY_MASK            0x00E00000
#define USAGE_FAULT_PRIORITY_BITS_POS        21

#define SVC_PRIORITY_MASK                    0xE0000000
#define SVC_PRIORITY_BITS_POS                29

#define DEBUG_MONITOR_PRIORITY_MASK          0x000000E0
#define DEBUG_MONITOR_PRIORITY_BITS_POS      5

#define PENDSV_PRIORITY_MASK                 0x00E00000
#define PENDSV_PRIORITY_BITS_POS             21

#define SYSTICK_PRIORITY_MASK                0xE0000000
#define SYSTICK_PRIORITY_BITS_POS            29

#define MEM_FAULT_ENABLE_MASK                0x00010000
#define BUS_FAULT_ENABLE_MASK                0x00020000
#define USAGE_FAULT_ENABLE_MASK              0x00040000

/* Enable Exceptions ... This Macro enable IRQ interrupts, Programmable Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Enable_Exceptions()    __asm(" CPSIE I ")

/* Disable Exceptions ... This Macro disable IRQ interrupts, Programmable Systems Exceptions and Faults by setting the I-bit in the PRIMASK. */
#define Disable_Exceptions()   __asm(" CPSID I ")

/* Enable Faults ... This Macro enable Faults by clearing the F-bit in the FAULTMASK */
#define Enable_Faults()        __asm(" CPSIE F ")

/* Disable Faults ... This Macro disable Faults by setting the F-bit in the FAULTMASK */
#define Disable_Faults()       __asm(" CPSID F ")

/*******************************************************************************
 *                           Data Types Declarations                           *
 *******************************************************************************/
typedef enum {
    GPIOA_IRQ = 0,
    GPIOB_IRQ = 1,
    GPIOC_IRQ = 2,
    GPIOD_IRQ = 3,
    GPIOE_IRQ = 4,
    UART0_IRQ = 5,
    UART1_IRQ = 6,
    SSI0_IRQ = 7,
    I2C0_IRQ = 8,
    PWM0_FAULT_IRQ = 9,
    PWM0_GEN0_IRQ = 10,
    PWM0_GEN1_IRQ = 11,
    PWM0_GEN2_IRQ = 12,
    QEI0_IRQ = 13,
    ADC0_SEQ0_IRQ = 14,
    ADC0_SEQ1_IRQ = 15,
    ADC0_SEQ2_IRQ = 16,
    ADC0_SEQ3_IRQ = 17,
    WATCHDOG0_1_IRQ = 18,
    TIMER0A_IRQ = 19,
    TIMER0B_IRQ = 20,
    TIMER1A_IRQ = 21,
    TIMER1B_IRQ = 22,
    TIMER2A_IRQ = 23,
    TIMER2B_IRQ = 24,
    COMP0_IRQ = 25,
    COMP1_IRQ = 26,
    SYSCTL_IRQ = 28,
    FLASH_IRQ = 29,
    GPIOF_IRQ = 30,
    UART2_IRQ = 33,
    SSI1_IRQ = 34,
    TIMER3A_IRQ = 35,
    TIMER3B_IRQ = 36,
    I2C1_IRQ = 37,
    QEI1_IRQ = 38,
    CAN0_IRQ = 39,
    CAN1_IRQ = 40,
    HIB_IRQ = 43,
    USB_IRQ = 44,
    PWM0_GEN3_IRQ = 45,
    UDMA_IRQ = 46,
    UDMA_ERR_IRQ = 47,
    ADC1_SEQ0_IRQ = 48,
    ADC1_SEQ1_IRQ = 49,
    ADC1_SEQ2_IRQ = 50,
    ADC1_SEQ3_IRQ = 51,
    UART3_IRQ = 59,
    UART4_IRQ = 60,
    UART5_IRQ = 61,
    UART6_IRQ = 62,
    UART7_IRQ = 63,
    ADC1_SS0_IRQ = 64,
    ADC1_SS1_IRQ = 65,
    ADC1_SS2_IRQ = 66,
} NVIC_IRQType;

typedef uint16_t NVIC_IRQPriorityType;

typedef enum
{
    EXCEPTION_RESET_TYPE,
    EXCEPTION_NMI_TYPE,
    EXCEPTION_HARD_FAULT_TYPE,
    EXCEPTION_MEM_FAULT_TYPE,
    EXCEPTION_BUS_FAULT_TYPE,
    EXCEPTION_USAGE_FAULT_TYPE,
    EXCEPTION_SVC_TYPE,
    EXCEPTION_DEBUG_MONITOR_TYPE,
    EXCEPTION_PEND_SV_TYPE,
    EXCEPTION_SYSTICK_TYPE
}NVIC_ExceptionType;

typedef uint8_t NVIC_ExceptionPriorityType;

/************************************************************************************
 *                                 End of File                                      *
 ************************************************************************************/

void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num) ;

void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num) ;

void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, uint16_t IRQ_Priority) ;

void NVIC_EnableException(NVIC_ExceptionType Exception_Num) ;

void NVIC_DisableException(NVIC_ExceptionType Exception_Num) ;

void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority) ;

#endif /* NVIC_H_ */
