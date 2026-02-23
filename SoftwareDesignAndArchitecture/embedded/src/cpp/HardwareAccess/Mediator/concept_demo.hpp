#ifndef CONCEPT_DEMO_HPP
#define CONCEPT_DEMO_HPP

#include "ClimateComponents.hpp"

// ============================================================================
// DEMONSTRATION: Contract Enforcement (Old vs. New)
// ============================================================================
//
// Scenario: We have a class 'BrokenHeater' that is intended to be used as a 
// heater, but the developer forgot to implement the 'off()' method.

class BrokenHeater {
public:
    void on() { std::cout << "BrokenHeater ON\n"; }
    // ERROR: Missing off() implementation!
};

// ----------------------------------------------------------------------------
// 1. The Old Way (Pre-C++20) - "Late Failure"
// ----------------------------------------------------------------------------
// Without concepts, mistakes are caught only when the code inside the template
// actually tries to use the missing function.

template<typename T>
void oldStyleController(T& device) {
    device.on();
    
    // ERROR HAPPENS HERE (Inside the library/usage code):
    // The compiler will say: "class BrokenHeater has no member named 'off'"
    // This is confusing because the error points to valid library code,
    // not necessarily the broken class definition.
    device.off(); 
}


// ----------------------------------------------------------------------------
// 2. The New Way (C++20 Concepts) - "Early Failure" & "Explicit Contract"
// ----------------------------------------------------------------------------

// Ideally, we want to know that BrokenLoader is invalid IMMEDIATELLY,
// before we even try to pass it to a controller.

// The line you asked about acts as a compile-time Unit Test:
// static_assert(Switchable<BrokenHeater>);

/* 
 * IF YOU UNCOMMENT THE LINE ABOVE, THE BUILD FAILS WITH:
 * 
 * error: static_assert failed
 * note: because 'BrokenHeater' does not satisfy 'Switchable'
 * note: the required expression 'dev.off()' is invalid
 * 
 * WHY THIS IS BETTER:
 * 1. Locality: The error points to the Assertion line, saying "This class fails the contract".
 * 2. Clarity: It tells you exactly WHICH requirement is missing (dev.off is invalid).
 * 3. Prevention: It stops you from even trying to use the class in the rest of the system.
 */

// This valid assertion passes silently:
static_assert(Switchable<Heater>); // OK: Heater has on() and off()

#endif // CONCEPT_DEMO_HPP
