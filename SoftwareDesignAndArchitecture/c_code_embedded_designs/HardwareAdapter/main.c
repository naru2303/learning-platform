#include <stdio.h>
#include "led_adapter.h"

// Mock hardware memory
uint32_t MOCK_GPIO_MEM[20];

// Application Logic - NOTICE: It knows nothing about LedProxy!
// It only knows "ILight" interface and an opaque instance pointer.
void BlinkSystemLight(const ILight* light_interface, void* light_instance) {
    printf("App: Requesting Light ON...\n");
    ILight_TurnOn(light_interface, light_instance);
    
    printf("App: Requesting Light OFF...\n");
    ILight_TurnOff(light_interface, light_instance);
}

int main(void) {
    // 1. Setup the Low-Level stuff (Infrastructure code)
    LedProxy real_led;
    LedProxy_Init(&real_led, (uintptr_t)MOCK_GPIO_MEM, 5);

    // 2. Setup the Adapter
    LedAdapter adapter;
    LedAdapter_Init(&adapter, &real_led);

    // 3. Run the Application
    // Dependency Injection: Pass the adapter disguised as the generic interface
    BlinkSystemLight(&LedAdapter_Interface, &adapter);

    return 0;
}
