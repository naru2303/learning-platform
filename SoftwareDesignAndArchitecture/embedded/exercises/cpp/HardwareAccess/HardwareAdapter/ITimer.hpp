#ifndef I_TIMER_HPP
#define I_TIMER_HPP

#include <cstdint>

// Abstract Base Class (Interface)
class ITimer {
public:
    virtual void start(std::uint32_t timeoutMs) = 0;
    virtual bool isRunning() const = 0;
    
    virtual ~ITimer() = default; // Essential for polymorphic destruction
};

#endif // I_TIMER_HPP