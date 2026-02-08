#ifndef LED_ADAPTER_H
#define LED_ADAPTER_H

#include "ilight.h"
#include "../HardwareProxy/led_driver.h" // The "Adaptee"

// The Adapter Structure
typedef struct {
    LedProxy* driver; // Helper reference (The Adaptee)
} LedAdapter;

// Implementation of the Interface functions
void LedAdapter_TurnOn(void* instance);
void LedAdapter_TurnOff(void* instance);
int  LedAdapter_IsOn(void* instance);

// The constant Interface VTable for this Adapter
extern const ILight LedAdapter_Interface;

// Initialization
void LedAdapter_Init(LedAdapter* me, LedProxy* driver);

#endif // LED_ADAPTER_H
