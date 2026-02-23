/**
 * @file timer_driver.h
 * @brief Proxy Driver for BitCruncher Timer Peripheral
 * @details This header defines the proxy structure and function prototypes
 * @author Houssem Chekili 
 */

#ifndef TIMER_DRIVER_H
#define TIMER_DRIVER_H

#include <stdint.h>

// TODO 1: Define the Hardware Register Map Structure
// Name it: BitCruncher_RegDef_t
typedef struct {
    // ... Fill in registers (CR, SR, ARR, CNT) using volatile uint32_t

    volatile uint32_t CR;   // Control Register
    volatile uint32_t SR;   // Status Register
    volatile uint32_t ARR;  // Auto-Reload Register
    const volatile uint32_t CNT;  // Counter Register (Read-Only enforcement)
} BitCruncher_RegDef_t;

// Bit Definitions
#define TIMER_CR_ENABLE  (1U << 0)
#define TIMER_CR_IRQ_EN  (1U << 4)
#define TIMER_SR_UIF     (1U << 0)


// TODO 2: Define the Proxy Struct
typedef struct {
    BitCruncher_RegDef_t* hw; 
    // Add any other software config if needed
} TimerProxy;


// TODO 3: Define Function Prototypes
// void Timer_Init(TimerProxy* const me, uintptr_t base_addr);
// void Timer_Start(TimerProxy* const me);
// void Timer_Stop(TimerProxy* const me);
// void Timer_SetReload(TimerProxy* const me, uint32_t val);
// uint32_t Timer_GetCounter(const TimerProxy* const me);
// void Timer_ClearFlag(TimerProxy* const me);
// int Timer_IsExpired(const TimerProxy* const me); // Checks SR Bit 0

void Timer_Init(TimerProxy* const me, uintptr_t base_addr);
void Timer_Start(TimerProxy* const me);
void Timer_Stop(TimerProxy* const me);
void Timer_SetReload(TimerProxy* const me, uint32_t val);
uint32_t Timer_GetCounter(const TimerProxy* const me);
void Timer_ClearFlag(TimerProxy* const me);
int Timer_IsExpired(const TimerProxy* const me); // Checks SR Bit 0


#endif // TIMER_DRIVER_H
