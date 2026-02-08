/**
 * @file timer_driver.c
 * @brief Proxy Driver for BitCruncher Timer Peripheral
 * @details This source file implements the proxy structure and function prototypes
 * @author Houssem Chekili 
 */

#include "timer_driver.h"

// TODO: Implement the functions here

void Timer_Init(TimerProxy* const me, uintptr_t base_addr) 
{
    me->hw = (BitCruncher_RegDef_t*)base_addr;
    // Additional initialization if needed

    // This depends on the specific hardware
}

void Timer_Start(TimerProxy* const me) 
{
    // Set the appropriate bit in the Control Register to start the timer
    me->hw->CR |= TIMER_CR_ENABLE; 
}

void Timer_Stop(TimerProxy* const me) 
{
    // Clear the appropriate bit in the Control Register to stop the timer
    me->hw->CR &= ~TIMER_CR_ENABLE; 
}

void Timer_SetReload(TimerProxy* const me, uint32_t val) 
{
    me->hw->ARR = val;
}

uint32_t Timer_GetCounter(const TimerProxy* const me) 
{
    return me->hw->CNT;
}

void Timer_ClearFlag(TimerProxy* const me) 
{
    // Clear the status flag (Write 0 to clear behavior)
    // Note: Be careful with RMW on status registers if other bits have Side Effects. 
    // Here, we assume standard behavior or that only bit 0 cares about 0-writes.
    me->hw->SR &= ~TIMER_SR_UIF;
}

int Timer_IsExpired(const TimerProxy* const me) 
{
    // Check if the status flag (assuming bit 0 is the flag) is set
    return (me->hw->SR & TIMER_SR_UIF) ? 1 : 0;
}