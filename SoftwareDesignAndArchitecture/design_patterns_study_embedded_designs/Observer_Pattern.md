# Design Pattern: Observer (Publish-Subscribe)

## 1. Concept: What is it?
The Observer pattern defines a one-to-many dependency between objects so that when one object (the **Subject**) changes state, all its dependents (the **Observers**) are notified and updated automatically. 

In embedded systems, this is often called **Publish-Subscribe**. It allows sensors or event generators to push data to consumers without knowing who those consumers are.

### When to use it?
*   **Data Distribution:** When you have a data source (e.g., GPS, temperature sensor, battery monitor) that needs to be used by multiple independent parts of the system (e.g., UI, data logger, safety controller).
*   **Decoupling:** When the "sensor" shouldn't care who is listening. You want to add a new "listener" (e.g., a debug logger) without modifying the sensor's code.
*   **Asynchronous Events:** When an event occurs at an unpredictable time (interrupts, user button press) and multiple actions need to happen immediately.

### Why is it the best for "1-to-Many" logic?
Without Observer, the subject (e.g., `BatteryMonitor`) looks like this:

```c
void Battery_Check(void) {
    if (voltage < LOW) {
        Display_ShowLowBattery();   // Coupled to Display
        Safety_CutoffPower();       // Coupled to Safety
        Logger_LogEvent("Low Bat"); // Coupled to Logger
    }
}
```
**The Problem:** Every time you add a new feature (e.g., "Send Bluetooth Alert"), you must edit the `Battery_Check` function. This violates the Open/Closed Principle.

**The Solution:**
```c
void Battery_Check(void) {
    if (voltage < LOW) {
        Observer_NotifyAll(BATTERY_LOW_EVENT);
    }
}
```
Now `BatteryMonitor` doesn't care. It just shouts "Battery Low!", and whoever subscribed handles it.

---

## 2. Decision Matrix: When to choose over others?

| Feature | Observer | vs. Mediator | vs. Polling |
| :--- | :--- | :--- | :--- |
| **Direction** | One-to-Many (1 Broadcasts to N) | Many-to-Many (Coordinator talks to A, B, C) | Many-to-One (Client asks, Sensor answers) |
| **Coupling** | Subject doesn't know Observers. | Mediator knows everything. | Client knows Sensor. |
| **Trigger** | "Push" (Event driven) | "Logic" (State driven) | "Pull" (Time driven) |
| **Best For** | Pure data distribution (Sensor -> UI/Logs). | Complex interaction logic (If Temp > X AND Door is Open...). | Simple, slow changing data where immediacy isn't critical. |

### Pros & Cons in Embedded

**Pros:**
*   **Extensibility:** Add new listeners (observers) without recompiling the subject.
*   **separation of Concerns:** The sensor focuses on sensing; the display focuses on displaying.
*   **Dynamic configuration:** Systems can subscribe/unsubscribe at runtime (e.g., diagnostic tools only listen when connected).

**Cons & Embedded Risks:**
*   **Notification Order:** You usually cannot guarantee which observer is notified first.
*   **Dynamic Memory:** Standard implementations use `std::vector` or `linked lists`. In embedded, we must use **Fixed-Size Arrays** or **Intrusive Lists** to avoid `malloc`.
*   **Reentrancy/Deadlock:** If an observer calls back into the subject, or if the notification happens inside an interrupt service routine (ISR), it can cause race conditions.

---

## 3. Implementation Patterns (Embedded C & Modern C++)

### Protocol in C
In C, we use **Function Pointers** as the interface. The Subject maintains an array of function pointers.

### Protocol in C++ (Modern)
In C++, we use **Concepts** to define what an Observer looks like, and **Templates** or **Interfaces** to store them. Since we avoid `new/delete`, we often use a `max_observers` template parameter or `std::pmr` (polymorphic memory resources) if available, but usually a simple `std::array` or `static_vector` is best.

---

## 4. Learning Tasks

### Task 1: The Battery Management System (BMS) - [Agent Implemented]
**Scenario:** A Battery Monitor is the Subject. It measures voltage.
**Observers:**
1.  **Display:** Shows the voltage on the screen.
2.  **SafetySystem:** Disconnects load if voltage is critical.
3.  **DataLogger:** Writes the value to EEPROM.

**Why this fits:** Typical embedded scenario where one critical hardware value drives UI, Safety, and Storage simultaneously.

### Task 2: The Intrusion Detection System - [User Practice]
**Scenario:** You have a `MotionSensor` (Subject).
**Requirements:**
1.  Create an interface `INotifiable` (or functionality).
2.  Implement `MotionSensor` that holds a list of observers.
3.  Create Observers:
    *   `Siren`: Prints "WEE WOO WEE WOO" when motion detected.
    *   `Camera`: Prints "Recording started..." when motion detected.
    *   `CloudUploader`: Prints "Sending alert to API..." when motion detected.
4.  **Constraint:** In C++, do NOT use `std::vector` or `new`. Use a fixed-size strategy (e.g., `std::array` inside the Subject with a counter).

---
