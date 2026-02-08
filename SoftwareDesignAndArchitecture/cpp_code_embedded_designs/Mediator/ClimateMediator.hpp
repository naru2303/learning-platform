#ifndef CLIMATE_MEDIATOR_HPP
#define CLIMATE_MEDIATOR_HPP

#include "ClimateComponents.hpp"

// The Mediator Template
// We use C++20 'requires' clause to enforce that generic types T, H, C
// must behave like a Thermometer, Heater, and Cooler.
//
// Benefits: 
// 1. Zero vtable overhead (Static Polymorphism).
// 2. We can swap in "MockThermometer" for testing instantly without inheritance.

template <TemperatureSource SensorT, Switchable HeaterT, Switchable CoolerT>
class ClimateMediator {
public:
    // Dependency Injection via References
    constexpr ClimateMediator(SensorT& t, HeaterT& h, CoolerT& c) noexcept
        : sensor(t), heater(h), cooler(c) {}

    // The Logic Coordination
    void update() {
        // We can check constraints at compile time, or use 'auto' with newer standards.
        float currentTemp = sensor.read();
        std::cout << "State: Temp=" << currentTemp << "C -> ";

        if (currentTemp < 20.0f) {
            heater.on();
            cooler.off();
        } 
        else if (currentTemp > 25.0f) {
            heater.off();
            cooler.on();
        } 
        else {
            heater.off();
            cooler.off();
        }
    }

private:
    SensorT& sensor;
    HeaterT& heater;
    CoolerT& cooler;
};

#endif // CLIMATE_MEDIATOR_HPP
