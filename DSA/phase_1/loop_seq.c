#include <stddef.h>
#include <stdint.h>

/*

This example shows two consecutive loops:
- First loop runs N times (O(N))
- Second loop runs N² times (O(N²))

Total complexity is O(N²) because the quadratic term dominates.

Embedded-System Notes
	•	volatile sink ensures the compiler does not remove loops during optimization.
	•	Use fixed N when testing on microcontrollers to keep timing deterministic.
	•	Never place such quadratic work inside:
	    •	ISRs
	    •	hard real-time control loops


---

 * Two sequential loops:
 *   Loop 1: O(N)
 *   Loop 2: O(N^2)
 * Total: O(N^2)
 */


 volatile uint32_t sink;  /* prevents compiler from optimizing loops away */

void sequential_loops(size_t n)
{
    /* -------- First Loop: O(N) -------- */
    for (size_t i = 0; i < n; i++)
    {
        sink += (uint32_t)i;   /* constant-time work */
    }

    /* -------- Second Loop: O(N^2) -------- */
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            sink += (uint32_t)(i + j);  /* constant-time work */
        }
    }
}

/* Example usage with fixed N (embedded style) */
#define TEST_N 200

int main(void)
{
    sequential_loops(TEST_N);

}