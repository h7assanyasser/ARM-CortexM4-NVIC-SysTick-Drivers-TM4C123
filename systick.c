#include "systick.h"
#include <tm4c123gh6pm.h>
#include "common_macros.h"

#define NULL_PTR ((void*)0)

static volatile void (*g_sysTick_callBackPtr)(void) = NULL_PTR ;

/****************************************************************************
 * Service Name: SysTick_Init
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): time_ms
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to init the sysTick to interrupt each time_ms counted
*****************************************************************************/

void SysTick_Init(uint16_t time_ms)
{
    uint32_t reload_value = (time_ms * (FCPU/1000)) - 1;                                // Calculate based on the defined frequency for the CPU
    NVIC_ST_CTRL_R = 0;                                                                 // Step 1: Disable SysTick
    if (reload_value > 0x00FFFFFF)                                                      // Step 2: Set reload value (24-bit max)
        reload_value = 0x00FFFFFF;
    NVIC_ST_RELOAD_R = reload_value;                                                    // Step 3: Clear current value
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE | NVIC_ST_CTRL_INTEN | NVIC_ST_CTRL_CLK_SRC;   // Step 4 + 5: Enable interrupt, use system clock, and start timer
}

/****************************************************************************
 * Service Name: SysTick_StartBusyWait
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): time_ms
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to init the sysTick to wait till count the time_ms
*****************************************************************************/

void SysTick_StartBusyWait(uint16_t time_ms)
{
    uint32_t reload_value = (time_ms * (FCPU/1000)) - 1 ;
    NVIC_ST_CTRL_R = 0 ;
    if (reload_value > 0x00FFFFFF)
        reload_value = 0x00FFFFFF;
    NVIC_ST_RELOAD_R = reload_value;
    NVIC_ST_CURRENT_R = 0 ;
    NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE | NVIC_ST_CTRL_CLK_SRC ;                       //Not enable interrupt here
    while ((NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT) == 0);                                 //Wait till flag is set
}

/****************************************************************************
 * Service Name: SysTick_SetCallBack
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Ptr2Func - Function that will be called by the sysTick
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set the function called by the ISR of sysTick
*****************************************************************************/

void SysTick_SetCallBack(volatile void (*Ptr2Func) (void))
{
    g_sysTick_callBackPtr = Ptr2Func ;
}

/****************************************************************************
 * Service Name: SysTick_Handler
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: The handler function of the sysTick interrupt
*****************************************************************************/

void SysTick_Handler(void)
{
    if(g_sysTick_callBackPtr != NULL_PTR)
        (*g_sysTick_callBackPtr)() ;
}

/****************************************************************************
 * Service Name: SysTick_Stop
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to stop the sysTick counter
*****************************************************************************/

void SysTick_Stop(void)
{
    CLEAR_BIT(NVIC_ST_CTRL_R, NVIC_ST_CTRL_ENABLE) ;
}

/****************************************************************************
 * Service Name: SysTick_Start
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to continue the sysTick counter
*****************************************************************************/

void SysTick_Start(void)
{
    SET_BIT(NVIC_ST_CTRL_R, NVIC_ST_CTRL_ENABLE) ;
}

/****************************************************************************
 * Service Name: SysTick_DeInit
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to deinit the systick settings
*****************************************************************************/

void SysTick_DeInit(void)
{
    NVIC_ST_CTRL_R = 0 ;
}











