# Task 2 — Analyze Loop Complexity (Inside-Out Rule)

Goal:  
Train yourself to look at loop structures and immediately determine their impact on execution time, which is critical for meeting real-time deadlines in firmware.

Core Rule:
1. Analyze the innermost loop first.
2. Multiply by how many times outer loops run.
3. Add consecutive blocks.
4. Keep only the dominant (largest growth) term.

---

## 1. Single Loop Summing an Array → O(N)

### Pattern (Structure)

Conceptually:

repeat N times:
- read array element
- add to sum

Only one loop, and the work inside the loop is constant time.

### Complexity Reasoning

- Loop runs N times
- Each iteration is O(1)

Total:
O(1) × N = O(N)

### Embedded Notes

- Very common in firmware:
  - summing ADC samples
  - computing checksums
  - scanning buffers
- Safe only if N is strictly bounded.
- Avoid function calls inside the loop when used in real-time paths.

### What to Test

- Run with N = 100, 1000, 10000
- Execution time should increase linearly.

---

## 2. Nested Loop (Bubble-Style Comparison) → O(N²)

### Pattern (Structure)

Conceptually:

repeat N times:
    repeat N times:
        compare (and maybe swap) elements

Even if the inner loop shrinks:

repeat N times:
    repeat (N - i) times:

Total operations:
N + (N-1) + (N-2) + ... ≈ N² / 2 → still O(N²)

### Inside-Out Analysis

- Inner loop: O(N)
- Outer loop: runs N times

Total:
N × N = O(N²)

### Embedded Notes

- Dangerous for real-time firmware.
- Only acceptable when:
  - N is very small (e.g., < 20)
  - data is nearly sorted
- Should never run:
  - in ISRs
  - in control loops
  - in communication stacks

### What to Test

- Double N and measure time.
- Expect runtime to increase by ~4× when N doubles.

---

## 3. Two Consecutive Loops (N then N²) → O(N²)

### Pattern (Structure)

Conceptually:

repeat N times:
    light work

repeat N² times:
    heavy work

These loops are sequential, not nested.

### Complexity Reasoning

First block: O(N)  
Second block: O(N²)

Total:
O(N) + O(N²)

Rule:
Keep only the dominant term → O(N²)

### Why Smaller Terms Are Ignored

As N grows large:

- N becomes insignificant compared to N²

Example:
If N = 10,000  
N = 10,000  
N² = 100,000,000  

Total time is dominated by the quadratic loop.

### Embedded Notes

- This pattern appears when:
  - preprocessing data (linear)
  - then performing heavy processing (quadratic)
- Always analyze the entire function, not individual loops.

---

## Practical Loop Analysis Checklist

When analyzing code:

### Step 1 — Identify Loop Types

- i = 0 .. N        → O(N)
- i *= 2 or i /= 2  → O(log N)
- fixed constant    → O(1)

### Step 2 — Start from Innermost Loop

Always analyze the deepest nested loop first.

### Step 3 — Multiply for Nesting

If:
- inner loop = O(N)
- outer loop runs N times

Then:
Total = O(N²)

### Step 4 — Add for Sequential Blocks

If:
- block A = O(N)
- block B = O(N²)

Then:
Total = O(N²)

---

## Embedded-System Warnings

### 1. Real-Time Deadlines

Even O(N) can be too slow if:
- N is not strictly bounded
- function runs inside ISR or critical task

Always determine the maximum possible N on real hardware.

### 2. Memory and Cache Effects

Big-Oh ignores:
- cache misses
- flash wait states
- bus contention

Quadratic algorithms amplify these problems.

### 3. Determinism

Worst-case time matters more than average in firmware.  
Always analyze worst-case paths.

---

## What You Should Implement (Design Level)

Write three separate functions:

### Function A — Linear Pass

- Input: pointer + length
- Operation: accumulate values
- Goal: observe linear scaling

### Function B — Nested Comparison

- Operates on small fixed-size array
- Compare or swap neighbors
- Goal: observe quadratic growth

### Function C — Sequential Loops

- First loop: light work, N iterations
- Second loop: heavy repeated work, N² iterations
- Goal: observe dominance of quadratic term

---

## How to Validate Your Analysis

### Timing Methods

On PC:
- use std::chrono

On microcontroller:
- toggle GPIO and measure with logic analyzer
- or use hardware timer counters

### Growth Test

Run each function with:

N = 100  
N = 200  
N = 400  

Expected behavior:

| Complexity | When N doubles |
|------------|----------------|
| O(N)       | time × 2       |
| O(N²)      | time × 4       |

This confirms your theoretical analysis in real execution.

---

## Skill You Are Building

By the end of Phase 1, you must be able to:

- Look at code
- Ignore instruction details
- Instantly classify:
  - O(1)
  - O(N)
  - O(N²)
  - O(log N)

This skill is critical for:
- firmware safety
- RTOS task design
- buffer processing
- driver development

---

## Next Recommended Task

Task 3 — Logarithmic Loops and Binary Search Pattern

Focus:
- loops that divide N
- why binary search is O(log N)
- connection to trees and lookup tables in firmware