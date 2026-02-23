# Hardware Task: The "BitCruncher" Timer

You are tasked to write a Hardware Proxy for a simple 16-bit Down-Counting Timer peripheral called **"BitCruncher"**.

## Specs
- **Register Width**: 32-bit (Standard)
- **Base Address**: `0x4000_2000` (Mock)

## Register Map

| Offset | Name | R/W | Description |
| :--- | :--- | :--- | :--- |
| `0x00` | `CR` (Control) | R/W | **Bit 0**: `ENABLE` (1=Run, 0=Stop)<br>**Bit 4**: `IRQ_EN` (Interrupt Enable) |
| `0x04` | `SR` (Status) | R/W | **Bit 0**: `UIF` (Update/Overflow Flag). Hardware sets to 1. Write 0 to clear. |
| `0x08` | `ARR` (AutoReload) | R/W | The value to reload into the counter when it hits 0. |
| `0x0C` | `CNT` (Counter) | R | The current countdown value. Read-only. |

## Requirements
1.  **C Version**: Create a `TimerProxy` struct and functions to `Init`, `Start`, `Stop`, `SetReload`, `GetCounter`, and `ClearFlag`.
2.  **C++ Version**: Create a `TimerDriver` class with strongly typed methods. Ensure `CNT` cannot be written to.

## Files to Edit
- `c_code/HardwareProxy/Practice/timer_driver.h`
- `c_code/HardwareProxy/Practice/timer_driver.c`
- `cpp_code/HardwareProxy/Practice/TimerDriver.hpp`
