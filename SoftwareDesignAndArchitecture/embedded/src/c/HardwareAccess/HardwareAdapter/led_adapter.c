#include "led_adapter.h"

// 1. Implement the Interface functions by delegating to the Proxy
void LedAdapter_TurnOn(void* instance) {
    // Cast generic void* back to our specific Adapter type
    LedAdapter* me = (LedAdapter*)instance;
    // Delegate to the real driver
    LedProxy_TurnOn(me->driver);
}

void LedAdapter_TurnOff(void* instance) {
    LedAdapter* me = (LedAdapter*)instance;
    LedProxy_TurnOff(me->driver);
}

int LedAdapter_IsOn(void* instance) {
    LedAdapter* me = (LedAdapter*)instance;
    return LedProxy_IsOn(me->driver);
}

// 2. Define the VTable
const ILight LedAdapter_Interface = {
    .turnOn = LedAdapter_TurnOn,
    .turnOff = LedAdapter_TurnOff,
    .isOn = LedAdapter_IsOn
};

// 3. Init
void LedAdapter_Init(LedAdapter* me, LedProxy* driver) {
    me->driver = driver;
}
