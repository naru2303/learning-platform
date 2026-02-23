#ifndef BMS_HPP
#define BMS_HPP

#include <array>
#include <algorithm>
#include <iostream>

// --- The Interface ---
// Pure virtual class defining the contract.
class IBatteryObserver {
public:
    virtual ~IBatteryObserver() = default;
    virtual void onVoltageChanged(float voltage, bool isCritical) = 0;
};

// --- The Subject ---
// Templated on MaxObservers to allow static allocation (No New/Malloc)
template <std::size_t MaxObservers>
class BatteryMonitor {
public:
    BatteryMonitor() : observerCount(0) {
        // Initialize array with nullptr
        observers.fill(nullptr);
    }

    bool addObserver(IBatteryObserver& observer) {
        if (observerCount >= MaxObservers) {
            std::cerr << "[Error] Max observers reached!\n";
            return false;
        }
        observers[observerCount++] = &observer;
        return true;
    }

    void setVoltage(float v) {
        voltage = v;
        bool crit = (voltage < 10.0f);
        notify(crit);
    }

private:
    float voltage = 0.0f;
    std::size_t observerCount;
    // Array of Pointers. The Observer objects themselves live on the stack or static global,
    // so we just store pointers to them. No ownership transfer.
    std::array<IBatteryObserver*, MaxObservers> observers;

    void notify(bool isCritical) {
        std::cout << "[Subject] Voltage: " << voltage << "V. Notifying...\n";
        for (std::size_t i = 0; i < observerCount; ++i) {
            if (observers[i]) {
                observers[i]->onVoltageChanged(voltage, isCritical);
            }
        }
    }
};

#endif
