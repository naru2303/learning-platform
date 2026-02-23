#ifndef TIMER_ADAPTER_H
#define TIMER_ADAPTER_H

#include "itimer.h"
#include "../../HardwareProxy/Practice/timer_driver.h" // CORRECTION: Adjusted path to match structure

// The Adapter Structure
typedef struct {
    TimerProxy* driver; // Helper reference (The Adaptee)
} TimerAdapter;

// Implementation of the Interface functions
void TimerAdapter_start(void* instance, uint32_t timeout_ms); // CORRECTION: uint32_t
int TimerAdapter_isRunning(void* instance); // CORRECTION: Return int

// The constant Interface VTable for this Adapter
extern const ITimer TimerAdapter_Interface;

// Initialization
void TimerAdapter_Init(TimerAdapter* me, TimerProxy* driver);

#endif // TIMER_ADAPTER_H