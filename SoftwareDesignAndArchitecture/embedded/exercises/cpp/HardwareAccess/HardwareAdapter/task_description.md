# Practice Task: Hardware Adapter for "BitCruncher" Timer

Your goal is to decouple the Application Logic from the specific `BitCruncher` Timer Proxy you wrote earlier.

## 1. The Scenario
The Application Layer needs a generic timer interface to perform delays or scheduling. It calls this interface `ITimer`.
However, your driver is named `TimerProxy` / `TimerDriver` and has specific functions like `Timer_SetReload` which the app doesn't like. The App prefers `start(milliseconds)`.

## 2. The Requirements


### C++ Version
1.  **Define Interface**: Abstract class `ITimer` in `ITimer.hpp`.
    *   `virtual void start(uint32_t timeoutMs) = 0;`
    *   `virtual bool isRunning() const = 0;`
2.  **Create Adapter**: `BitCruncherAdapter` class inheriting `ITimer` and wrapping `TimerDriver`.

## 3. Files to Create

*   `cpp_code/HardwareAdapter/Practice/ITimer.hpp`
*   `cpp_code/HardwareAdapter/Practice/BitCruncherAdapter.hpp`
