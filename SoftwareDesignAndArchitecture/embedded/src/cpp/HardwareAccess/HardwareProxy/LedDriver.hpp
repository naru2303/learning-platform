#ifndef LED_DRIVER_HPP
#define LED_DRIVER_HPP

#include <cstdint>
#include <concepts>

// Hardware Register definition (Memory Layout)
struct GpioRegisters {
    volatile std::uint32_t MODER;
    volatile std::uint32_t OTYPER;
    volatile std::uint32_t OSPEEDR;
    volatile std::uint32_t PUPDR;
    volatile std::uint32_t IDR;
    volatile std::uint32_t ODR;
};

// ============================================================================
// C++20 CONCEPT EXPLANATION
// ============================================================================
// WHAT IS A CONCEPT?
// A concept is a compile-time constraint on template parameters. It defines
// requirements that a type must satisfy to be used with a template.
//
// CURRENT STATUS: NOT USED
// This concept is DEFINED but NOT ACTUALLY USED in this file. Since LedDriver
// takes a raw std::uintptr_t (an integer) in its constructor and creates the
// GpioRegisters* internally via reinterpret_cast, there is no template type
// parameter to constrain. This makes the concept effectively "dead code".
//
// HOW TO USE IT (Example for learning):
// If LedDriver were a template class that accepted different register map types,
// you would apply the concept like this:
//
//   template<typename RegMapT>
//       requires HardwarePointer<RegMapT*>  // <-- Constraint applied here
//   class GenericDriver {
//       RegMapT* registers;
//       // ...
//   };
//
// WHY USE CONCEPTS?
// - Type Safety: Ensures only valid pointer types are used at compile time.
// - Better Error Messages: Compiler reports constraint violations clearly.
// - Self-Documenting: The concept name explains what the template expects.
//
// EXAMPLE USAGE:
//   volatile uint32_t* validPtr;
//   static_assert(HardwarePointer<decltype(validPtr)>);  // ✓ Passes
//   
//   char* invalidPtr;
//   static_assert(HardwarePointer<decltype(invalidPtr)>); // ✗ Fails
// ============================================================================
template<typename T>
concept HardwarePointer = requires(T p) {
    { *p } -> std::convertible_to<volatile std::uint32_t>;
};

class LedDriver {
public:
    // Explicit constructor to prevent implicit conversions
    // address is the base address of the GPIO Port
    constexpr explicit LedDriver(std::uintptr_t address, std::uint8_t pin) noexcept
        : registers_{reinterpret_cast<GpioRegisters*>(address)}, pin_mask_{1U << pin} {
        // In a real scenario, you might do initialization here or in an Init() method
        // But constructors are good for invariants.
    }

    // Delete copy to prevent creating multiple controllers for the same unique hardware resource
    // (Unless you are sure that's safe, but usually it's better to pass by reference)
    LedDriver(const LedDriver&) = delete;
    LedDriver& operator=(const LedDriver&) = delete;

    // Move is acceptable if we transfer ownership (though logic depends on system design)
    LedDriver(LedDriver&&) = default;
    LedDriver& operator=(LedDriver&&) = default;

    void turnOn() const noexcept {
        registers_->ODR |= pin_mask_;
    }

    void turnOff() const noexcept {
        registers_->ODR &= ~pin_mask_;
    }

    void toggle() const noexcept {
        registers_->ODR ^= pin_mask_;
    }

    [[nodiscard]] bool isOn() const noexcept {
        return (registers_->ODR & pin_mask_) != 0;
    }

private:
    GpioRegisters* const registers_;
    const std::uint32_t pin_mask_;
};

#endif // LED_DRIVER_HPP
