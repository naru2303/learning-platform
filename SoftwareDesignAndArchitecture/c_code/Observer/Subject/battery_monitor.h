#ifndef BATTERY_MONITOR_H
#define BATTERY_MONITOR_H

#include <stddef.h>
#include <stdbool.h>

#define MAX_OBSERVERS 5

// 1. Define the Observer Interface (Function Pointer)
//    Any function that wants to listen must match this signature.
typedef void (*BatteryObserverCB)(float voltage, bool isCritical);

// 2. Define the Subject Struct
typedef struct {
    float voltage;
    // Storage for observers (No malloc, fixed size for deterministic memory)
    BatteryObserverCB observers[MAX_OBSERVERS]; 
    int observerCount;
} BatteryMonitor;

// 3. Public Methods
void BatteryMonitor_Init(BatteryMonitor* me);
bool BatteryMonitor_AddObserver(BatteryMonitor* me, BatteryObserverCB observer);
void BatteryMonitor_SetVoltage(BatteryMonitor* me, float newVoltage);

#endif
