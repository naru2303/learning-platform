#ifndef BMS_OBSERVERS_H
#define BMS_OBSERVERS_H

#include <stdbool.h>

// These functions match the 'BatteryObserverCB' signature

void Display_Update(float voltage, bool isCritical);
void Safety_Check(float voltage, bool isCritical);
void Logger_Write(float voltage, bool isCritical);

#endif
