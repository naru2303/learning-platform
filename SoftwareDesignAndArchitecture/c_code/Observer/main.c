#include <stdio.h>
#include "Subject/battery_monitor.h"
#include "Observers/bms_observers.h"

int main(void) {
    BatteryMonitor bms;
    BatteryMonitor_Init(&bms);

    // 1. Subscription Phase (Wiring the system)
    BatteryMonitor_AddObserver(&bms, Display_Update);
    BatteryMonitor_AddObserver(&bms, Safety_Check);
    // Note: We can easily comment out Logger without breaking 'bms' code
    BatteryMonitor_AddObserver(&bms, Logger_Write); 

    printf("--- System Start ---\n");

    // 2. Event Phase
    // Voltage drops slowly
    BatteryMonitor_SetVoltage(&bms, 12.5f);
    BatteryMonitor_SetVoltage(&bms, 11.0f);
    
    // Critical event
    BatteryMonitor_SetVoltage(&bms, 9.5f);

    return 0;
}
