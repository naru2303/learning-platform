/**
 * @file TimerDriver.hpp
 * @brief Proxy Driver for BitCruncher Timer Peripheral
 * @details This header defines the proxy structure and function prototypes
 * @author Houssem Chekili 
 */


#ifndef TIMER_DRIVER_HPP
#define TIMER_DRIVER_HPP

#include <cstdint>

// TODO 1: Define Register Map (or use register constants)
struct TimerRegisters {
    // volatile std::uint32_t ...
    volatile std::uint32_t CR;   // Control Register
    volatile std::uint32_t SR;   // Status Register
    volatile std::uint32_t ARR;  // Auto-Reload Register
    const volatile std::uint32_t CNT;  // Counter Register (Read-Only enforcement
};

class TimerDriver {
public:
    // TODO 2: Constructor
    // explicit TimerDriver(std::uintptr_t baseAddr) ...
    explicit TimerDriver(std::uintptr_t timerAddr) noexcept
        : registers(reinterpret_cast<TimerRegisters*>(timerAddr)) { };
        

    // TODO 3: Methods
    void init() const noexcept 
    {
        // Additional initialization if needed, setting bits in registers

        registers->CR = 0; // Example: Reset Control Register
    }

    void start() const noexcept 
    {
        registers->CR |= TIMER_CR_ENABLE; 
    }

    void stop() const noexcept 
    {
        registers->CR &= ~TIMER_CR_ENABLE; 
    }

    void setReload(std::uint32_t ticks) const noexcept 
    {
        registers->ARR = ticks;
    }
    
    [[nodiscard]] std::uint32_t getCounter() const noexcept 
    {
        return registers->CNT;
    }

    void clearFlag() const noexcept 
    {
        registers->SR &= ~TIMER_SR_UIF;
    }

    [[nodiscard]] bool isExpired() const noexcept 
    {
        return (registers->SR & TIMER_SR_UIF) != 0;
    }
    
private:
    TimerRegisters* const registers;

    static constexpr std::uint32_t TIMER_CR_ENABLE  = (1U << 0);
    static constexpr std::uint32_t TIMER_CR_IRQ_EN  = (1U << 4);
    static constexpr std::uint32_t TIMER_SR_UIF     = (1U << 0);
};

#endif // TIMER_DRIVER_HPP
