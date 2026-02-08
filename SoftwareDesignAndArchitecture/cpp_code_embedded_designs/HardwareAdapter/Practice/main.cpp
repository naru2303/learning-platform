#include <iostream>
#include "BitCruncherAdapter.hpp"

// Mock memory
alignas(std::uint32_t) std::uint8_t MOCK_TIMER_MEM_CPP[1024];

// Application Logic
// Uses generic ITimer, doesn't know about Hardware
void performTaskWithDelay(ITimer& timer) {
    std::cout << "App: Starting 500ms delay..." << std::endl;
    timer.start(500);
    
    if (timer.isRunning()) {
        std::cout << "App: Timer is currently running." << std::endl;
    }
}

int main() {
    constexpr std::uintptr_t ADDR = reinterpret_cast<std::uintptr_t>(MOCK_TIMER_MEM_CPP);
    
    // 1. Low-level Driver
    TimerDriver realTimer(ADDR);

    // 2. Adapter
    BitCruncherAdapter adapter(realTimer);

    // 3. Application
    performTaskWithDelay(adapter);

    return 0;
}
