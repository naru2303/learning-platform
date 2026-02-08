# Solutions — Phase 1 Practice Problems (Asymptotic Analysis)

---

## 1. Show that: 5N + 20 = O(N)

### Step 1: Use the Big-Oh definition

We must find constants c > 0 and n₀ such that:

5N + 20 ≤ c · N   for all N ≥ n₀

---

### Step 2: Simplify the inequality

5N + 20 ≤ cN  
20 ≤ (c − 5)N

---

### Step 3: Choose suitable constants

Let:
- c = 6

Then:
20 ≤ N

So the inequality holds for all:

N ≥ 20

---

### Step 4: Conclusion

There exist constants c = 6 and n₀ = 20 such that:

5N + 20 ≤ 6N for all N ≥ 20

Therefore:

5N + 20 = O(N)

---

## 2. Show that: N² + 100N = Θ(N²)

To prove Θ(N²), we must show both:

- O(N²) (upper bound)
- Ω(N²) (lower bound)

---

### Step 1: Prove O(N²)

We want:

N² + 100N ≤ c · N²

Divide both sides by N² (N > 0):

1 + 100/N ≤ c

For N ≥ 1:

1 + 100/N ≤ 101

So choose:
- c = 101
- n₀ = 1

Thus:

N² + 100N = O(N²)

---

### Step 2: Prove Ω(N²)

We want:

N² + 100N ≥ c · N²

Since 100N ≥ 0:

N² + 100N ≥ N²

So choose:
- c = 1
- n₀ = 1

Thus:

N² + 100N = Ω(N²)

---

### Step 3: Conclusion

Because N² + 100N is both O(N²) and Ω(N²):

N² + 100N = Θ(N²)

---

## 3. Decide Which Grows Faster: N log N or N²

### Step 1: Compare growth using division

Compute:

(N log N) / (N²) = (log N) / N

---

### Step 2: Take the limit as N → ∞

lim (N → ∞) (log N) / N = 0

---

### Step 3: Conclusion

Because the ratio goes to 0:

N log N = o(N²)

Therefore:

N² grows faster than N log N

---

## 4. Find the Turning Point for: 50N = N²

### Step 1: Solve the equation

N² = 50N  
N(N − 50) = 0

---

### Step 2: Solutions

- N = 0 (ignore)
- N = 50

---

### Step 3: Interpretation

At N = 50, both functions are equal.

For N > 50:
N² > 50N

So after N = 50, the quadratic function grows faster.

---

## Summary

| Problem | Result |
|-------|--------|
| 5N + 20 | O(N) |
| N² + 100N | Θ(N²) |
| Faster growth | N² |
| Turning point | N = 50 |

These exercises reinforce:
- Ignoring constants
- Dominant terms
- Using limits and inequalities
- Understanding growth behavior