#ifndef CLIMATE_COMPONENTS_HPP
#define CLIMATE_COMPONENTS_HPP

#include <iostream>
#include <concepts>

// --- C++20 Definitions for Component Contracts ---

// Concept: Something that can be turned on and off
template<typename T>
concept Switchable = requires(T dev) {
    { dev.on() } -> std::same_as<void>;
    { dev.off() } -> std::same_as<void>;
};

// Concept: Something that provides temperature
template<typename T>
concept TemperatureSource = requires(T sens) {
    { sens.read() } -> std::convertible_to<float>;
};


// --- Concrete Components ---

class Thermometer {
public:
    explicit constexpr Thermometer(float initial) noexcept : temp(initial) {}
    
    // [[nodiscard]]: Issues a compiler warning if the return value is ignored.
    // Critical for pure query methods: calling read() without using the result is a logic error (dead code).
    [[nodiscard]] float read() const noexcept { return temp; }
    
    // Test helper (not part of concept, but useful)
    void setMockTemp(float t) noexcept { temp = t; }

private:
    float temp;
};

class Heater {
public:
    void on() { 
        if(!isOn) { 
            std::cout << "  [HW] Heater ON" << std::endl; 
            isOn = true; 
        } 
    }
    void off() { 
        if(isOn) { 
            std::cout << "  [HW] Heater OFF" << std::endl; 
            isOn = false; 
        } 
    }
private:
    bool isOn = false;
};

class Cooler {
public:
    void on() { 
        if(!isOn) { 
            std::cout << "  [HW] Cooler ON" << std::endl; 
            isOn = true; 
        } 
    }
    void off() { 
        if(isOn) { 
            std::cout << "  [HW] Cooler OFF" << std::endl; 
            isOn = false; 
        } 
    }
private:
    bool isOn = false;
};

// --- Contract Enforcement ---
// static_assert coupled with Concepts acts as a "compile-time unit test".
// It guarantees that these classes perfectly implement the required interfaces.
// If, for example, Heater was missing on(), the build would fail explicitly HERE,
// providing immediate, clear feedback on contract violations.
static_assert(TemperatureSource<Thermometer>);
static_assert(Switchable<Heater>);
static_assert(Switchable<Cooler>);

#endif // CLIMATE_COMPONENTS_HPP
