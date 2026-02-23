#include "HardwareProxy/Practice/TimerDriver.hpp"
#include <iostream>
#include <vector>

// Mock memory for the hardware registers
// alignas is important to simulate actual register boundary requirements
alignas(std::uint32_t) std::uint8_t MOCK_TIMER_MEMORY[1024];

int main() {
    // Determine the address at runtime or compile time
    constexpr std::uintptr_t TIMER_BASE_ADDR = reinterpret_cast<std::uintptr_t>(MOCK_TIMER_MEMORY);

    // Instantiate the Proxy
    auto timer = TimerDriver(TIMER_BASE_ADDR);

    timer.init(); 

    timer.setReload(1000);
    timer.start();
    std::cout << "Timer started with reload value 1000." << std::endl;
    std::uint32_t counter = timer.getCounter();
    std::cout << "Current Timer Counter: " << counter << std::endl;
    timer.stop();
    std::cout << "Timer stopped." << std::endl;

    
    return 0;
}
