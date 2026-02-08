# Phase 1 — Asymptotic Notation (Big-Oh, Omega, Theta, little-oh)

This note explains asymptotic notation step by step using two functions:

- f(N) = N^2  
- g(N) = 1000N

Goal:
- Understand what each notation means
- Compare growth rates
- Find the turning point
- Prove Big-Oh using constants (as in Weiss)

---

## 1. What Asymptotic Notations Mean

All notations describe how a function grows when N becomes very large.  
We ignore small N and constant factors.

---

### Big-Oh — O(f(N)) → Upper Bound

Meaning:  
The algorithm grows no faster than f(N) after some point.

Formal definition:  
T(N) is O(f(N)) if there exist constants c > 0 and n0 such that:

T(N) ≤ c · f(N) for all N ≥ n0

Interpretation:  
After N is large enough, T(N) always stays below some multiple of f(N).

Used for: worst-case guarantees.

---

### Big-Omega — Ω(f(N)) → Lower Bound

Meaning:  
The algorithm grows at least as fast as f(N).

Formal:  
T(N) ≥ c · f(N) for all N ≥ n0

Interpretation:  
After some point, T(N) never goes below f(N).

Used for: minimum work required.

---

### Big-Theta — Θ(f(N)) → Tight Bound

Meaning:  
The algorithm grows exactly like f(N).

Formal:  
T(N) is both:
- O(f(N)) and
- Ω(f(N))

Interpretation:  
T(N) is sandwiched between two constant multiples of f(N).

Used for: exact growth rate.

---

### little-oh — o(f(N)) → Strictly Smaller Growth

Meaning:  
T(N) grows strictly slower than f(N).

Formal:  
lim (N → ∞) [ T(N) / f(N) ] = 0

Interpretation:  
T(N) becomes insignificant compared to f(N).

---

## 2. Compare N^2 and 1000N

Compare values:

| N     | 1000N       | N^2         |
|-------|-------------|-------------|
| 10    | 10,000      | 100         |
| 100   | 100,000     | 10,000      |
| 1000  | 1,000,000   | 1,000,000   |
| 10000 | 10,000,000  | 100,000,000 |

At N = 1000, they are equal.  
After that, N^2 grows much faster.

This crossing is called the turning point.

---

## 3. Find the Turning Point Mathematically

Solve:

N^2 = 1000N  
N(N − 1000) = 0  

Solutions:
- N = 0 (ignore)
- N = 1000

For N > 1000:
N^2 > 1000N

So quadratic becomes worse after N = 1000.

---

## 4. Proving Big-Oh Using Constants

Prove:

1000N = O(N^2)

Definition requires constants c and n0 such that:

1000N ≤ c · N^2 for all N ≥ n0

Step 1: Divide by N (N > 0):

1000 ≤ c · N

Step 2: Choose N ≥ 1000

Then:

1000 ≤ N

So if we choose:
- c = 1
- n0 = 1000

Then:

1000N ≤ N^2 for all N ≥ 1000

Therefore:

1000N = O(N^2)

---

## 5. Is N^2 = O(1000N)?

Try:

N^2 ≤ c · 1000N  
Divide by N:

N ≤ 1000c

But N grows forever, so no constant c can satisfy this.

Therefore:

N^2 is NOT O(1000N)

---

## 6. All Notations Between These Two Functions

Let:
- f(N) = 1000N
- g(N) = N^2

Big-Oh:
1000N = O(N^2)

Big-Omega:
N^2 = Ω(1000N)

Big-Theta:
Not true (growth rates are different)

little-oh:
1000N = o(N^2)

Because:

lim (N → ∞) (1000N / N^2) = 1000 / N = 0

---

## 7. How This Connects to Loops

### Single Loop

for (i = 0; i < N; i++)
    work();

Runs N times → O(N)

---

### Nested Loop

for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
        work();

Runs N × N → O(N^2)

---

### Consecutive Loops

for (i = 0; i < N; i++)   // O(N)
    ...

for (j = 0; j < N*N; j++) // O(N^2)
    ...

Total: O(N) + O(N^2) → O(N^2)

Largest term dominates.

---

## 8. Embedded Systems Perspective

In firmware:

- O(N^2) can miss deadlines
- O(log N) is preferred for lookups
- Worst-case time matters more than average

Examples:
- Linear search in buffer → O(N)
- Binary search in sorted table → O(log N)
- Sorting in ISR is usually unacceptable

---

## 9. Practice Problems (Do by Hand)

1. Show that:
   5N + 20 = O(N)

2. Show that:
   N^2 + 100N = Θ(N^2)

3. Decide which grows faster:
   N log N or N^2

4. Find turning point for:
   50N = N^2


---

## 10. Key Intuition

Ask:

If I double the input, how much does work increase?

| Complexity | Input ×2 → Work |
|------------|------------------|
| O(1)       | same             |
| O(N)       | ×2               |
| O(N^2)     | ×4               |
| O(log N)   | +1 step          |

This intuition is more important than formulas when designing firmware.