# Design Patterns for Embedded Systems in C

**Source:** "Design Patterns for Embedded Systems in C" by Bruce Powel Douglass

The book provides a comprehensive toolkit for embedded software engineers to apply optimized, reusable solutions to recurring problems within resource-constrained environments.

---

## Extracted Design Patterns (When and Why to Use)

The book categorizes patterns into four main domains: **Hardware Access**, **Concurrency/Resource Management**, **State Machines**, and **Safety/Reliability**.

### Hardware Access Patterns

| Pattern Name | When and Why to Use |
| :--- | :--- |
| **Hardware Proxy** | Use to encapsulate hardware access and protect application code from changes in the physical interface or bit-encoding. |
| **Hardware Adapter** | Use to convert an existing hardware interface into an interface expected by the application, facilitating hardware reuse. |
| **Mediator** | Use to coordinate complex interactions between multiple hardware elements (e.g., robot arm joints) to achieve system-level goals. |
| **Observer** | Use to distribute sensor data to multiple clients dynamically without the server needing prior knowledge of its clients. |
| **Debouncing** | Use to reject intermittent signals caused by the mechanical bouncing of metal contacts in switches or buttons. |
| **Interrupt** | Use to handle high-urgency events by immediately pausing normal processing to respond to hardware signals. |
| **Polling** | Use to periodically check for new data when events are not highly urgent or hardware cannot generate interrupts. |

### Concurrency Patterns

| Pattern Name | When and Why to Use |
| :--- | :--- |
| **Cyclic Executive** | Use for small or safety-critical systems where a simple infinite loop can run tasks in sequence with low overhead. |
| **Static Priority** | Use with an RTOS to schedule tasks based on urgency or criticality, allowing high-priority events to preempt lower ones. |
| **Critical Region** | Use to prevent preemption during short, time-critical actions by disabling task switching or interrupts. |
| **Guarded Call** | Use mutex semaphores to protect shared resources from simultaneous access by multiple threads. |
| **Queuing** | Use for asynchronous communication between tasks, allowing the sender to "send and forget" while the receiver processes messages later. |
| **Rendezvous** | Use to synchronize multiple tasks based on complex preconditions before they are allowed to proceed. |
| **Simultaneous Locking** | Use to avoid deadlock by requiring a task to lock all required resources at once or none at all. |
| **Ordered Locking** | Use to eliminate circular waiting (deadlock) by forcing tasks to lock shared resources in a specific, global numerical order. |

### State Machine Patterns

| Pattern Name | When and Why to Use |
| :--- | :--- |
| **Single Event Receptor** | Use for a simple implementation where one function receives all events, often used for both synchronous and asynchronous delivery. |
| **Multiple Event Receptor** | Use for synchronous state machines where each event has its own specific handler function for simpler logic. |
| **State Table** | Use for large, flat state spaces to achieve constant-time performance ($O(1)$) regardless of the number of states. |
| **State Pattern** | Use to localize behavior by creating separate objects for each state, making it easy to add or modify states. |
| **Decomposed AND-State** | Use to implement orthogonal regions (concurrency within a state) by decomposing a state machine into interacting objects. |

### Safety/Reliability Patterns

| Pattern Name | When and Why to Use |
| :--- | :--- |
| **One's Complement** | Use to detect memory corruption by storing critical data twice -- normally and as a bit-inverted copy -- and comparing them. |
| **CRC (Cyclic Redundancy)** | Use for large data sets to detect bit corruption using polynomial-based error-detection codes. |
| **Smart Data** | Use for defensive design by binding data with operations that automatically check for range and validity constraints. |
| **Channel** | Use as a unit of large-scale redundancy to organize end-to-end data processing from sensor to actuator. |
| **Protected Single Channel** | Use to enhance a single channel by adding data validation checks at key transformation points. |
| **Dual Channel** | Use for high reliability by using redundant channels (homogeneous or heterogeneous) to detect faults or continue operation. |

---

## What an Embedded Engineer Must Know from This Book

1. **Object-Oriented Programming in C:** You can implement classes, encapsulation, and polymorphism in C using structs to hold data and function pointers for behaviors. Using a `me` pointer as the first argument in functions allows multiple instances of a "class" to manage their own data.
2. **Embedded Constraints:** Engineers must prioritize minimizing recurring costs (memory, power, compute) because embedded hardware is rarely user-extensible.
3. **Real-Time Correctness:** In real-time systems, timeliness is a part of correctness. "Hard" real-time systems must meet deadlines strictly, while "soft" systems use stochastic measures.
4. **Priority Inversion and Deadlock:** You must understand unbounded priority inversion, where intermediate-priority tasks block a high-priority task. Using priority inheritance or simultaneous locking are key strategies to prevent system failure.
5. **State Machine Efficiency:** FSMs are the best way to handle event-driven behavior. Engineers should know how to choose between table-driven machines (for speed) and state pattern objects (for flexibility).
6. **Safety vs. Reliability:** Reliability is about availability (up-time), while safety is about reducing risk and hazards. Sometimes a "safe" system is less reliable if it frequently enters a "fault-safe" shutdown state.

---

## Book Summary and Takeaways

**Summary:** The book introduces an agile, model-based process called Harmony/ERT. It posits that design patterns are optimization tools used to improve a system's quality of service (QoS) -- such as performance, safety, and reliability -- after a functional model is built. It bridges the gap between high-level software engineering concepts (like UML and OOP) and low-level C implementation for "bare-metal" or RTOS environments.

**Key Takeaways:**
- **Design is Optimization:** Patterns are not just for making code "work"; they are for making code optimally efficient regarding specific criteria like memory or speed.
- **Trade-Off Analysis:** Every pattern has consequences (pros and cons). Engineers should use a weighted decision matrix to select patterns based on prioritized system requirements.
- **Redundancy for Safety:** To protect against hardware failures (random) and software errors (systematic), you must implement architectural redundancy (channels) and data-level redundancy (One's Complement, CRC).
- **Flattening Hierarchy:** While nested and AND-states are powerful in UML, they are often implemented by "flattening" the state space into a simpler flat structure to save memory and improve speed in C.

---

## Additional Patterns and Sub-Variants

### Architectural Infrastructure Patterns

| Pattern Name | When and Why to Use |
| :--- | :--- |
| **Microkernel Architecture** | Often used to build scalable RTOSs where only necessary services are loaded into memory. |
| **Broker / Data Bus Pattern** | Used in larger embedded middleware (like CORBA or DDS) to manage communication across distributed processors. |

### Dual Channel Sub-Patterns (Safety/Reliability)

| Pattern Name | When and Why to Use |
| :--- | :--- |
| **Homogeneous Redundancy** | Replicating identical channels to protect against random hardware failures. |
| **Heterogeneous Redundancy** | Using different designs/code for each channel to protect against both failures and systematic software errors. |
| **Triple Modular Redundancy (TMR)** | Using three channels and a Channel Arbiter to vote on the correct output. |
| **Sanity-Check Pattern** | A primary channel paired with a low-fidelity, lightweight secondary channel that checks for "reasonable" results. |
| **Monitor-Actuator Pattern** | A high-fidelity check where an independent sensor monitors the physical result of an actuator's actions. |

---

## Design Principles

### The Weighted Decision Matrix (Trade Study)

Core principle for pattern selection. Rank design criteria (Performance, Safety, Memory, etc.) on a scale of 0-10 and score each pattern against those weights to identify the optimal solution mathematically.

### Three Levels of Design

1. **Architectural Design:** Decisions with systemic scope (e.g., concurrency models).
2. **Mechanistic Design:** Optimizing collaborations that achieve a specific use case.
3. **Detailed Design (Idioms):** Optimizing internal function logic or data types (e.g., Smart Data).

### Five Key Views of Architecture

To fully design an embedded system, you must address the **Subsystem**, **Concurrency**, **Distribution**, **Safety/Reliability**, and **Deployment** views.

### State Machine Concepts

- **Pseudostates:** Beyond basic states, engineers must use Conditional, Fork, Join, and History pseudostates to manage complex logic without "state explosion".
- **Run-To-Completion (RTC) Semantics:** A state machine must finish its entire action sequence (exit -> transition -> entry) before it is allowed to process the next event.

---

## Important Embedded Notes (Hardware and Concurrency)

- **Timeliness as Correctness:** In real-time embedded systems, a "correct" result delivered late is considered a system failure.
- **Unbounded vs. Bounded Priority Inversion:** Using a Mutex without Priority Inheritance (or Priority Ceiling) can lead to a high-priority task being blocked indefinitely by a chain of lower-priority tasks.
- **The `me` Pointer:** To implement classes in C, every member function should take a pointer to the instance data (the `me` pointer) as its first argument.
- **Deterministic State Behavior:** To avoid race conditions, you must ensure that if an event is handled in two independent AND-states, the system does not rely on which one executes first.
- **Event Propagation:** If you do need a specific execution order in AND-states, use an action in the first state to generate (propagate) a new event for the second state.
- **Superloop vs. RTOS:** For very simple systems, a "Superloop" (Cyclic Executive) is often more reliable and easier to certify than a complex RTOS.

---

## Summary Table

| Concept Type | Item | Summary |
| :--- | :--- | :--- |
| Architectural | **Active Object** | An object that "owns" its thread and event queue; critical for event-driven systems. |
| Architectural | **Microkernel** | Minimizes RTOS footprint by only loading required services. |
| Concurrency | **Priority Inheritance** | Prevents unbounded priority inversion by temporarily raising a low-priority task's status. |
| State Logic | **History Pseudostate** | Allows a state machine to "remember" and return to the last active substate after an interrupt or pause. |
| Data Integrity | **One's Complement** | Detects bit-flips in RAM by storing an inverted copy of critical data. |
| Safety | **Heterogeneous Redundancy** | Prevents systematic software bugs by using two different code implementations for the same task. |
