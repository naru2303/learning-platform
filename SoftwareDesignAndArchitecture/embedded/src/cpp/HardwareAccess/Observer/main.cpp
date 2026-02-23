#include "Bms.hpp"
#include "Observers.hpp"

int main() {
    // 1. Static Allocation of Components
    // They exist for the lifetime of the scope (or could be global/static)
    Display display;
    SafetySystem safety;
    DataLogger logger;

    // 2. The Subject (Capacity = 5)
    BatteryMonitor<5> bms;

    // 3. Wiring (Dependency Injection)
    bms.addObserver(display);
    bms.addObserver(safety);
    bms.addObserver(logger);

    std::cout << "--- C++ Observer Pattern (Static Allocation) ---\n";

    // 4. Execution
    bms.setVoltage(12.0f);
    bms.setVoltage(9.8f); // Critical

    return 0;
}
