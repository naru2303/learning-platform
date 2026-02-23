#include "led_driver.h"

// Initialize the proxy with hardware address and pin details
void LedProxy_Init(LedProxy* const me, uintptr_t address, uint8_t pin) {
    me->base_addr = (GPIO_RegDef_t*)address;
    me->pin_number = pin;
    
    // Example: Configure pin as output in hardware
    // (In reality, this logic would represent specific bit manipulation for the register)
    uint32_t mode_mask = (1UL << (me->pin_number * 2));
    me->base_addr->MODER |= mode_mask; 
}

void LedProxy_TurnOn(LedProxy* const me) {
    // Access hardware via the cached base address
    me->base_addr->ODR |= (1UL << me->pin_number);
}

void LedProxy_TurnOff(LedProxy* const me) {
    me->base_addr->ODR &= ~(1UL << me->pin_number);
}

void LedProxy_Toggle(LedProxy* const me) {
    me->base_addr->ODR ^= (1UL << me->pin_number);
}

uint8_t LedProxy_IsOn(const LedProxy* const me) {
    return (me->base_addr->ODR & (1UL << me->pin_number)) ? 1 : 0;
}
