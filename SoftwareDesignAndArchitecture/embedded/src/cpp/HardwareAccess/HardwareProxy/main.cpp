#include "LedDriver.hpp"
#include <iostream>
#include <vector>

// Mock memory for the hardware registers
// alignas is important to simulate actual register boundary requirements
alignas(std::uint32_t) std::uint8_t MOCK_GPIO_MEMORY[1024];

int main() {
    // Determine the address at runtime
    const std::uintptr_t GPIO_BASE_ADDR = reinterpret_cast<std::uintptr_t>(MOCK_GPIO_MEMORY);

    // Instantiate the Proxy
    // We act as if MOCK_GPIO_MEMORY is the hardware address
    auto led = LedDriver(GPIO_BASE_ADDR, 5);

    led.turnOn();

    if (led.isOn()) {
        std::cout << "LED is ON (C++ Proxy verified)" << std::endl;
    }

    led.toggle();
    
    // Example of modern C++ initialization usage
    // Using auto and structured binding (if we had a struct returned) or just standard object
    
    return 0;
}
