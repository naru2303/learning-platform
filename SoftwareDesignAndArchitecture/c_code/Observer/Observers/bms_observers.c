#include "bms_observers.h"
#include <stdio.h>

void Display_Update(float voltage, bool isCritical) {
    if (isCritical) {
        printf("  [Display] !! LOW BATTERY !! (%.1fV)\n", voltage);
    } else {
        printf("  [Display] Voltage: %.1fV\n", voltage);
    }
}

void Safety_Check(float voltage, bool isCritical) {
    if (isCritical) {
        printf("  [Safety]  CRITICAL VOLTAGE. DISCONNECTING LOADS.\n");
    }
}

void Logger_Write(float voltage, bool isCritical) {
    // Simulating writing to EEPROM/SD
    printf("  [Logger]  Recording data point: { v: %.1f, crit: %d }\n", voltage, isCritical);
}
