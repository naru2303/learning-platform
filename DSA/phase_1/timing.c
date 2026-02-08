/*
 * ============================================================
 * Task 5 — Empirical Timing and Operation Counting
 * ============================================================
 *
 * Goal:
 * Show the difference between:
 *   - O(N) Linear Search
 *   - O(N^2) Bubble Sort
 *
 * Using TWO measurements:
 *   1) Real execution time (using clock() for PC simulation)
 *   2) Operation counter (counts comparisons and assignments)
 *
 * NOTE:
 * In real embedded systems you would use:
 *   - hardware timers
 *   - GPIO toggle + logic analyzer
 *
 * Here we use time.h only to demonstrate the concept.
 *
 * ============================================================
 */

#include <stdint.h>
#include <stddef.h>
#include <time.h>
#include <stdio.h>

/* ------------------------------------------------------------
 * GLOBAL OPERATION COUNTER
 * ------------------------------------------------------------
 * Increment this whenever we do:
 *   - a comparison
 *   - an assignment
 *
 * This lets us SEE if operations grow like N or N^2.
 * ------------------------------------------------------------
 */

volatile uint64_t op_count = 0;

/* ============================================================
 * O(N) — LINEAR SEARCH
 * ============================================================
 *
 * Searches for target in array.
 * Worst case: check every element → O(N)
 *
 * ------------------------------------------------------------
 */

int linear_search(const int32_t *arr, size_t n, int32_t target)
{
    for (size_t i = 0; i < n; i++)
    {
        op_count++;                 /* comparison */
        if (arr[i] == target)
        {
            return (int)i;
        }
    }
    return -1;
}

/* ============================================================
 * O(N^2) — BUBBLE SORT
 * ============================================================
 *
 * Nested loops → quadratic growth.
 * Counts comparisons and swaps.
 *
 * ------------------------------------------------------------
 */

void bubble_sort(int32_t *arr, size_t n)
{
    for (size_t i = 0; i < n - 1; i++)
    {
        for (size_t j = 0; j < n - 1 - i; j++)
        {
            op_count++;             /* comparison */
            if (arr[j] > arr[j + 1])
            {
                /* swap = 3 assignments */
                int32_t tmp = arr[j];   op_count++;
                arr[j] = arr[j + 1];    op_count++;
                arr[j + 1] = tmp;       op_count++;
            }
        }
    }
}

/* ============================================================
 * TEST DATA
 * ============================================================
 */

#define N 500

static int32_t data_search[N];
static int32_t data_sort[N];

/* ============================================================
 * MAIN — TIMING + OPERATION COUNT
 * ============================================================
 */

int main(void)
{
    clock_t start, end;
    double elapsed;

    /* Initialize arrays */
    for (size_t i = 0; i < N; i++)
    {
        data_search[i] = (int32_t)i;
        data_sort[i] = (int32_t)(N - i);   /* reverse order (worst case) */
    }

    /* =====================================================
     * LINEAR SEARCH TEST (O(N))
     * =====================================================
     */

    op_count = 0;
    start = clock();

    linear_search(data_search, N, -1);  /* worst case: not found */

    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Linear Search:\n");
    printf("  Time: %f sec\n", elapsed);
    printf("  Operations: %llu\n\n", (unsigned long long)op_count);

    /* =====================================================
     * BUBBLE SORT TEST (O(N^2))
     * =====================================================
     */

    op_count = 0;
    start = clock();

    bubble_sort(data_sort, N);

    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Bubble Sort:\n");
    printf("  Time: %f sec\n", elapsed);
    printf("  Operations: %llu\n\n", (unsigned long long)op_count);

    while (1)
    {
        /* stop here for debugger */
    }
}

/* ============================================================
 * HOW TO INTERPRET RESULTS
 * ============================================================
 *
 * Try changing:
 *   #define N 200
 *   #define N 400
 *   #define N 800
 *
 * You should observe:
 *
 * Linear Search:
 *   - Operations ≈ N
 *   - Time roughly doubles when N doubles
 *
 * Bubble Sort:
 *   - Operations ≈ N^2
 *   - Time roughly quadruples when N doubles
 *
 * ============================================================
 *
 * WHY OPERATION COUNT MATTERS IN EMBEDDED SYSTEMS
 *
 * - Timers may vary due to:
 *     cache, flash wait states, interrupts
 *
 * - Counting operations shows TRUE algorithm growth
 *
 * This is useful when:
 * - estimating worst-case execution time (WCET)
 * - deciding if code is safe for ISR or RTOS task
 *
 * ============================================================
 *
 * EMBEDDED VERSION (REAL MCU)
 *
 * Replace clock() with:
 *   - hardware timer read
 *   - GPIO toggle before/after function
 *
 * Operation counter still works the same.
 *
 * ============================================================
 */