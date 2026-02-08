#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>

// Hardware Register Map Overlay
typedef struct {
    volatile uint32_t MODER;   // Mode register
    volatile uint32_t OTYPER;  // Output type register
    volatile uint32_t OSPEEDR; // Output speed register
    volatile uint32_t PUPDR;   // Pull-up/pull-down register
    volatile uint32_t IDR;     // Input data register
    volatile uint32_t ODR;     // Output data register
} GPIO_RegDef_t;

// The Proxy Struct (Context)
typedef struct {
    GPIO_RegDef_t* base_addr; // Pointer to the actual hardware address
    uint8_t pin_number;       // Specific pin this proxy controls
} LedProxy;

// Constructor-like initializer
void LedProxy_Init(LedProxy* const me, uintptr_t address, uint8_t pin);

// Behavior
void LedProxy_TurnOn(LedProxy* const me);
void LedProxy_TurnOff(LedProxy* const me);
void LedProxy_Toggle(LedProxy* const me);
uint8_t LedProxy_IsOn(const LedProxy* const me);

#endif // LED_DRIVER_H
