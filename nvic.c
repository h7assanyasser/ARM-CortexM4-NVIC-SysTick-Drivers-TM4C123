#include "nvic.h"
#include <tm4c123gh6pm.h>
#include "common_macros.h"

/****************************************************************************
 * Service Name: NVIC_EnableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to enable Interrupt request for specific IRQ
*****************************************************************************/

void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num)
{
    if (IRQ_Num <= 31)
    {
        NVIC_EN0_R |= (1 << IRQ_Num);
    }
    else if (IRQ_Num <= 63)
    {
        NVIC_EN1_R |= (1 << (IRQ_Num - 32));
    }
    else if (IRQ_Num <= 95)
    {
        NVIC_EN2_R |= (1 << (IRQ_Num - 64));
    }
    else if (IRQ_Num <= 127)
    {
        NVIC_EN3_R |= (1 << (IRQ_Num - 96));
    }
    else if (IRQ_Num <= 195)
    {
        NVIC_EN4_R |= (1 << (IRQ_Num - 128));
    }
}

/****************************************************************************
 * Service Name: NVIC_DisableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to disable Interrupt request for specific IRQ
*****************************************************************************/

void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num)
{
    if (IRQ_Num <= 31)
    {
        NVIC_EN0_R &=~ (1 << IRQ_Num);
    }
    else if (IRQ_Num <= 63)
    {
        NVIC_EN1_R &=~ (1 << (IRQ_Num - 32));
    }
    else if (IRQ_Num <= 95)
    {
        NVIC_EN2_R &=~ (1 << (IRQ_Num - 64));
    }
    else if (IRQ_Num <= 127)
    {
        NVIC_EN3_R &=~ (1 << (IRQ_Num - 96));
    }
    else if (IRQ_Num <= 195)
    {
        NVIC_EN4_R &=~ (1 << (IRQ_Num - 128));
    }
}

/****************************************************************************
 * Service Name: NVIC_SetPriorityIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num, IRQ_Priority - Priority level
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set Interrupt priority for specific IRQ
*****************************************************************************/

void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, uint16_t IRQ_Priority)
{
    if (IRQ_Num <= 154 && IRQ_Priority <= 7)                                        //PRI registers are aligned so we will count offset
    {
        uint8_t registerIndex = IRQ_Num / 4;                                        // Each register handles 4 IRQs so we divide by 4, 3/4 = 0 PRI0
        uint8_t fieldOffset   = (IRQ_Num % 4) * 8 + 5;                              // Position of bits [7:5] in each field, (7%4) * 8 + 5 = 3*8 + 5 = 29
        volatile uint32_t* priReg = &NVIC_PRI0_R + registerIndex;                   //volatile as that's register accessing

        *priReg &= ~(0x7 << fieldOffset);                                           // Clear the old priority bits and insert new priority
        *priReg |=  ((IRQ_Priority & 0x7) << fieldOffset);                          // Set new priority
    }
}

/****************************************************************************
 * Service Name: NVIC_EnableException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Name - the Exception name as defined
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to enable Interrupt request for specific Exception
*****************************************************************************/

void NVIC_EnableException(NVIC_ExceptionType Exception_Name)
{
    switch(Exception_Name)
    {
        case EXCEPTION_USAGE_FAULT_TYPE:
            NVIC_SYS_HND_CTRL_R |= USAGE_FAULT_ENABLE_MASK ;                        // Enable Usage Fault
            break;

        case EXCEPTION_BUS_FAULT_TYPE:
            NVIC_SYS_HND_CTRL_R |= BUS_FAULT_ENABLE_MASK ;                          // Enable Bus Fault
            break;

        case EXCEPTION_MEM_FAULT_TYPE:
            NVIC_SYS_HND_CTRL_R |= MEM_FAULT_ENABLE_MASK ;                          // Enable MemManage Fault
            break;

        case EXCEPTION_SYSTICK_TYPE:
            NVIC_ST_CTRL_R |= 0x2;                                                  // Enable SysTick interrupt
            break;

        case EXCEPTION_SVC_TYPE:                                                    // These are always enabled or not maskable, nothing to set
        case EXCEPTION_PEND_SV_TYPE:
        case EXCEPTION_DEBUG_MONITOR_TYPE:
        case EXCEPTION_HARD_FAULT_TYPE:
        case EXCEPTION_NMI_TYPE:
        case EXCEPTION_RESET_TYPE:
            break;
    }
}

/****************************************************************************
 * Service Name: NVIC_DisableException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Name - the Exception name as defined
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to disable Interrupt request for specific Exception
*****************************************************************************/

void NVIC_DisableException(NVIC_ExceptionType Exception_Num)
{
    switch(Exception_Num)
    {
        case EXCEPTION_USAGE_FAULT_TYPE:
            NVIC_SYS_HND_CTRL_R &=~ USAGE_FAULT_ENABLE_MASK ;                       // Disable Usage Fault
            break;

        case EXCEPTION_BUS_FAULT_TYPE:
            NVIC_SYS_HND_CTRL_R &=~ BUS_FAULT_ENABLE_MASK ;                         // Disable Bus Fault
            break;

        case EXCEPTION_MEM_FAULT_TYPE:
            NVIC_SYS_HND_CTRL_R &=~ MEM_FAULT_ENABLE_MASK ;                         // Disable MemManage Fault
            break;

        case EXCEPTION_SYSTICK_TYPE:
            NVIC_ST_CTRL_R &=~ 0x2;                                                 // Disable SysTick interrupt
            break;

        case EXCEPTION_SVC_TYPE:                                                    // These are always enabled or not maskable, nothing to set
        case EXCEPTION_PEND_SV_TYPE:
        case EXCEPTION_DEBUG_MONITOR_TYPE:
        case EXCEPTION_HARD_FAULT_TYPE:
        case EXCEPTION_NMI_TYPE:
        case EXCEPTION_RESET_TYPE:
            break;
    }
}

/****************************************************************************
 * Service Name: NVIC_SetPriorityException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Name, Exception_Priority - Priority level
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set Interrupt priority for specific Exception
*****************************************************************************/

void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority)
{
    switch (Exception_Num)
    {
        case EXCEPTION_MEM_FAULT_TYPE:
            NVIC_SYS_PRI1_R = (NVIC_SYS_PRI1_R & ~MEM_FAULT_PRIORITY_MASK) | (Exception_Priority << MEM_FAULT_PRIORITY_BITS_POS) ;
            break;

        case EXCEPTION_BUS_FAULT_TYPE:
            NVIC_SYS_PRI1_R = (NVIC_SYS_PRI1_R & ~BUS_FAULT_PRIORITY_MASK) | (Exception_Priority << BUS_FAULT_PRIORITY_BITS_POS);
            break;

        case EXCEPTION_USAGE_FAULT_TYPE:
            NVIC_SYS_PRI1_R = (NVIC_SYS_PRI1_R & ~USAGE_FAULT_PRIORITY_MASK) | (Exception_Priority << USAGE_FAULT_PRIORITY_BITS_POS);
            break;

        case EXCEPTION_SVC_TYPE:
            NVIC_SYS_PRI2_R = (NVIC_SYS_PRI2_R & ~SVC_PRIORITY_MASK) | (Exception_Priority << SVC_PRIORITY_BITS_POS);
            break;

        case EXCEPTION_DEBUG_MONITOR_TYPE:
            NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & ~DEBUG_MONITOR_PRIORITY_MASK) | (Exception_Priority << DEBUG_MONITOR_PRIORITY_BITS_POS);
            break ;

        case EXCEPTION_PEND_SV_TYPE:
            NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & ~PENDSV_PRIORITY_MASK) | (Exception_Priority << PENDSV_PRIORITY_BITS_POS);
            break;

        case EXCEPTION_SYSTICK_TYPE:
            NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & ~SYSTICK_PRIORITY_MASK) | (Exception_Priority << SYSTICK_PRIORITY_BITS_POS);
            break;
    }
}

