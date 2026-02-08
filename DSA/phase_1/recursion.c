/*
 * ============================================================
 * Task 4 — Recursion and the Stack Safety Test
 * ============================================================
 *
 * Goals:
 * 1) Implement Factorial:
 *      - Recursive version
 *      - Iterative version
 *
 * 2) Compare Fibonacci:
 *      - Naive recursive (O(2^N))
 *      - Iterative (O(N))
 *
 * 3) Explain STACK DEPTH and why recursion is dangerous in
 *    embedded systems with small RAM (e.g., 2 KB stack).
 *
 * Style:
 * - Embedded-friendly
 * - No dynamic memory
 * - Deterministic where possible
 *
 * ============================================================
 */

#include <stdint.h>
#include <stddef.h>

/* ============================================================
 * 1) FACTORIAL — RECURSIVE VERSION
 * ============================================================
 *
 * factorial(n) = n * factorial(n-1)
 * base case: factorial(0) = 1
 *
 * Each recursive call:
 * - pushes a stack frame
 * - stores parameters, return address, local variables
 *
 * Stack depth = n calls
 * Complexity:
 * - Time:  O(N)
 * - Space: O(N) due to stack
 *
 * ------------------------------------------------------------
 */

uint32_t factorial_recursive(uint32_t n)
{
    if (n == 0)
        return 1;

    return n * factorial_recursive(n - 1);
}

/* ============================================================
 * 2) FACTORIAL — ITERATIVE VERSION
 * ============================================================
 *
 * Uses a loop instead of recursion.
 *
 * Complexity:
 * - Time:  O(N)
 * - Space: O(1)  (no stack growth)
 *
 * This is the preferred version for firmware.
 *
 * ------------------------------------------------------------
 */

uint32_t factorial_iterative(uint32_t n)
{
    uint32_t result = 1;

    for (uint32_t i = 1; i <= n; i++)
    {
        result *= i;
    }

    return result;
}

/* ============================================================
 * 3) FIBONACCI — NAIVE RECURSIVE (VERY BAD)
 * ============================================================
 *
 * fib(n) = fib(n-1) + fib(n-2)
 * base cases:
 *   fib(0) = 0
 *   fib(1) = 1
 *
 * This version recomputes the SAME values again and again.
 *
 * Example:
 * fib(5) calls fib(4) and fib(3)
 * fib(4) calls fib(3) and fib(2)
 * fib(3) is computed MULTIPLE times
 *
 * Complexity:
 * - Time:  O(2^N)  (exponential)
 * - Space: O(N)    (stack depth)
 *
 * This violates the "Compound Interest Rule":
 *   Never solve the same subproblem repeatedly.
 *
 * ------------------------------------------------------------
 */

uint32_t fib_recursive(uint32_t n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;

    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

/* ============================================================
 * 4) FIBONACCI — ITERATIVE (GOOD)
 * ============================================================
 *
 * Builds sequence step-by-step using two variables.
 *
 * Complexity:
 * - Time:  O(N)
 * - Space: O(1)
 *
 * This is safe and fast for embedded systems.
 *
 * ------------------------------------------------------------
 */

uint32_t fib_iterative(uint32_t n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;

    uint32_t prev = 0;
    uint32_t curr = 1;

    for (uint32_t i = 2; i <= n; i++)
    {
        uint32_t next = prev + curr;
        prev = curr;
        curr = next;
    }

    return curr;
}

/* ============================================================
 * STACK SAFETY ANALYSIS (VERY IMPORTANT)
 * ============================================================
 *
 * Assume:
 * - MCU stack size = 2 KB = 2048 bytes
 *
 * Each recursive call uses stack for:
 * - return address
 * - saved registers
 * - parameters
 * - local variables
 *
 * Typical small MCU stack frame (approx):
 *   32 to 64 bytes per call (depends on compiler and ABI)
 *
 * Let's estimate:
 *   64 bytes per call
 *
 * Max recursive depth:
 *   2048 / 64 = 32 calls
 *
 * So:
 * - factorial_recursive(32) may already crash
 * - fib_recursive(32) may also overflow stack
 *
 * And fib_recursive is worse:
 * - Deep recursion
 * - Massive CPU usage
 *
 * That is why recursion is usually avoided in firmware.
 *
 * ------------------------------------------------------------
 */

/* ============================================================
 * TEST SECTION (EMBEDDED STYLE)
 * ============================================================
 */

int main(void)
{
    uint32_t f1, f2;
    uint32_t fib1, fib2;

    /* -------- Factorial Tests -------- */
    f1 = factorial_recursive(5);  /* 120 */
    f2 = factorial_iterative(5);  /* 120 */

    /* -------- Fibonacci Tests -------- */
    fib1 = fib_recursive(10);     /* 55 (but slow if n grows) */
    fib2 = fib_iterative(10);     /* 55 (fast and safe) */

    /*
     * Do NOT try:
     *   fib_recursive(40)
     * on embedded targets.
     * It will be extremely slow and may crash the stack.
     */

    while (1)
    {
        /* place breakpoint here to inspect results */
    }
}

/* ============================================================
 * SUMMARY — WHAT YOU MUST REMEMBER
 * ============================================================
 *
 * Factorial:
 * - Recursive: simple, but uses O(N) stack
 * - Iterative: same speed, NO stack growth → preferred
 *
 * Fibonacci:
 * - Naive recursive: O(2^N) time, O(N) stack → terrible
 * - Iterative: O(N) time, O(1) space → correct choice
 *
 * Embedded Rule:
 * - Avoid recursion unless depth is strictly bounded
 * - Never use exponential algorithms
 * - Always consider stack size (often only a few KB)
 *
 * This is why the "Compound Interest Rule" matters:
 * - Do not recompute the same work again and again
 *
 * ============================================================
 */