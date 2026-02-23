#ifndef I_TIMER_H
#define I_TIMER_H

#include <stdint.h> // CORRECTION: Use stdint.h for C, cstdint is for C++

// The Interface Definition
// Application code uses this, not the specific implementation.

typedef struct ITimer ITimer;

struct ITimer {
    // Methods (VTable)
    void (*start)(void* instance, uint32_t timeout_ms); // CORRECTION: uint32_t
    int (*isRunning)(void* instance); // CORRECTION: Changed return type to int (boolean)
};

// Helper macros for cleaner syntax
#define ITimer_Start(interface, instance, timeout_ms)  ((interface)->start(instance, timeout_ms))
#define ITimer_IsRunning(interface, instance) ((interface)->isRunning(instance))

#endif // I_TIMER_H