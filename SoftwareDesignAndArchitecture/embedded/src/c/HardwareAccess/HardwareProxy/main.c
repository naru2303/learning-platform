#include "led_driver.h"
#include <stdio.h>

// Mock Hardware Address for simulation
uint32_t VIRTUAL_GPIO_PORT_A[1024]; 

#define GPIOA_BASE ((uintptr_t)VIRTUAL_GPIO_PORT_A)

int main(void) {
    LedProxy system_led;
    
    // Initialize the proxy (bind it to address and pin)
    LedProxy_Init(&system_led, GPIOA_BASE, 5);

    // Use the proxy
    LedProxy_TurnOn(&system_led);
    
    if (LedProxy_IsOn(&system_led)) {
        printf("LED is ON!\n");
    }

    LedProxy_TurnOff(&system_led);

    return 0;
}
