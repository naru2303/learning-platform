#include <iostream>
#include "LedAdapter.hpp"

// Mock memory
alignas(std::uint32_t) std::uint8_t MOCK_CPP_MEM[1024];

// Application Logic
// Uses generic ILight, doesn't care about LedDriver details
void runDiagnostics(ILight& light) {
    std::cout << "Diagnostics: Testing Light..." << std::endl;
    light.on();
    if (light.getState()) {
        std::cout << "Diagnostics: Light OK (On)" << std::endl;
    }
    light.off();
}

int main() {
    const std::uintptr_t ADDR = reinterpret_cast<std::uintptr_t>(MOCK_CPP_MEM);
    
    // 1. Low-level Driver
    LedDriver realLed(ADDR, 3);

    // 2. Adapter
    LedAdapter adapter(realLed);

    // 3. Application
    runDiagnostics(adapter);

    return 0;
}
