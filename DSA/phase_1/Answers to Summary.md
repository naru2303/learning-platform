# Phase 1 — Concept Check Answers

---

## 1. Why Do We Ignore Constants (like 3N) in Big-Oh?

Because Big-Oh describes **growth rate**, not exact runtime.

Example:
- Algorithm A: 3N operations
- Algorithm B: 100N operations

Both grow **linearly** as N increases.

As N → very large:
- 3N and 100N are both dominated by **N**

So both are classified as:
- O(N)

### Why This Matters

Constants depend on:
- CPU speed
- compiler
- optimization level

But **algorithm structure** does not change.

Big-Oh lets us compare algorithms independent of hardware.

---

## 2. Hidden O(N) Inside a Loop → Turns O(N) into O(N²)

Yes, this is very common and very dangerous.

### Example Pattern

```c 
for (i = 0; i < N; i++)
{
copy_string(dest, src);   // copy is O(N)
}
```

If `copy_string()` copies N characters, then:

- Outer loop = N
- Inner operation = N

Total = N × N = O(N²)

### Common Hidden O(N) Operations

- strcpy / memcpy on large buffers
- scanning strings (strlen)
- shifting arrays
- searching inside loop

### Embedded Danger

Looks like:
- "just one loop"

But actually:
- quadratic behavior
- can break real-time deadlines

Always check what the inner function really does.

---

## 3. Why O(1) Does NOT Mean "Fast"

O(1) means:

> Execution time does NOT depend on input size.

It does NOT mean:
- small
- quick
- efficient

### Example
```c 
delay_1_second();
```

This is:
- O(1)
- but very slow

Another example:

Reading from slow flash memory:
- still O(1)
- but may take many cycles

### What O(1) Actually Guarantees

If input doubles:
- runtime stays the same

So O(1) = **predictable**, not necessarily fast.

In embedded systems:
- predictability is often more important than speed.

---

## 4. Turning Point: When Does O(N log N) Beat O(N²)?

We compare:

N log N  vs  N²

Divide both by N:

log N  vs  N

So N² grows much faster once N becomes moderate.

### Approximate Turning Point

Solve roughly:

N log₂N = N²  
log₂N = N

This happens around:

N ≈ 4 to 8 (very small)

But in real systems (with constants):

Turning point is usually around:

N ≈ 20–50

After that:

- O(N log N) is **much faster** than O(N²)

### Practical Meaning

For small arrays:
- simple O(N²) sorts may be faster

For larger data:
- O(N log N) algorithms always win

This is why:

- insertion sort → small buffers
- quicksort / mergesort → large datasets

---

## Final Takeaways (Very Important)

- Big-Oh ignores constants to focus on scalability.
- Always inspect what happens **inside** loops.
- O(1) means constant, not fast.
- Algorithm choice matters more as N grows.
- Turning points depend on constants, but growth always wins.

These ideas are critical for:
- real-time safety
- RTOS scheduling
- buffer processing
- firmware reliability

---
