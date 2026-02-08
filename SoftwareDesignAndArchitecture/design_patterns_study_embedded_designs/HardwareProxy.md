# Hardware Proxy Design Pattern

## 1. When to use this design pattern?
Use the **Hardware Proxy** pattern when you need to access hardware devices (sensors, actuators, controllers) from your software. It is applicable whenever you have hardware registers, memory-mapped I/O, or specific hardware addresses that need to be read or written.

## 2. Why is it the best in my use case?
It is the best approach because it **encapsulates** the volatile and low-level details of the hardware (like absolute memory addresses, bit-masking, and register layouts) into a structured software entity.
- **Encapsulation:** It hides the "ugly" hardware bit-banging from the business logic.
- **Type Safety:** It turns raw memory addresses into typed structures or classes.
- **Flexibility:** If the hardware address changes (e.g., board revision), you only change the Proxy, not the application logic.

## 3. How do I know it's the best for my use case?
You know it's the best if:
- You find yourself writing `*(volatile uint32_t*)(0x40021000) = 0x01;` scattered throughout your code.
- You are writing code that depends on specific hardware bit positions.
- You want to be able to unit test your application logic without the actual hardware connected (by mocking the Proxy).

## 4. When to choose over the other?
- **Vs. Raw Pointers:** Choose Proxy over raw pointers immediately for any project larger than a blinking LED demo. Raw pointers are error-prone and hard to maintain.
- **Vs. Hardware Adapter:** Use **Proxy** when you just want to *access* the hardware as it is. Use **Adapter** when you need to *change* the interface of the hardware to match a pre-existing interface expected by the client (e.g., making a specific temperature sensor look like a generic `ITemperatureSensor`). The Proxy is often the lower layer used *by* an Adapter.

## 5. Pros and Cons

### Pros
- **Decoupling:** Application code doesn't need to know physical addresses.
- **Readability:** `led.turnOn()` is readable; `*0x40020C14 |= 0x20` is not.
- **Testability:** Proxies can be easily mocked or stubbed to test higher-level logic on a host PC.
- **Safety:** Can enforce read-only access to read-only registers via implementation (const correctness).

### Cons
- **Overhead:** A slight function call overhead compared to inline macros (though modern compilers and `inline` keywords often eliminate this).
- **Complexity:** Requires writing a struct/class for every hardware peripheral, which takes more initial setup time than just `#define`.

## 6. Implementation in C and C++ (Embedded)

### C Implementation
In C, the pattern is implemented using a **struct** to define the register map and a **pointer** to the base address. Functions take a pointer to the instance (`me` pointer) to operate on the specific hardware.

*See `c_code/HardwareProxy/` files for full source.*

**Key features:**
- `struct` overlay for memory mapping.
- `volatile` keyword to prevent compiler caching.
- object-based design (passing `self`/`me` pointer).

### C++ Implementation (Modern Embedded)
In C++, we use a **class** to provide stricter encapsulation.
*See `cpp_code/HardwareProxy/` files for full source.*

**Key features:**
- `constexpr` constructors for compile-time initialization where possible.
- `delete` copy constructors to prevent duplicating the hardware handle (Single Responsibility).
- `reinterpret_cast` encapsulated inside the class to bridge the gap between integers and pointers safely.
- No `virtual` functions used here to avoid vtable overhead (unless polymorphism is explicitly required).
