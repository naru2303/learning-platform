# Mediator Design Pattern (Hardware Access / Coordination)

## 1. When to use this design pattern?
Use the **Mediator** pattern when:
- You have a set of hardware components (or software objects) that need to communicate with each other in complex ways.
- The interaction logic is distributed among the components, making them tightly coupled (e.g., the Temperature Sensor directly commanding the Heater).
- You want to reuse a component (e.g., the Motor driver) in a different system, but it is "polluted" with logic specific to another component (e.g., it checks a specific sensor).

## 2. Why is it the best in my use case?
It is the best choice because it **centralizes complex control logic**.
Instead of an $N \times N$ communication web (everyone talking to everyone), you have a $1 \to N$ star topology. The Mediator becomes the "brain" that coordinates the "limbs" (Colleagues).

## 3. How do I know it's the best for my use case?
Ask yourself: **"If I replace the Temperature Sensor with a model from a different vendor, do I have to re-compile the Heater Driver?"**
- If **YES**: You have tight coupling. You need a Mediator.
- If **NO**: You might already have a layered architecture or a Mediator in place.

## 4. When to choose over the other?
- **Vs. Observer**: Use **Observer** when you just want to broadcast data ("I changed!") without caring who listens or what they do. Use **Mediator** when the interaction requires a decision or coordination ("If Sensor A is high AND Switch B is on, THEN start Motor C").
- **Vs. Facade**: A **Facade** simplifies access to a sub-system (usually one-way control). A **Mediator** facilitates multidirectional interaction/collaboration between components.

## 5. Pros and Cons

| Pros | Cons |
| :--- | :--- |
| **Decoupling**: Colleagues (Sensors, Actuators) don't know about each other. They only know the generic Mediator interface (or nothing at all). | **Complexity**: The Mediator itself can become a "God Object" or "Monolith" containing too much logic that serves too many masters. |
| **Reuse**: Hardware drivers remain pure and reusable. | **Performance**: Adds a slight layer of indirection (function calls) compared to direct access. |
| **Clarity**: System-level policy (e.g., "Safety Shutdown") is readable in one place, not scattered across 10 files. | |

## 6. Implementation in C and C++

### C Implementation
The Mediator is usually a `struct` that holds pointers to the "Colleagues" (the hardware proxies).
- The Colleagues might have a back-pointer to the Mediator (if they need to notify it).
- Or, the Mediator polls the Colleagues and decides what to do from a main loop.

### C++ Implementation
The Mediator is a `class`.
- It takes references/pointers to `HardwareProxy` objects in its constructor.
- It exposes high-level operations (`regulateTemperature()`) that orchestrate the lower-level calls.

---

# Practice Task: "The Climate Controller"

We will build a simple feedback loop system using the **Mediator** pattern.

**Components (Colleagues):**
1.  **Thermometer**: Reads current temperature.
2.  **Heater**: Can be turned On/Off.
3.  **Cooler**: Can be turned On/Off.

**The Mediator (ClimateController):**
-   **Rule 1**: If Temp < 20.0°C, Heater ON, Cooler OFF.
-   **Rule 2**: If Temp > 25.0°C, Heater OFF, Cooler ON.
-   **Rule 3**: Otherwise (20-25), Both OFF.

## Task Requirements
1.  **Proxies**: Create mock proxies for Thermometer, Heater, and Cooler.
2.  **Mediator**: Implement `ClimateController` that coordinates them.
3.  **Constraint**: The Heater must **never** check the Thermometer directly.

Let's start by looking at the C implementation structure I will generate for you.
