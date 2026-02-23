#include "battery_monitor.h"
#include <stdio.h>

void BatteryMonitor_Init(BatteryMonitor* me) {
    me->voltage = 0.0f;
    me->observerCount = 0;
    // Clear array for safety
    for(int i=0; i<MAX_OBSERVERS; i++) {
        me->observers[i] = NULL; 
    }
}

bool BatteryMonitor_AddObserver(BatteryMonitor* me, BatteryObserverCB observer) {
    if (me->observerCount >= MAX_OBSERVERS) {
        printf("[Error] Max observers reached!\n");
        return false;
    }
    
    me->observers[me->observerCount++] = observer;
    return true;
}

static void NotifyAll(BatteryMonitor* me, bool isCritical) {
    for (int i = 0; i < me->observerCount; i++) {
        if (me->observers[i] != NULL) {
            // Call the function pointer
            me->observers[i](me->voltage, isCritical);
        }
    }
}

void BatteryMonitor_SetVoltage(BatteryMonitor* me, float newVoltage) {
    // Only notify on significant change, or always. Here we do always for demo.
    me->voltage = newVoltage;
    bool isCritical = (newVoltage < 10.0f);
    
    printf("[Subject] Voltage changed to %.1fV. Notifying %d observers...\n", 
           me->voltage, me->observerCount);
           
    NotifyAll(me, isCritical);
}
