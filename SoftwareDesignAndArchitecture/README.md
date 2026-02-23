# Software Design and Architecture

Self-study program to become a better Software Architect. Covers design patterns (GoF, embedded, RTOS), SOLID principles, clean architecture, and architectural patterns -- all with C/C++ implementations for embedded systems.

**Embedded-first approach:** All examples and exercises must be embedded-relevant. Generic programming examples are out of scope. GoF patterns that overlap with embedded patterns are learned through the embedded track first.

---

## Goals

1. Master embedded-specific patterns from Douglass ("Design Patterns for Embedded Systems in C") -- primary track
2. Master the remaining GoF design patterns (those not already covered by embedded track)
3. Understand how production RTOS frameworks (QP, FreeRTOS, Zephyr) implement these patterns
4. Apply SOLID principles and clean architecture in resource-constrained environments
5. Recognize architectural patterns beyond design patterns (Layered, Hexagonal, Pipes & Filters, ECS)

---

## Folder Structure

```
SoftwareDesignAndArchitecture/
|-- README.md                   # This file
|-- design_roadmap.md           # Master checklist (tick off as you learn)
|-- CMakeLists.txt              # Root build system
|
|-- references/                 # Read-only knowledge base
|   |-- dp_generic.md           # GoF patterns (20 patterns, 5 marked as covered by embedded)
|   |-- dp_embedded.md          # Douglass book extraction (26+ patterns)
|   +-- dp_rtos.md              # QP, FreeRTOS, Zephyr pattern implementations
|
|-- embedded/                   # Track 1 (PRIMARY): Embedded Patterns (Douglass)
|   |-- study/
|   |   |-- HardwareAccess/     # Observer.md, HardwareProxy.md, ...
|   |   |-- Concurrency/
|   |   |-- StateMachines/
|   |   +-- SafetyReliability/
|   |-- src/
|   |   |-- c/{Domain}/{Pattern}/    # e.g., c/HardwareAccess/HardwareProxy/
|   |   +-- cpp/{Domain}/{Pattern}/
|   +-- exercises/
|       |-- c/{Domain}/{Pattern}/    # Your C solution + task_description.md
|       +-- cpp/{Domain}/{Pattern}/
|
|-- generic/                    # Track 2: Remaining GoF Patterns
|   |-- study/                  # Agent-generated explanations (one per pattern)
|   |-- src/{c,cpp}/{Pattern}/
|   +-- exercises/{c,cpp}/{Pattern}/
|
+-- rtos/                       # Track 3: RTOS Patterns
    |-- study/
    |-- src/{c,cpp}/{Pattern}/
    +-- exercises/{c,cpp}/{Pattern}/
```

**Embedded domains** (match dp_embedded.md categories):
- **HardwareAccess** -- HardwareProxy, HardwareAdapter, Observer, Mediator, Debouncing, Interrupt, Polling
- **Concurrency** -- Cyclic Executive, Static Priority, Critical Region, Guarded Call, Queuing, Rendezvous, Simultaneous Locking, Ordered Locking
- **StateMachines** -- Single Event Receptor, Multiple Event Receptor, State Table, State Pattern, Decomposed AND-State
- **SafetyReliability** -- One's Complement, CRC, Smart Data, Channel, Protected Single Channel, Dual Channel

**Convention:** Each track mirrors the same layout: `study/` (theory), `src/` (reference code), `exercises/` (practice). The embedded track adds a domain sublayer between language and pattern.

---

## Reference Material

| File | Source | Content |
| :--- | :--- | :--- |
| [references/dp_generic.md](references/dp_generic.md) | GoF / Python Masterclass | All 23 patterns in a table: Creational, Structural, Behavioral |
| [references/dp_embedded.md](references/dp_embedded.md) | "Design Patterns for Embedded Systems in C" -- Douglass | 26+ patterns across Hardware Access, Concurrency, State Machines, Safety/Reliability + design principles |
| [references/dp_rtos.md](references/dp_rtos.md) | QP, FreeRTOS, Zephyr analysis | How frameworks turn abstract patterns into production code |

---

## Building and Running Code

**Prerequisites:** CMake >= 3.16, GCC (C11 + C++20 support)

### Basic Usage

```bash
# Configure -- pick a track, domain (embedded only), pattern, language
cmake -B build -DTRACK=embedded -DDOMAIN=HardwareAccess -DPATTERN=HardwareProxy -DLANG=c

# Build
cmake --build build

# Run
./build/HardwareProxy
```

### All Options

| Option | Values | Default | Description |
| :--- | :--- | :--- | :--- |
| `TRACK` | `generic`, `embedded`, `rtos` | (required) | Which learning track |
| `DOMAIN` | `HardwareAccess`, `Concurrency`, `StateMachines`, `SafetyReliability` | (required for embedded) | Embedded domain category |
| `PATTERN` | Pattern folder name | (required) | e.g., `Observer`, `HardwareProxy` |
| `LANG` | `c`, `cpp` | (required) | Language |
| `MODE` | `src`, `exercise` | `src` | `src` = reference demo, `exercise` = your practice code |
| `DEPS` | Semicolon-separated names | (empty) | Cross-pattern dependencies (same domain) |

### Examples

```bash
# Reference demo: embedded Observer in C++ (HardwareAccess domain)
cmake -B build -DTRACK=embedded -DDOMAIN=HardwareAccess -DPATTERN=Observer -DLANG=cpp
cmake --build build && ./build/Observer

# Reference demo: embedded Mediator in C
cmake -B build -DTRACK=embedded -DDOMAIN=HardwareAccess -DPATTERN=Mediator -DLANG=c
cmake --build build && ./build/Mediator

# Your exercise: embedded HardwareProxy in C
cmake -B build -DTRACK=embedded -DDOMAIN=HardwareAccess -DPATTERN=HardwareProxy -DLANG=c -DMODE=exercise
cmake --build build && ./build/HardwareProxy

# Pattern with dependency: HardwareAdapter needs HardwareProxy sources
cmake -B build -DTRACK=embedded -DDOMAIN=HardwareAccess -DPATTERN=HardwareAdapter -DLANG=c -DDEPS=HardwareProxy
cmake --build build && ./build/HardwareAdapter

# Generic track (no DOMAIN needed)
cmake -B build -DTRACK=generic -DPATTERN=Strategy -DLANG=cpp
cmake --build build && ./build/Strategy
```

### Compiler Settings

The build system enforces strict warnings for learning:
- `-Wall -Wextra -Wpedantic -Wshadow -Wconversion`
- `-Wstrict-prototypes` (C only)
- C standard: C11, C++ standard: C++20
- No compiler extensions

---

## Agent-Guided Learning Workflow

This is the formalized protocol for learning each design pattern using the Copilot agents. The coding agent acts as professor -- it teaches, generates reference code, and reviews your practice.

### Step 1: Select a Pattern

Check [design_roadmap.md](design_roadmap.md) and pick the next unchecked pattern. Note which track it belongs to (generic/embedded/rtos).

### Step 2: @plan -- Route and Context

Ask `@plan`:
- Which reference file covers this pattern
- Which track folder to use
- Any prerequisites (e.g., learn HardwareProxy before HardwareAdapter)

### Step 3: @impl-cpp -- Professor Mode

Use this prompt template:

> *"Act as a professional C/C++ Software Architect. Study [Pattern Name] from #file:references/dp_embedded.md (or dp_generic.md). Generate:*
> 1. *Study note answering: When to use? Why best for my case? How do I know it fits? vs alternatives? Pros/Cons?*
> 2. *C implementation (embedded, no dynamic memory, `me` pointer pattern)*
> 3. *C++ implementation (modern C++17/20, no heap, templates/concepts)*
> 4. *Task 1 (reference demo) -- you implement, place in `embedded/src/{lang}/{Domain}/{Pattern}/`*
> 5. *Task 2 (practice exercise) -- I implement, place description in `embedded/exercises/{lang}/{Domain}/{Pattern}/task_description.md`*
> *All examples MUST be embedded-relevant (sensors, actuators, peripherals, ISRs). No generic examples."*

The agent generates:
- `embedded/study/{Domain}/{Pattern}.md` -- theory and decision matrix
- `embedded/src/c/{Domain}/{Pattern}/*.c,*.h` -- C reference implementation
- `embedded/src/cpp/{Domain}/{Pattern}/*.cpp,*.hpp` -- C++ reference implementation
- `embedded/exercises/c/{Domain}/{Pattern}/task_description.md` -- your C exercise
- `embedded/exercises/cpp/{Domain}/{Pattern}/task_description.md` -- your C++ exercise

### Step 4: Study and Implement

1. Read the study note in `embedded/study/{Domain}/{Pattern}.md`
2. Read the reference implementation in `embedded/src/`
3. Implement the exercise yourself (both C and C++ versions)
4. Build and test:
   ```bash
   cmake -B build -DTRACK=embedded -DDOMAIN=HardwareAccess -DPATTERN=Debouncing -DLANG=c -DMODE=exercise
   cmake --build build && ./build/Debouncing
   ```

### Step 5: @code-reviewer -- Review Your Code

> *"Review my implementation in #file:embedded/exercises/c/{Domain}/{Pattern}/main.c against the study note in #file:embedded/study/{Domain}/{Pattern}.md. Check: pattern correctness, MISRA compliance, embedded constraints (no heap, fixed arrays), naming conventions."*

### Step 6: Update Progress

- Check off the pattern in [design_roadmap.md](design_roadmap.md)
- Log the session: `@brain update "Learned {Pattern} -- {track} track"`

### Time Estimate Per Pattern

| Activity | Duration |
| :--- | :--- |
| Study note generation (agent) | ~5 min |
| Reading + understanding | ~20 min |
| C implementation | ~30 min |
| C++ implementation | ~30 min |
| Code review + fixes | ~10 min |
| **Total per pattern** | **~1.5 hours** |

---

## Recommended Learning Order

### Phase 1: Embedded Track (most relevant to daily work)

**HardwareAccess domain:**
- [x] Observer, HardwareProxy, HardwareAdapter, Mediator
- [ ] Debouncing
- [ ] Interrupt
- [ ] Polling

**Concurrency domain:**
- [ ] Cyclic Executive
- [ ] Static Priority
- [ ] Critical Region
- [ ] Guarded Call
- [ ] Queuing
- [ ] Rendezvous
- [ ] Simultaneous Locking
- [ ] Ordered Locking

**StateMachines domain:**
- [ ] Single Event Receptor
- [ ] Multiple Event Receptor
- [ ] State Table
- [ ] State Pattern
- [ ] Decomposed AND-State

**SafetyReliability domain:**
- [ ] One's Complement
- [ ] CRC
- [ ] Smart Data
- [ ] Channel
- [ ] Protected Single Channel
- [ ] Dual Channel

### Phase 2: Generic Track (GoF patterns NOT covered by embedded)

5 GoF patterns are already handled in the embedded track: Observer, Mediator, Adapter, Proxy, State. See `references/dp_generic.md` (Status column).

**Behavioral:**
- [ ] Strategy
- [ ] Command
- [ ] Chain of Responsibility
- [ ] Iterator
- [ ] Memento
- [ ] Interpreter

**Structural:**
- [ ] Facade
- [ ] Composite
- [ ] Decorator
- [ ] Bridge
- [ ] Flyweight

**Creational:**
- [ ] Builder
- [ ] Factory Method
- [ ] Singleton (careful in embedded)
- [ ] Abstract Factory
- [ ] Prototype

### Phase 3: RTOS Track (theoretical, less code-heavy)

34. Active Object (QP)
35. Producer-Consumer (FreeRTOS queues)
36. Devicetree Factory (Zephyr)

---

## Beyond Design Patterns

Design patterns are one pillar of software architecture. To become a complete architect, these additional topics are planned:

### SOLID Principles and Clean Architecture (Uncle Bob)

| Principle | Embedded Relevance |
| :--- | :--- |
| **S** -- Single Responsibility | Each module/driver owns one hardware concern |
| **O** -- Open/Closed | Add new sensors without modifying existing code (Observer, Strategy) |
| **L** -- Liskov Substitution | HAL interfaces must be substitutable across MCU families |
| **I** -- Interface Segregation | Don't force a temperature sensor to implement motor control APIs |
| **D** -- Dependency Inversion | Application depends on abstractions (ILight), not concrete drivers |

Clean Architecture layers in embedded: Hardware -> HAL -> Domain Logic -> Application. Dependencies point inward.

### Architectural Patterns

| Pattern | Description | Embedded Application |
| :--- | :--- | :--- |
| **Layered Architecture** | Strict layer separation with upward-only dependencies | BSP -> HAL -> Middleware -> Application |
| **Hexagonal (Ports & Adapters)** | Core logic surrounded by interchangeable adapters | Swap SPI sensor for I2C sensor without touching business logic |
| **Pipes & Filters** | Data flows through a chain of processing stages | Sensor -> Filter -> Calibrate -> Validate -> Store |
| **ECS (Entity-Component-System)** | Composition over inheritance, data-oriented | IoT device management, sensor fusion architectures |

### System Design (separate learning track)

A dedicated `SystemDesign/` track is planned for:
- Distributed systems concepts
- API design and protocols
- Scalability and reliability patterns
- Interview-style system design problems

This will be a sibling folder to `SoftwareDesignAndArchitecture/` under the learning platform.

---

## Progress Tracking

Use [design_roadmap.md](design_roadmap.md) as the master checklist. Mark patterns with `[x]` as you complete them.

**Current progress:** 4 / 26 embedded patterns studied (Observer, HardwareProxy, HardwareAdapter, Mediator -- all in HardwareAccess domain)
