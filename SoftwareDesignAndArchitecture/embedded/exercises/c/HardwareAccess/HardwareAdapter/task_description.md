# Practice Task: Hardware Adapter for "BitCruncher" Timer

Your goal is to decouple the Application Logic from the specific `BitCruncher` Timer Proxy you wrote earlier.

## 1. The Scenario
The Application Layer needs a generic timer interface to perform delays or scheduling. It calls this interface `ITimer`.
However, your driver is named `TimerProxy` / `TimerDriver` and has specific functions like `Timer_SetReload` which the app doesn't like. The App prefers `start(milliseconds)`.

## 2. The Requirements

### C Version
1.  **Define Interface**: Create `itimer.h` struct with function pointers:
    *   `void (*start)(void* instance, uint32_t timeout_ms);`
    *   `int (*is_running)(void* instance);`
2.  **Create Adapter**: implement `TimerAdapter` that wraps `TimerProxy`.
    *   *Note*: Use `arr = timeout_ms` (assume 1 tick = 1 ms for simplicity).
    *   Implement `start` by calling `SetReload` then `Start`.

## 3. Files to Create
*   `c_code/HardwareAdapter/Practice/itimer.h`
*   `c_code/HardwareAdapter/Practice/timer_adapter.h` & `.c`
