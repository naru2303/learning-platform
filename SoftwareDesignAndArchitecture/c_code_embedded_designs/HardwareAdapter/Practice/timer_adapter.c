#include "timer_adapter.h"

// 1. Implement the Interface functions by delegating to the Proxy
void TimerAdapter_start(void* instance, uint32_t timeout_ms) {
    // Cast generic void* back to our specific Adapter type
    TimerAdapter* me = (TimerAdapter*)instance;

    // Delegate to the real driver
    Timer_SetReload(me->driver, timeout_ms);
    Timer_Start(me->driver);
}


int TimerAdapter_isRunning(void* instance) { // CORRECTION: Return int, fixed signature
    TimerAdapter* me = (TimerAdapter*)instance;
    return Timer_IsExpired(me->driver);
} // CORRECTION: Added missing closing brace

// 2. Define the VTable
const ITimer TimerAdapter_Interface = {
    .start = TimerAdapter_start,
    .isRunning = TimerAdapter_isRunning
};

// 3. Init
void TimerAdapter_Init(TimerAdapter* me, TimerProxy* driver) {
    me->driver = driver;
}
