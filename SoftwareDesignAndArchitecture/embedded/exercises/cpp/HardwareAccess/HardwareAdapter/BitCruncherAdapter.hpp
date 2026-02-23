#ifndef BIT_CRUNCHER_ADAPTER_HPP
#define BIT_CRUNCHER_ADAPTER_HPP

#include "ITimer.hpp"
#include "../../HardwareProxy/Practice/TimerDriver.hpp"

class BitCruncherAdapter : public ITimer {
public:
    // Inject the specific driver via constructor
    explicit BitCruncherAdapter(TimerDriver& driverRef) : driver(driverRef) {}

    void start(std::uint32_t timeoutMs) override {
        // Adapter Logic: Map milliseconds to ticks (assuming 1:1)
        driver.setReload(timeoutMs);
        driver.start();
    }

    bool isRunning() const override {
        // Inverted logic: If it hasn't expired, it is running
        return !driver.isExpired();
    }

private:
    TimerDriver& driver;
};

#endif // BIT_CRUNCHER_ADAPTER_HPP
