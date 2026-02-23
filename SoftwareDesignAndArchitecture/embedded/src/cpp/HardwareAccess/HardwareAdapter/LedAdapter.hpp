#ifndef LED_ADAPTER_HPP
#define LED_ADAPTER_HPP

#include "ILight.hpp"
#include "../HardwareProxy/LedDriver.hpp"

// The Adapter
class LedAdapter : public ILight {
public:
    // Inject the specific driver via constructor
    explicit LedAdapter(LedDriver& driverRef) : driver(driverRef) {}

    void on() override {
        driver.turnOn(); // Delegation
    }

    void off() override {
        driver.turnOff();
    }

    bool getState() const override {
        return driver.isOn();
    }

private:
    LedDriver& driver; // Reference to the Adaptee
};

#endif // LED_ADAPTER_HPP
