# Hardware Adapter Design Pattern

## 1. When to use this design pattern?
Use the **Hardware Adapter** when:
- You have an existing application component that expects a specific interface (e.g., `start_timer()`), but your hardware driver has a different signature (e.g., `BitCruncher_Enable()`).
- You want to be able to switch between different hardware chips (e.g., STM32 vs. TI vs. Simulator) without changing the high-level application code.
- You want to integrate legacy code or third-party drivers that don't match your system's architecture.

## 2. Why is it the best in my use case?
It decouples the **Domain Logic** from the **Hardware Details**.
- **Portability:** Your main application relies on `IGpio`, not `STM32_GPIO`.
- **Maintainability:** If the hardware changes, you only write a new Adapter; you don't touch the application.

## 3. How differs from Proxy?
- **Proxy**: Represents the hardware *exactly as it is* (1:1 mapping to registers).
- **Adapter**: Represents the hardware *as the application wants it to be* (mapping to a domain interface).

## 4. Implementation in C (Polymorphism)
In C, adapters are often implemented using **Virtual Function Tables (vtables)** or structs of function pointers.

**Example Structure:**
```c
// The "Interface"
typedef struct {
    void (*turnOn)(void* instance);
    void (*turnOff)(void* instance);
} IDigitalOut;

// The Application uses IDigitalOut, not the specific LedDriver.
```

## 5. Implementation in C++ (Interfaces)
In C++, use **Abstract Base Classes** (pure virtual functions) or **Templates** (static polymorphism).

**Example:**
```cpp
class IDigitalOut {
public:
    virtual void turnOn() = 0;
    virtual ~IDigitalOut() = default;
};

// Adapter
class LedAdapter : public IDigitalOut {
    LedDriver& driver; // Composition
public:
    void turnOn() override { driver.turnOn(); }
};
```
