#ifndef OBSERVERS_HPP
#define OBSERVERS_HPP

#include "Bms.hpp"
#include <iostream>

class Display : public IBatteryObserver {
public:
    void onVoltageChanged(float voltage, bool isCritical) override {
        if (isCritical) {
            std::cout << "  [Display] !! LOW BATT !! (" << voltage << ")\n";
        } else {
            std::cout << "  [Display] " << voltage << "V\n";
        }
    }
};

class SafetySystem : public IBatteryObserver {
public:
    void onVoltageChanged(float voltage, bool isCritical) override {
        if (isCritical) {
            std::cout << "  [Safety]  Cutting Power to Motors.\n";
        }
    }
};

class DataLogger : public IBatteryObserver {
public:
    void onVoltageChanged(float voltage, bool isCritical) override {
        std::cout << "  [Logger]  Saved to Flash: " << voltage << "\n";
    }
};

#endif
